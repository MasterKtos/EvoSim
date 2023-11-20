// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateTravel.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/AI/Pathfinding/AIManager.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"
#include "EvoSim/Creature/CreatureComponents/MemoryComponent.h"
#include "EvoSim/Creature/CreatureComponents/NeedsEvaluatorComponent.h"
#include "EvoSim/Map/Tile.h"

UCreatureStateTravel::UCreatureStateTravel()
{
	StateName = ECreatureStateName::Travel;
}

bool UCreatureStateTravel::TryEnterState(const ECreatureStateName FromState)
{
	// Creature might already be on the target
	// returns false because TryToSatisfyNeeds()
	// already triggers state change
	if(TryToSatisfyNeeds())
		return false;

	GetPathForCurrentNeed();
	
	return !MovesToDo.IsEmpty();
}

bool UCreatureStateTravel::TryExitState()
{
	if(TryToSatisfyNeeds())
		return true;
	
	// Recalculate path if there's a creature on the way
	if(MovesToDo.IsEmpty() ||
		!MovesToDo.IsEmpty() && Owner->CurrentTile->GetNeighbour(MovesToDo.Last())->CreaturesPresent.Num() > 0)
	{
		GetPathForCurrentNeed();

		// Cannot find path to any need
        if(MovesToDo.IsEmpty())
        {
        	Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Rest);
        	return false;
        }

		// If, even after recalculating path, Owner is still blocked by other creatures,
		// just go on a tile with other creature
		// if(Owner->CurrentTile->GetNeighbour(MovesToDo.Last())->CreaturesPresent.Num() > 0 && Owner->Move(MovesToDo.Last()))
		// {
		// 	MovesToDo.Pop();
		// 	return true;
		// }
	}
	
	return false;
}

void UCreatureStateTravel::Update()
{
	if(TryExitState())
		return;
	
	// TODO: Check if there is better way to the target

	if(TargetedNeed != Owner->NeedsEvaluator->GetCurrentNeed())
		GetPathForCurrentNeed();
	
	if(!MovesToDo.IsEmpty() && Owner->Move(MovesToDo.Last()))
	{
		MovesToDo.Pop();
	}
}

void UCreatureStateTravel::GetPathForCurrentNeed()
{
	Owner->FovComponent->UpdateTilesInSight();
    
	const TArray<ATile*> Plants = Owner->FovComponent->GetPlantTilesInSight();
	const TArray<ATile*> Water = Owner->FovComponent->GetWaterTilesInSight();
	const TArray<ATile*> Bros = Owner->FovComponent->GetHerbCreaturesTilesInSight();
	
	TArray<ATile*> CurrentTargets;
	TargetedNeed = Owner->NeedsEvaluator->GetCurrentNeed();
	switch(TargetedNeed)
	{
	case ECreatureNeed::Eat:
		CurrentTargets = !Plants.IsEmpty() ? Plants : Owner->MemoryComponent->GetRememberedTiles(ETileType::Land, ETileType::Plant);
		break;
		
	case ECreatureNeed::Drink:
		CurrentTargets = !Water.IsEmpty() ? Water : Owner->MemoryComponent->GetRememberedTiles(ETileType::Water);
		break;
		
	case ECreatureNeed::DrinkOrEat:
		if(!Water.IsEmpty()) { CurrentTargets = Water; break; }
		if(!Plants.IsEmpty()) { CurrentTargets = Plants; break; }
		
		CurrentTargets = Owner->MemoryComponent->GetRememberedTiles(ETileType::Water);
		if(CurrentTargets.IsEmpty())
			CurrentTargets = Owner->MemoryComponent->GetRememberedTiles(ETileType::Land, ETileType::Plant);
		break;
		
	case ECreatureNeed::Reproduce:
		CurrentTargets = Bros; break;
		
	case ECreatureNeed::Satisfied:
	default: ;
	}

	MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, CurrentTargets);
}

bool UCreatureStateTravel::TryToSatisfyNeeds() const
{
	ECreatureStateName ToState = StateName;
	switch(Owner->NeedsEvaluator->GetCurrentNeed())
	{
	case ECreatureNeed::Drink:
		ToState = ECreatureStateName::Drink; break;
		
	case ECreatureNeed::Eat:
		ToState = ECreatureStateName::Eat; break;
				
	case ECreatureNeed::Reproduce:
		ToState = ECreatureStateName::Reproduce; break;

	case ECreatureNeed::Satisfied:
		ToState = ECreatureStateName::Rest; break;
		
	case ECreatureNeed::DrinkOrEat:
		if(Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Drink))
			return true;
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Eat);
	
	default: break;
	}
	
	return Owner->AIComponent->ChangeCurrentState(ToState);
}

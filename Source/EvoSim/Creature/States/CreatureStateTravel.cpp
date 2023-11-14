// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateTravel.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/AI/Pathfinding/AIManager.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/CreatureMovementComponent.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"
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
			
		if(Owner->CurrentTile->GetNeighbour(MovesToDo.Last())->CreaturesPresent.Num() > 0 && Owner->Move(MovesToDo.Last()))
		{
			MovesToDo.Pop();
			return true;
		}
	}

	
	
	return false;
}

void UCreatureStateTravel::Update()
{
	if(TryExitState())
		return;
	
	// TODO: Check if there is better way to the target
	
	if(!MovesToDo.IsEmpty() && Owner->Move(MovesToDo.Last()))
	{
		MovesToDo.Pop();
	}
}

void UCreatureStateTravel::GetPathForCurrentNeed()
{
	const int Hunger = Owner->Hunger;
	const int Thirst = Owner->Thirst;
	
	Owner->FovComponent->UpdateTilesInSight();
    
	const TArray<ATile*> Plants = Owner->FovComponent->GetPlantTilesInSight();
	const TArray<ATile*> Water = Owner->FovComponent->GetWaterTilesInSight();
	
	TArray<ATile*> CurrentTargets;
	// Check conditions for travelling to Plants
	if (Hunger >= Thirst && !Plants.IsEmpty())
		CurrentTargets = Plants;
	// Check conditions for travelling to Water
	else if (Hunger < Thirst &&!Water.IsEmpty())
		CurrentTargets = Water;

	MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, CurrentTargets);
}

bool UCreatureStateTravel::TryToSatisfyNeeds() const
{
	if(Owner->Thirst >= Owner->Hunger || Owner->Thirst > 80)
	{
		for(const auto Direction : TEnumRange<EDirection>())
		{
			if(const auto Neighbour = Owner->CurrentTile->GetNeighbour(Direction); IsValid(Neighbour) && Neighbour->Type == ETileType::Water)
				return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Drink);
		}
	}
	else if(Owner->CurrentTile->Type == ETileType::Plant)
	{
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Eat);
	}
	return false;
}

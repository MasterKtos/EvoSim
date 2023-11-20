// Fill out your copyright notice in the Description page of Project Settings.


#include "CarnivoreStateTravel.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/AI/Pathfinding/AIManager.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/Carnivorous.h"
#include "EvoSim/Creature/Herbivorous.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"
#include "EvoSim/Creature/CreatureComponents/NeedsEvaluatorComponent.h"
#include "EvoSim/Map/Tile.h"

bool UCarnivoreStateTravel::TryEnterState(const ECreatureStateName FromState)
{
	// Creature might already be on the target
	if(TryExitState())
		return false;

	const auto CurrentNeed = Owner->NeedsEvaluator->GetCurrentNeed();
	if(CurrentNeed == ECreatureNeed::Satisfied)
		return false;
	
	Owner->FovComponent->UpdateTilesInSight();
    
	const TArray<ATile*> Meat = Owner->FovComponent->GetHerbCreaturesTilesInSight();
	const TArray<ATile*> Water = Owner->FovComponent->GetWaterTilesInSight();
	const TArray<ATile*> Bros = Owner->FovComponent->GetMeatCreaturesTilesInSight();
	
	
	TArray<ATile*> CurrentTargets;
	switch(CurrentNeed)
	{
	case ECreatureNeed::Eat: CurrentTargets = Meat; break;
	case ECreatureNeed::Drink: CurrentTargets = Water; break;
	case ECreatureNeed::Reproduce: CurrentTargets = Bros; break;
	case ECreatureNeed::DrinkOrEat: CurrentTargets = !Water.IsEmpty() ? Water:Meat; break;
	case ECreatureNeed::Satisfied: //falls through
	default: break;
	}

	MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, CurrentTargets);
	
	return !MovesToDo.IsEmpty();
}

bool UCarnivoreStateTravel::TryExitState()
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

void UCarnivoreStateTravel::Update()
{
	Super::Update();
}

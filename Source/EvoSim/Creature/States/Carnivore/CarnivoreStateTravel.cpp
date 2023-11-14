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
	case ECreatureNeed::Satisfied: //falls through
	default: break;
	}

	MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, CurrentTargets);
	
	return !MovesToDo.IsEmpty();
}

bool UCarnivoreStateTravel::TryExitState()
{
	const auto CurrentNeed = Owner->NeedsEvaluator->GetCurrentNeed();
	for(const auto Direction : TEnumRange<EDirection>())
	{
		const auto Neighbour = Owner->CurrentTile->GetNeighbour(Direction);
		if(!IsValid(Neighbour))
			continue;

		switch(CurrentNeed)
		{
		case ECreatureNeed::Eat:
			if(!(Neighbour->CreaturesPresent.Num() > 0 &&
			   Neighbour->CreaturesPresent.FindItemByClass<AHerbivorous>()))
				break;
			return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Eat);
		case ECreatureNeed::Drink:
			if(Neighbour->Type != ETileType::Water)
				break;
			return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Drink);
		case ECreatureNeed::Reproduce:
			if(!(Neighbour->CreaturesPresent.Num() > 0 &&
			Neighbour->CreaturesPresent.FindItemByClass<ACarnivorous>()))
				break;
			return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Reproduce);
		case ECreatureNeed::Satisfied:
			if(Neighbour->Type == ETileType::Water)
				return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Drink);
			if(Neighbour->CreaturesPresent.Num() > 0 &&
			   Neighbour->CreaturesPresent.FindItemByClass<AHerbivorous>())
				return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Eat);
		default: break;
		}
	}
	
	return false;
}

void UCarnivoreStateTravel::Update()
{
	Super::Update();
}

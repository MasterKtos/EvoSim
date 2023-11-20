// Fill out your copyright notice in the Description page of Project Settings.


#include "CarnivoreStateTravel.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/AI/Pathfinding/AIManager.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"
#include "EvoSim/Creature/CreatureComponents/NeedsEvaluatorComponent.h"
#include "EvoSim/Map/Tile.h"

void UCarnivoreStateTravel::GetPathForCurrentNeed()
{
	// Super::GetPathForCurrentNeed();
	const auto CurrentNeed = Owner->NeedsEvaluator->GetCurrentNeed();
	
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
}

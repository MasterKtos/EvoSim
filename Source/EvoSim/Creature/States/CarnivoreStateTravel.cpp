// Fill out your copyright notice in the Description page of Project Settings.


#include "CarnivoreStateTravel.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/AI/Pathfinding/AIManager.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"
#include "EvoSim/Map/Tile.h"

UCarnivoreStateTravel::UCarnivoreStateTravel()
{
	StateName = ECreatureStateName::Travel;
}

bool UCarnivoreStateTravel::TryEnterState(const ECreatureStateName FromState)
{
	// Creature might already be on the target
	if(TryExitState())
		return false;
	
	const int Hunger = Owner->Hunger;
	const int Thirst = Owner->Thirst;
	
	Owner->FovComponent->UpdateTilesInSight();
    
	const TArray<ATile*> Meat = Owner->FovComponent->GetHerbCreaturesTilesInSight();
	const TArray<ATile*> Water = Owner->FovComponent->GetWaterTilesInSight();
	
	TArray<ATile*> CurrentTargets;
	// Check conditions for hunting
	if (Hunger > Thirst && !Meat.IsEmpty())
		CurrentTargets = Meat;
	// Check conditions for travelling to Water
	else if (!Water.IsEmpty())
		CurrentTargets = Water;

	MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, CurrentTargets);
	
	return !MovesToDo.IsEmpty();
}

bool UCarnivoreStateTravel::TryExitState()
{
	if(Owner->Thirst > Owner->Hunger)
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

void UCarnivoreStateTravel::Update()
{
	Super::Update();
}

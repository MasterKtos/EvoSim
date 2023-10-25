// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateTravel.h"

#include "EvoSim/AI/AIManager.h"
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
	const int Hunger = Owner->Hunger;
	const int Thirst = Owner->Thirst;
	
	Owner->FovComponent->UpdateTilesInSight();
    
	const TArray<ATile*> Plants = Owner->FovComponent->GetPlantTilesInSight();
	const TArray<ATile*> Water = Owner->FovComponent->GetWaterTilesInSight();
	
	TArray<ATile*> CurrentTargets;
	// Check conditions for travelling to Plants
	if (Hunger > Thirst && !Plants.IsEmpty())
		CurrentTargets = Plants;
	// Check conditions for travelling to Water
	else if (!Water.IsEmpty())
		CurrentTargets = Water;

	MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, CurrentTargets);
	// Creature might already be on the target
	if(MovesToDo.IsEmpty())
	{
		TryExitState();
		return false;
	}
	return true;
}

bool UCreatureStateTravel::TryExitState()
{
	if(!MovesToDo.IsEmpty())
		return false;

	// TODO: check based on the currently set need to satisfy

	if(Owner->CurrentTile->Type == ETileType::Plant)
	{
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Eat);
	}
	for(const auto Direction : TEnumRange<EDirection>())
	{
		if(const auto Neighbour = Owner->CurrentTile->GetNeighbour(Direction); IsValid(Neighbour) && Neighbour->Type == ETileType::Water)
			return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Drink);
	}

	ensureMsgf(false, TEXT("this here should literally never happen"));
	return false;
}

void UCreatureStateTravel::Update()
{
	Super::Update();
	
	// TODO: Check if creature needs to change target 
	// TODO: Check if there is better way to the target

	// TODO: Travel to next tile in path
	if(!Owner->MovementComponent->IsAtTarget())
		return;
	
	if(!MovesToDo.IsEmpty() && Owner->Move(MovesToDo.Last()))
	{
		MovesToDo.Pop();
	}
}

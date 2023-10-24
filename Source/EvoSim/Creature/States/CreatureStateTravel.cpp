// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateTravel.h"

#include "EvoSim/AI/AIManager.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/CreatureMovementComponent.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"
#include "EvoSim/Map/Tile.h"
#include "EvoSim/Map/TilePlant.h"

bool UCreatureStateTravel::TryEnterState(const ECreatureStateName FromState)
{
	const int Hunger = Owner->Hunger;
	const int Thirst = Owner->Thirst;
	
	Owner->FovComponent->UpdateTilesInSight();
    
	const TArray<ATile*> Plants = Owner->FovComponent->GetPlantTilesInSight();
	const TArray<ATile*> Water = Owner->FovComponent->GetWaterTilesInSight();
    
	if(Hunger > Thirst && !Plants.IsEmpty())
	{
		MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, Plants);
		if(!MovesToDo.IsEmpty())
			return true;
	}
	if(!Water.IsEmpty())
	{
		MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, Water);
		if(!MovesToDo.IsEmpty())
			return true;
	}
	
	return false;
}

bool UCreatureStateTravel::TryExitState()
{
	if(!MovesToDo.IsEmpty())
		return false;

	if(Owner->CurrentTile->Type == ETileType::Plant)
	{
		Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Eat);
		return true;
	}
	if(Owner->CurrentTile->Type == ETileType::Water)
	{
		Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Drink);
		return true;
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

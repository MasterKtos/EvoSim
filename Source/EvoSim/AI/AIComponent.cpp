// Fill out your copyright notice in the Description page of Project Settings.


#include "AIComponent.h"

#include "AIManager.h"
#include "ComponentReregisterContext.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/CreatureMovementComponent.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"
#include "EvoSim/Creature/States/CreatureState.h"
#include "EvoSim/Creature/States/CreatureStateDrink.h"
#include "EvoSim/Creature/States/CreatureStateEat.h"
#include "EvoSim/Creature/States/CreatureStateReproduce.h"
#include "EvoSim/Creature/States/CreatureStateRest.h"
#include "EvoSim/Creature/States/CreatureStateTravel.h"
#include "EvoSim/Manager/SimManager.h"
#include "EvoSim/Map/Tile.h"
#include "EvoSim/Map/TilePlant.h"

UAIComponent::UAIComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAIComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACreature>(GetOwner());
	if(!ensure(Owner))
		UE_LOG(LogActorComponent, Log, TEXT("FovComponent | No Owner (or owner is not a Creature)."));

	if(USimManager* SimManager = Cast<USimManager>(GetWorld()->GetGameInstance()))
		SimManager->AddToUpdate(this);

	CreatureStateMap = {
		{ECreatureStateName::Rest, NewObject<UCreatureStateRest>()},
		{ECreatureStateName::Eat, NewObject<UCreatureStateEat>()},
		{ECreatureStateName::Drink, NewObject<UCreatureStateDrink>()},
		{ECreatureStateName::Travel, NewObject<UCreatureStateTravel>()},
		{ECreatureStateName::Reproduce, NewObject<UCreatureStateReproduce>()},
	 };
	for (const auto CreatureState : CreatureStateMap)
	{
		CreatureState.Value->Owner = Owner;
	}

	CurrentCreatureState = CreatureStateMap[ECreatureStateName::Rest];
}

void UAIComponent::Update()
{
	Owner->Hunger++;
	Owner->Thirst++;
	Owner->Randy++;
	CurrentCreatureState->Update();
	return;
	
	Owner->Hunger++;
	Owner->Thirst++;

	const int Hunger = Owner->Hunger;
	const int Thirst = Owner->Thirst;
	
	if(!Owner->MovementComponent->IsAtTarget())
		return;
	
	if(!MovesToDo.IsEmpty())
	{
		if(Owner->Move(MovesToDo.Last()))
			MovesToDo.Pop();
		
		if(MovesToDo.IsEmpty())
		{
			switch (Owner->CurrentTile->Type) {
			case ETileType::Water:
				Owner->Thirst = 0;
				break;
			case ETileType::Plant:
				Cast<ATilePlant>(Owner->CurrentTile)->Eat();
				Owner->Hunger = 0;
				break;
			default: break;
			}
		}
		else
			return;
	}

	// Creature died of thirst and/or hunger 
	if(Hunger >= 100 || Thirst >= 100)
	{
		if(USimManager* SimManager = Cast<USimManager>(GetWorld()->GetGameInstance()))
			SimManager->RemoveFromUpdate(this);
		Owner->Destroy();
		return;
	}

	// Satisfy creature needs
	if(Hunger < 50 && Thirst < 50)
	{
		// RandomDirection
		return;
	}
	else
		FindNewPath();
	
	
}

bool UAIComponent::ChangeCurrentState(const ECreatureStateName NewStateName)
{
	if(CreatureStateMap[NewStateName]->TryEnterState(CurrentCreatureState->StateName))
	{
		CurrentCreatureState = CreatureStateMap[NewStateName];
		return true;
	}
	return false;
}

void UAIComponent::FindNewPath()
{
	const int Hunger = Owner->Hunger;
	const int Thirst = Owner->Thirst;
	
	Owner->FovComponent->UpdateTilesInSight();
    
    const TArray<ATile*> Plants = Owner->FovComponent->GetPlantTilesInSight();
    // const TArray<ATile*> Water = Owner->FovComponent->GetWaterTilesInSight();
    
    if(Hunger > Thirst && !Plants.IsEmpty())
    {
    	MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, Plants);
    }
    // else if(!Water.IsEmpty())
    // {
    // 	MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, Water);
    // }
    else
    {
    	// Go to random tile
    }
}


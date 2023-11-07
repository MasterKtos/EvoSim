// Fill out your copyright notice in the Description page of Project Settings.


#include "AIComponent.h"

#include "ComponentReregisterContext.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/States/CreatureState.h"
#include "EvoSim/Creature/States/CreatureStateDrink.h"
#include "EvoSim/Creature/States/CreatureStateEat.h"
#include "EvoSim/Creature/States/CreatureStateReproduce.h"
#include "EvoSim/Creature/States/CreatureStateRest.h"
#include "EvoSim/Creature/States/CreatureStateTravel.h"
#include "EvoSim/Manager/SimManager.h"

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
}

void UAIComponent::Update()
{
	Owner->Hunger++;
	Owner->Thirst++;
	Owner->Randy++;
	CurrentCreatureState->Update();
}

void UAIComponent::InitializeStateMap(const TMap<ECreatureStateName, UCreatureState*>& StateMap, ECreatureStateName InitialStateName)
{
	CreatureStateMap = StateMap;
	CurrentCreatureState = CreatureStateMap[InitialStateName];
	
	for (const auto CreatureState : CreatureStateMap)
	{
		CreatureState.Value->Owner = Owner;
	}
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

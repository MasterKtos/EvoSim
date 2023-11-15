// Fill out your copyright notice in the Description page of Project Settings.


#include "AIComponent.h"

#include "ComponentReregisterContext.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/States/CreatureState.h"
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

	Cast<USimManager>(GetWorld()->GetGameInstance())->AddToUpdate(this);
}

void UAIComponent::Update()
{
	Owner->Hunger++;
	Owner->Thirst++;
	Owner->Randy++;

	if(Owner->Hunger > 100 || Owner->Thirst > 100)
	{
		Cast<USimManager>(GetWorld()->GetGameInstance())->RemoveFromUpdate(this);
		Owner->Destroy();
		return;
	}
	
	CurrentSpeed += Owner->Speed;
	if (CurrentSpeed >= 1)
	{
		CurrentSpeed--;
		CurrentCreatureState->Update();
	}
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

bool UAIComponent::ForceCurrentState(const ECreatureStateName NewStateName, ACreature* ForcedBy)
{
	if(CurrentCreatureState == CreatureStateMap[NewStateName])
		return false;

	CreatureStateMap[NewStateName]->ForceEnterState(ForcedBy);
	CurrentCreatureState = CreatureStateMap[NewStateName];
	return true;
}

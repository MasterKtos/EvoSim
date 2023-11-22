// Fill out your copyright notice in the Description page of Project Settings.


#include "AIComponent.h"

#include "ComponentReregisterContext.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/MemoryComponent.h"
#include "EvoSim/Creature/States/CreatureState.h"
#include "EvoSim/Creature/States/CreatureStateTravel.h"
#include "EvoSim/Manager/SimManager.h"
#include "Pathfinding/AIManager.h"

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

	if(Owner->Randy > 100)
		Owner->Randy = 100;

	if(Owner->Hunger > 100 || Owner->Thirst > 100)
	{
		Owner->Die();
		return;
	}
	
	CurrentSpeed += Owner->Speed;
	if (CurrentSpeed >= 1)
	{
		CurrentSpeed--;
		Owner->MemoryComponent->CheckTilesToForget();
		
		if(Owner->IsInDanger())
		{
			CurrentCreatureState = CreatureStateMap[ECreatureStateName::Rest];
			Owner->RunAway();
		}
		else
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
		switch(CurrentCreatureState->StateName)
		{
		case ECreatureStateName::Drink:
			for (const EDirection Direction : TEnumRange<EDirection>())
			{
				ATile* NeighboringTile = Owner->CurrentTile->GetNeighbour(Direction);
				if(NeighboringTile->Type == ETileType::Water)
				{
					Owner->MemoryComponent->RememberTile(NeighboringTile);
					break;
				}
			}
			break;
		case ECreatureStateName::Eat:
			Owner->MemoryComponent->RememberTile(Owner->CurrentTile);
		default: break;
		}
		
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

void UAIComponent::ForcePath(const TArray<EDirection>& Array)
{
	Cast<UCreatureStateTravel>(CreatureStateMap[ECreatureStateName::Travel])->MovesToDo = Array;
}

void UAIComponent::ForcePathTo(ATile* Tile)
{
	Cast<UCreatureStateTravel>(CreatureStateMap[ECreatureStateName::Travel])->MovesToDo = Cast<USimManager>(GetWorld()->GetGameInstance())->AIManager->FindPathToTile(Owner->CurrentTile, Tile);
}

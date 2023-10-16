// Fill out your copyright notice in the Description page of Project Settings.


#include "AIComponent.h"

#include "AIManager.h"
#include "ComponentReregisterContext.h"
#include "BaseGizmos/ParameterToTransformAdapters.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"
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

	const int Hunger = Owner->Hunger;
	const int Thirst = Owner->Thirst;
	
	if(Hunger >= 100 || Thirst >= 100)
	{
		if(USimManager* SimManager = Cast<USimManager>(GetWorld()->GetGameInstance()))
			SimManager->RemoveFromUpdate(this);
		Owner->Destroy();
		return;
	}
	
	Owner->FovComponent->UpdateTilesInSight();

	const TArray<ATile*> Plants = Owner->FovComponent->GetPlantTilesInSight();
	const TArray<ATile*> Water = Owner->FovComponent->GetPlantTilesInSight();

	if(Hunger > Thirst)
	{
		if(Hunger > 80)
		{
			// RandomDirection
		}
		else if(!Plants.IsEmpty())
		{
			MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, Plants);
		}
		else
		{
			MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, Water);
		}
	}
	else
	{
		if(Thirst > 80)
		{
			// RandomDirection
		}
		else if(!Water.IsEmpty())
		{
			MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, Water);
		}
		else
		{
			MovesToDo = AAIManager::FindPathToTile(Owner->CurrentTile, Plants);
		}
	}

	if(MovesToDo.IsEmpty())
		return;
	
	if(!Owner->Move(MovesToDo.Pop(false)))
	{
		MovesToDo.Empty();
	}
}


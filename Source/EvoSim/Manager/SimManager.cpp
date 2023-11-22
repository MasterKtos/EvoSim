// Fill out your copyright notice in the Description page of Project Settings.


#include "SimManager.h"

#include "EvoSimLifetimeInterface.h"
#include "EvoSim/AI/Pathfinding/AIManager.h"
#include "EvoSim/Map/MapManager.h"


void USimManager::Init()
{
	Super::Init();
	AIManager = NewObject<AAIManager>(GetOuter(), TEXT("AIManager"));
	AIManager->AddToRoot();
}

void USimManager::Tick()
{
	MapManager->UpdateTiles();

	if(!ManagersToRemove.IsEmpty())
	{
		for (int i = 0; i < ManagersToRemove.Num(); i++)
		{
			int FoundIndex = INDEX_NONE;
			if(!Managers.Find(ManagersToRemove[i], FoundIndex))
				continue;

			Managers.RemoveAt(FoundIndex);
		}
		ManagersToRemove.Empty();
	}

	if(!ManagersToAdd.IsEmpty())
	{
		for (int i = 0; i < ManagersToAdd.Num(); i++)
		{
			Managers.Add(ManagersToAdd[i]);
		}
		ManagersToAdd.Empty();
	}
	
	for (TScriptInterface<IEvoSimLifetime> Manager : Managers)
	{
		if(Manager != nullptr && ensureAlways(Manager))
			Manager->Update();
	}

	StartSimulation();
	CollectGarbage(RF_Standalone);
}

void USimManager::AddMapManager(AMapManager* NewMapManager)
{
	MapManager = NewMapManager;
}

void USimManager::AddToUpdate(TScriptInterface<IEvoSimLifetime> Manager)
{
	ManagersToAdd.Add(Manager);
}

void USimManager::RemoveFromUpdate(TScriptInterface<IEvoSimLifetime> Manager)
{
	ManagersToRemove.Add(Manager);
}

void USimManager::StartSimulation()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USimManager::Tick, TickRate, false);
}

void USimManager::StopSimulation()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

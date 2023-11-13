// Fill out your copyright notice in the Description page of Project Settings.


#include "SimManager.h"

#include "EvoSimLifetimeInterface.h"
#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Map/MapManager.h"


void USimManager::Tick()
{
	MapManager->UpdateTiles();

	if(!Managers.IsEmpty())
	{
		for (int i = 0; i < ManagersToRemove.Num(); i++)
		{
			int FoundIndex = INDEX_NONE;
			if(!Managers.Find(ManagersToRemove[i], FoundIndex))
				continue;

			Managers.RemoveAt(FoundIndex);
			ManagersToRemove.RemoveAt(i);

		}
		ManagersToRemove.Empty();
	}
	
	for (TScriptInterface<IEvoSimLifetime> Manager : Managers)
	{
		if(Manager != nullptr && ensureAlways(Manager))
			Manager->Update();
	}
	
	StartSimulation();
}

void USimManager::AddMapManager(AMapManager* NewMapManager)
{
	MapManager = NewMapManager;
}

void USimManager::AddToUpdate(TScriptInterface<IEvoSimLifetime> Manager)
{
	Managers.Add(Manager);
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

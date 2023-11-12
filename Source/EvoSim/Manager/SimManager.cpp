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
			if(Managers.Find(ManagersToRemove[i]) == INDEX_NONE)
			{
				Cast<UAIComponent>(ManagersToRemove[i])->GetOwner()->Destroy();
				continue;
			}

			const auto Index = Managers.Find(ManagersToRemove[i]);
			Cast<UAIComponent>(Managers[Index])->GetOwner()->Destroy();
			Managers[Index] = nullptr;

		}
		ManagersToRemove.Empty();
	}
	
	for (IEvoSimLifetime* Manager : Managers)
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

void USimManager::AddToUpdate(IEvoSimLifetime* Manager)
{
	Managers.SetNum(20);
	for(int Index = 0; Index <= 20; Index++)
	{
		if(Managers[Index] != nullptr)
			continue;

		Managers[Index] = Manager;
		return;
	}
	Managers.Add(Manager);
}

void USimManager::RemoveFromUpdate(IEvoSimLifetime* Manager)
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

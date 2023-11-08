// Fill out your copyright notice in the Description page of Project Settings.


#include "SimManager.h"

#include "EvoSimLifetimeInterface.h"


void USimManager::Tick()
{
	for (IEvoSimLifetime* Manager : Managers)
	{
		Manager->Update();
	}
	
	for (int i = 0; i < ManagersToRemove.Num(); ++i)
	{
		if(!Managers.Find(ManagersToRemove[i]))
			continue;

		Managers.Remove(ManagersToRemove[i]);
		ManagersToRemove.RemoveAt(i);
	}
	
	StartSimulation();
}

void USimManager::AddToUpdate(IEvoSimLifetime* Manager)
{
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

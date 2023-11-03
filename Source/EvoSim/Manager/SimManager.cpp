// Fill out your copyright notice in the Description page of Project Settings.


#include "SimManager.h"

#include "EvoSimLifetimeInterface.h"


void USimManager::Tick()
{
	for (IEvoSimLifetime* Manager : Managers)
	{
		Manager->Update();
	}
	
	StartSimulation();
}

void USimManager::AddToUpdate(IEvoSimLifetime* Manager)
{
	Managers.Add(Manager);
}

void USimManager::RemoveFromUpdate(IEvoSimLifetime* Manager)
{
	Managers.Remove(Manager);
}

void USimManager::StartSimulation()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USimManager::Tick, TickRate, false);
}

void USimManager::StopSimulation()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

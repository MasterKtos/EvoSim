// Fill out your copyright notice in the Description page of Project Settings.


#include "SimManager.h"

#include "ManagerInterface.h"

void USimManager::Init()
{
	Super::Init();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USimManager::Tick, 1.0f, true, 1.0f);
}

void USimManager::Shutdown()
{
	Super::Shutdown();
	
	if (TimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void USimManager::Tick()
{
	for (IManagerInterface* Manager : Managers)
	{
		Manager->Update();
	}
}

void USimManager::AddToUpdate(IManagerInterface* Manager)
{
	Managers.Add(Manager);
}

void USimManager::RemoveFromUpdate(IManagerInterface* Manager)
{
	Managers.Remove(Manager);
}
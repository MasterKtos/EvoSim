// Fill out your copyright notice in the Description page of Project Settings.


#include "SimManager.h"

#include "ManagerInterface.h"


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

void USimManager::StartSimulation()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USimManager::Tick, 1.0f, true, 1.0f);
}

void USimManager::PauseSimulation()
{
	GetWorld()->GetTimerManager().PauseTimer(TimerHandle);
}

void USimManager::ContinueSimulation()
{
	GetWorld()->GetTimerManager().UnPauseTimer(TimerHandle);
}


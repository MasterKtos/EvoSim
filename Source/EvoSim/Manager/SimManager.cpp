// Fill out your copyright notice in the Description page of Project Settings.


#include "SimManager.h"

#include "EvoSimLifetimeInterface.h"


void USimManager::Tick()
{
	if(IsTickOngoing)
		return;

	IsTickOngoing = true;

	for (IEvoSimLifetime* Manager : Managers)
	{
		Manager->Update();
	}
	
	IsTickOngoing = false;
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
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &USimManager::Tick, 0.6f, true, .1f);
}

void USimManager::PauseSimulation()
{
	GetWorld()->GetTimerManager().PauseTimer(TimerHandle);
}

void USimManager::ContinueSimulation()
{
	GetWorld()->GetTimerManager().UnPauseTimer(TimerHandle);
}


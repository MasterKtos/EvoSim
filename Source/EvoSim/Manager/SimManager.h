// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SimManager.generated.h"

class IEvoSimLifetime;

UCLASS()
class EVOSIM_API USimManager : public UGameInstance
{
	GENERATED_BODY()

	FTSTicker::FDelegateHandle TickDelegateHandle;
	
	TArray<IEvoSimLifetime*> Managers;
	
	FTimerHandle TimerHandle;

	void Tick();

public:
	void AddToUpdate(IEvoSimLifetime* Manager);

	void RemoveFromUpdate(IEvoSimLifetime* Manager);

	UFUNCTION(BlueprintCallable)
	void StartSimulation();
	UFUNCTION(BlueprintCallable)
	void StopSimulation();

	UPROPERTY(BlueprintReadWrite)
	float TickRate = 1.f;

private:
	bool IsTickOngoing = false;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SimManager.generated.h"

class IManagerInterface;

UCLASS()
class EVOSIM_API USimManager : public UGameInstance
{
	GENERATED_BODY()

	FTSTicker::FDelegateHandle TickDelegateHandle;
	
	TArray<IManagerInterface*> Managers;
	
	FTimerHandle TimerHandle;

	void Tick();

public:
	void AddToUpdate(IManagerInterface* Manager);

	void RemoveFromUpdate(IManagerInterface* Manager);

	UFUNCTION(BlueprintCallable)
	void StartSimulation();
	UFUNCTION(BlueprintCallable)
	void PauseSimulation();
	UFUNCTION(BlueprintCallable)
	void ContinueSimulation();
};

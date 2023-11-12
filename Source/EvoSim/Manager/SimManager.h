// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SimManager.generated.h"

class AMapManager;
class IEvoSimLifetime;

UCLASS()
class EVOSIM_API USimManager : public UGameInstance
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<IEvoSimLifetime*> Managers;
	UPROPERTY()
	TArray<IEvoSimLifetime*> ManagersToRemove;

	UPROPERTY()
	FTimerHandle TimerHandle;

	void Tick();

	UPROPERTY()
	AMapManager* MapManager = nullptr;

public:
	UFUNCTION()
	void AddMapManager(AMapManager* NewMapManager);
	void AddToUpdate(IEvoSimLifetime* Manager);
	void RemoveFromUpdate(IEvoSimLifetime* Manager);

	UFUNCTION(BlueprintCallable)
	void StartSimulation();
	UFUNCTION(BlueprintCallable)
	void StopSimulation();

	UPROPERTY(BlueprintReadWrite)
	float TickRate = 1.f;


	// Values set in menu
	UPROPERTY(BlueprintReadWrite)
	int HerbCreaturesToSpawn = 100;
	UPROPERTY(BlueprintReadWrite)
	int MeatCreaturesToSpawn = 100;
	UPROPERTY(BlueprintReadWrite)
	float HerbSpeed = 1;
	UPROPERTY(BlueprintReadWrite)
	float MeatSpeed = 1;
	UPROPERTY(BlueprintReadWrite)
	int FOV = 270;
	UPROPERTY(BlueprintReadWrite)
	int ViewDistance = 7;
	UPROPERTY(BlueprintReadWrite)
	int PlantDurability = 1;

private:
	UPROPERTY()
	bool IsTickOngoing = false;
};

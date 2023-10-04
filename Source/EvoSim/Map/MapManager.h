// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapManager.generated.h"

class ATile;

USTRUCT()
struct FInitialParameters
{
	GENERATED_BODY()

	TArray<ATile> InitialMap;
};

UCLASS()
class EVOSIM_API AMapManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapManager();

	UFUNCTION()
	void GenerateMap(FInitialParameters Parameters);
	UFUNCTION()
	void UpdateTiles();
	
	UPROPERTY()
	TArray<ATile*> Tiles;
};

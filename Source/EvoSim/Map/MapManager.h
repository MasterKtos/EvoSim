// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapManager.generated.h"

class ATilePlant;
enum class ETileType : uint8;
class ATile;

USTRUCT(Blueprintable)
struct FInitialParameters
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<ETileType> InitialMap = {};
	UPROPERTY(BlueprintReadWrite)
	int InitialMapRowNum = 0;
};

UCLASS()
class EVOSIM_API AMapManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapManager();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ATile* SetNewTarget(ATile* From);
	
	UFUNCTION(BlueprintCallable)
	void GenerateMap(const FInitialParameters& Parameters);
	UFUNCTION(BlueprintCallable)
	void UpdateTiles();

	UFUNCTION(BlueprintCallable)
	int MapCoordsToIndex(int CoordX, int CoordY) const;
	UFUNCTION(BlueprintCallable)
	ATile* GetTileFromCoords(int CoordX, int CoordY);

	UPROPERTY(BlueprintReadWrite)
	TArray<ATile*> Tiles = {};
	UPROPERTY(BlueprintReadWrite)
	int TilesRowSize = 0;

protected:
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<ATile> TilePrefab;
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<ATilePlant> TilePlantPrefab;
	UPROPERTY(BlueprintReadWrite)
	TSubclassOf<ATilePlant> TileObstaclePrefab;
};

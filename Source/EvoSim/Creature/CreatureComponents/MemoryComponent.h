// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EvoSim/Map/Tile.h"
#include "MemoryComponent.generated.h"

#define NO_VALUE -1
#define	TIME_TO_REMEMBER 30

USTRUCT()
struct FTileMemory
{
	GENERATED_BODY()

	int Turns;
	UPROPERTY()
	ATile* Tile;
}; 

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EVOSIM_API UMemoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMemoryComponent();

	virtual void BeginPlay() override;
	
	void RememberTile(ATile* Tile);

	// Obstacle will never be remembered, so it's equal to null/none
	TArray<ATile*> GetRememberedTiles(ETileType TileType1 = ETileType::Obstacle, ETileType TileType2 = ETileType::Obstacle);
	
	void CheckTilesToForget();

private:
	UPROPERTY()
	TArray<FTileMemory> TilesToRemember;
};

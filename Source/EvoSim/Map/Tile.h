// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM()
enum class ETileType
{
	Water, Obstacle,
    Land, Plant
};

UENUM()
enum class EDirection
{
	N, NE,
	E, SE,
	S, SW,
	W, NW
};

UCLASS()
class EVOSIM_API ATile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATile();

	UPROPERTY()
    ETileType Type = ETileType::Water;
	UPROPERTY()
    FVector2D Coords = {0, 0};
	UFUNCTION()
    ATile* GetNeighbour(EDirection Direction) const;
	
protected:
	UPROPERTY()
	ATile* Left = nullptr;
	UPROPERTY()
	ATile* Right = nullptr;
	UPROPERTY()	
	ATile* Up = nullptr;
	UPROPERTY()
	ATile* Down = nullptr;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UENUM(Blueprintable)
enum class ETileType : uint8
{
	Water, Obstacle,
    Land, Plant
};

UENUM(Blueprintable)
enum class EDirection : uint8
{
	N, NE,
	E, SE,
	S, SW,
	W, NW
};

ENUM_RANGE_BY_FIRST_AND_LAST(EDirection, EDirection::N, EDirection::NW);

UCLASS()
class EVOSIM_API ATile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATile();

	UPROPERTY(BlueprintReadWrite)
    ETileType Type = ETileType::Water;
	UPROPERTY(BlueprintReadWrite)
    FVector2D Coords = {0, 0};
	UFUNCTION(BlueprintCallable)
    ATile* GetNeighbour(EDirection Direction) const;
	UFUNCTION(BlueprintCallable)
	virtual void Update();
	
	UFUNCTION()
	void SetNeighbours(ATile* UpTile, ATile* DownTile, ATile* LeftTile, ATile* RightTile);
	UFUNCTION(BlueprintNativeEvent)
	void SetTileType(ETileType NewType);
	
protected:
	UPROPERTY(BlueprintReadWrite)
	ATile* Left = nullptr;
	UPROPERTY(BlueprintReadWrite)
	ATile* Right = nullptr;
	UPROPERTY(BlueprintReadWrite)
	ATile* Up = nullptr;
	UPROPERTY(BlueprintReadWrite)
	ATile* Down = nullptr;
};

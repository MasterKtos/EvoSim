// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Creature.generated.h"

enum class EDirection : uint8;
class UAIComponent;
class USphereComponent;
class UCreatureMovementComponent;
class UFovComponent;
class AMapManager;
class ATile;

UCLASS()
class EVOSIM_API ACreature : public AActor
{
	GENERATED_BODY()
	
public:	
	ACreature();
	
	UPROPERTY(BlueprintReadWrite)
	AMapManager* MapManager;

	UPROPERTY(BlueprintReadWrite)
	float FieldOfView = 0;
	UPROPERTY(BlueprintReadWrite)
	float ViewDistance = 0;
	UPROPERTY(BlueprintReadWrite)
	float Speed = 0;

	UPROPERTY(BlueprintReadWrite)
	int Hunger = 0;	
	UPROPERTY(BlueprintReadWrite)
	int Thirst = 0;
	UPROPERTY(BlueprintReadWrite)
	int Randy = 0;

	UPROPERTY(BlueprintReadOnly)
	bool bHerbivorous = true;
	
	UPROPERTY()
	int DrinkPerUpdate = 10;
	UPROPERTY()
	int EatPerUpdate = 30;

	UPROPERTY()
	int TurnsToReproduce = 3;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	ATile* CurrentTile = nullptr;
	
	bool Move(EDirection Direction);

	UPROPERTY()
	UFovComponent* FovComponent;
	UPROPERTY()
	UCreatureMovementComponent* MovementComponent;
	UPROPERTY(BlueprintReadOnly)
	UAIComponent* AIComponent;
	UPROPERTY(BlueprintReadWrite)
	USphereComponent* FovSphereComponent;
};

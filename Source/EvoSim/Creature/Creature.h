// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvoSim/AI/AIComponent.h"
#include "GameFramework/Actor.h"
#include "Creature.generated.h"

class UAIComponent;
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

public:
	UPROPERTY(BlueprintReadWrite)
	AMapManager* MapManager;

	UPROPERTY(BlueprintReadWrite)
	float FieldOfView = 0;
	UPROPERTY(BlueprintReadWrite)
	float ViewDistance = 0;
	UPROPERTY(BlueprintReadWrite)
	float Speed = 0;

	UPROPERTY()
	int Hunger = 0;	
	UPROPERTY()
	int Thirst = 0;
	
	UPROPERTY(BlueprintReadWrite)
	ATile* CurrentTile = nullptr;
	
protected:
	virtual void BeginPlay() override;

public:
	bool Move(EDirection Direction);

	UPROPERTY()
	UFovComponent* FovComponent;
	UPROPERTY()
	UCreatureMovementComponent* MovementComponent;
	
private:
	UPROPERTY()
	UAIComponent* AIComponent;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Creature.generated.h"

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

	float FieldOfView = 0;
	float ViewDistance = 0;

protected:
	virtual void BeginPlay() override;

	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;
	
	UPROPERTY(BlueprintReadWrite)
	ATile* CurrentTile;

	UPROPERTY(BlueprintReadWrite)
	float Speed = 0;

private:
	UPROPERTY();
	UFovComponent* FovComponent;
};

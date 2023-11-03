// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "TilePlant.generated.h"

UCLASS()
class EVOSIM_API ATilePlant : public ATile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATilePlant();
	
	virtual void Update() override;

	UFUNCTION(BlueprintCallable)
	void Eat();

	UPROPERTY(BlueprintReadWrite)
	int MaxDurability = 1;

	UPROPERTY(VisibleAnywhere)
	int Durability = 1;
	
protected:
	UFUNCTION(BlueprintCallable)
	void RegrowPlant();
	
	UPROPERTY(BlueprintReadWrite)
	USceneComponent* PlantMeshComponent;
	UPROPERTY(BlueprintReadWrite)
	int TimeToReset = 3;
	UPROPERTY()
	int TimeToResetCounter = 0;
};

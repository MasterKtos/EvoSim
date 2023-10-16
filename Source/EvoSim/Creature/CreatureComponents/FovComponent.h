// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FovComponent.generated.h"

class AMapManager;
class ATile;
class ACreature;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVOSIM_API UFovComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFovComponent();
	
	UFUNCTION(BlueprintCallable)
	void UpdateTilesInSight();
	
	UFUNCTION(BlueprintCallable)
	const TArray<ATile*>& GetWaterTilesInSight() const;
	UFUNCTION(BlueprintCallable)
	const TArray<ATile*>& GetPlantTilesInSight() const;
	UFUNCTION(BlueprintCallable)
	const TArray<ATile*>& GetMeatInSight() const;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	ACreature* Owner = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TArray<ATile*> WaterTiles;
	UPROPERTY(BlueprintReadWrite)
	TArray<ATile*> PlantTiles;
	UPROPERTY(BlueprintReadWrite)
	TArray<ATile*> MeatTiles;
};

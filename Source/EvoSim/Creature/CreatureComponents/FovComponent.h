// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureComponent.h"
#include "FovComponent.generated.h"

class ACreature;
class ACarnivorous;
class AHerbivorous;
class AMapManager;
class ATile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVOSIM_API UFovComponent : public UCreatureComponent
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
	const TArray<ATile*>& GetHerbCreaturesTilesInSight() const;
	UFUNCTION(BlueprintCallable)
	const TArray<ATile*>& GetMeatCreaturesTilesInSight() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TArray<ATile*> WaterTiles;
	UPROPERTY()
	TArray<ATile*> PlantTiles;
	UPROPERTY()
	TArray<ATile*> HerbCreaturesTilesInSight;
	UPROPERTY()
	TArray<ATile*> MeatCreaturesTilesInSight;

private:
	UFUNCTION()
	TArray<AActor*> GetOverlappingActors(UClass* ActorsOfClass) const;

	UPROPERTY()
	TArray<AActor*> IgnoredActors;

	UPROPERTY()
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
};

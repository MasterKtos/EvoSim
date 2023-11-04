// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FovComponent.generated.h"

class ACreature;
class ACarnivorous;
class AHerbivorous;
class AMapManager;
class ATile;

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
	const TArray<AHerbivorous*>& GetHerbCreaturesInSight() const;
	UFUNCTION(BlueprintCallable)
	const TArray<ACarnivorous*>& GetMeatCreaturesInSight() const;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	ACreature* Owner = nullptr;

	UPROPERTY()
	TArray<ATile*> WaterTiles;
	UPROPERTY()
	TArray<ATile*> PlantTiles;
	UPROPERTY()
	TArray<AHerbivorous*> HerbCreaturesInSight;
	UPROPERTY()
	TArray<ACarnivorous*> MeatCreaturesInSight;

private:
	TArray<AActor*> GetOverlappingActors(UClass* ActorsOfClass) const;

	UPROPERTY()
	TArray<AActor*> IgnoredActors;
	
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
};

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

protected:
	virtual void BeginPlay() override;

public:
	void UpdateTilesInSight();

private:
	UPROPERTY()
	ACreature* Owner = nullptr;

	TArray<ATile*> WaterTiles;
	TArray<ATile*> PlantTiles;
	TArray<ATile*> MeatTiles;

public:
	[[nodiscard]] const TArray<ATile*>& GetWaterTilesInSight() const;

	[[nodiscard]] const TArray<ATile*>& GetPlantTilesInSight() const;

	[[nodiscard]] const TArray<ATile*>& GetMeatInSight() const;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvoSim/Manager/EvoSimLifetimeInterface.h"
#include "GameFramework/Actor.h"
#include "Corpse.generated.h"

class ATile;
class USimManager;

UCLASS()
class EVOSIM_API ACorpse : public AActor, public IEvoSimLifetime
{
	GENERATED_BODY()

public:
	ACorpse();

	virtual void Update() override;

	bool Eat();

	UPROPERTY()
	UStaticMeshComponent* SphereMesh;
	UPROPERTY()
	ATile* CurrentTile;
	
protected:
	virtual void BeginPlay() override;

	int Lifetime = 30;
	int Durability = 1;

	UPROPERTY()
	USimManager* GameInstance = nullptr;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvoSim/Manager/EvoSimLifetimeInterface.h"
#include "GameFramework/Actor.h"
#include "Corpse.generated.h"

class USimManager;

UCLASS()
class EVOSIM_API ACorpse : public AActor, public IEvoSimLifetime
{
	GENERATED_BODY()

public:
	ACorpse();

	virtual void Update() override;

	void BeEaten();

	UPROPERTY()
	UStaticMeshComponent* SphereMesh;
	
protected:
	virtual void BeginPlay() override;

private:
	int Lifetime = 30;
	int Durability = 1;

	UPROPERTY()
	USimManager* GameInstance = nullptr;
};

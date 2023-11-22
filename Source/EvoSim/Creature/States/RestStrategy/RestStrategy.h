// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvoSim/Creature/CreatureComponents/CreatureComponent.h"
#include "UObject/Object.h"
#include "RestStrategy.generated.h"

UENUM()
enum class ERestStrategyName
{
	None, Random, CloseToBros, AwayFromBros
};

UCLASS()
class EVOSIM_API URestStrategy : public UCreatureComponent
{
	GENERATED_BODY()

public:
	UFUNCTION()
	void SetStrategy(ERestStrategyName Name);
	
	UFUNCTION()
	void ApplyMovement() const;

private:
	ERestStrategyName StrategyName = ERestStrategyName::None;
	
	void RandomMovement() const;
	void CloseToBrosMovement() const;
	void AwayFromBrosMovement() const;
};

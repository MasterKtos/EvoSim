// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvoSim/Creature/States/CreatureStateEat.h"
#include "HerbivoreStateEat.generated.h"

/**
 * 
 */
UCLASS()
class EVOSIM_API UHerbivoreStateEat : public UCreatureStateEat
{
	GENERATED_BODY()
public:
	virtual bool TryEnterState(const ECreatureStateName FromState) override;
	virtual void Update() override;
};

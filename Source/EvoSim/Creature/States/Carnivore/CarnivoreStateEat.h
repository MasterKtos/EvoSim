// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvoSim/Creature/States/CreatureStateEat.h"
#include "CarnivoreStateEat.generated.h"

/**
 * 
 */
UCLASS()
class EVOSIM_API UCarnivoreStateEat : public UCreatureStateEat
{
	GENERATED_BODY()
public:
	
	virtual bool TryExitState() override;
	virtual void Update() override;
};

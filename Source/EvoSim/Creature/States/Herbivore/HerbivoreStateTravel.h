// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvoSim/Creature/States/CreatureStateTravel.h"
#include "HerbivoreStateTravel.generated.h"

/**
 * 
 */
UCLASS()
class EVOSIM_API UHerbivoreStateTravel : public UCreatureStateTravel
{
	GENERATED_BODY()

protected:
	virtual void GetTargetsInView() override;
};

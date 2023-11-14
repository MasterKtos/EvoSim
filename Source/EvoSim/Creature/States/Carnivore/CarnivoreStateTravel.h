﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvoSim/Creature/States/CreatureStateTravel.h"
#include "CarnivoreStateTravel.generated.h"

enum class EDirection : uint8;
/**
 * 
 */
UCLASS()
class EVOSIM_API UCarnivoreStateTravel : public UCreatureStateTravel
{
	GENERATED_BODY()
	
public:
	virtual bool TryEnterState(const ECreatureStateName FromState) override;
	virtual bool TryExitState() override;
	virtual void Update() override;
};
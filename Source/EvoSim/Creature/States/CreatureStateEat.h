﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureState.h"
#include "CreatureStateEat.generated.h"

/**
 * 
 */
UCLASS()
class EVOSIM_API UCreatureStateEat : public UCreatureState
{
	GENERATED_BODY()

public:
	virtual bool TryEnterState(const ECreatureStateName FromState) override;

	virtual bool TryExitState() override;

	virtual void Update() override;
	
	static constexpr ECreatureStateName StateName = ECreatureStateName::Eat;

};

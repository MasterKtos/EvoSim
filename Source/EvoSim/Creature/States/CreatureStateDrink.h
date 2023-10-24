// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureState.h"
#include "CreatureStateDrink.generated.h"

/**
 * 
 */
UCLASS()
class EVOSIM_API UCreatureStateDrink : public UCreatureState
{
	GENERATED_BODY()

public:
	UCreatureStateDrink();

	virtual bool TryEnterState(const ECreatureStateName FromState) override;
	virtual bool TryExitState() override;
	virtual void Update() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureState.h"
#include "CarnivoreStateEat.generated.h"

/**
 * 
 */
UCLASS()
class EVOSIM_API UCarnivoreStateEat : public UCreatureState
{
	GENERATED_BODY()
public:
	UCarnivoreStateEat();

	virtual bool TryEnterState(const ECreatureStateName FromState) override;
	virtual bool TryExitState() override;
	virtual void Update() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureState.h"
#include "CreatureStateReproduce.generated.h"

/**
 * 
 */
UCLASS()
class EVOSIM_API UCreatureStateReproduce : public UCreatureState
{
	GENERATED_BODY()

public:
	UCreatureStateReproduce();

	virtual bool TryEnterState(const ECreatureStateName FromState) override;
	virtual bool TryExitState() override;
	virtual void Update() override;
	
private:
	int CurrentTurn = 0;
};

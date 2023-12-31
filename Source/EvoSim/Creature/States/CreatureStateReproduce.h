﻿// Fill out your copyright notice in the Description page of Project Settings.

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
	virtual void ForceEnterState(ACreature* ForcedBy = nullptr) override;
	virtual bool TryExitState() override;
	virtual void Update() override;
	
private:
	UPROPERTY()
	ACreature* Partner = nullptr;
	
	UPROPERTY()
	int CurrentTurn = 0;
	
	bool bMother = true;
};

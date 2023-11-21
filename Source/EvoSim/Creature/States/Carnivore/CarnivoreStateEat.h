// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvoSim/Creature/States/CreatureStateEat.h"
#include "CarnivoreStateEat.generated.h"

class ACorpse;
/**
 * 
 */
UCLASS()
class EVOSIM_API UCarnivoreStateEat : public UCreatureStateEat
{
	GENERATED_BODY()
public:
	virtual bool TryEnterState(const ECreatureStateName FromState) override;
	virtual bool TryExitState() override;
	virtual void Update() override;

private:
	UPROPERTY()
	ACorpse* Prey;
};

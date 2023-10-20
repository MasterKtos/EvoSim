// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "EvoSim/Manager/EvoSimLifetimeInterface.h"
#include "CreatureState.generated.h"

class ACreature;

UENUM()
enum class ECreatureStateName
{
	Rest, Eat,
	Drink, Travel,
	Reproduce
};

UCLASS()
class UCreatureState : public UObject, public IEvoSimLifetime
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual bool TryEnterState(const ECreatureStateName FromState) { return false; }

	UFUNCTION()
	virtual bool TryExitState() { return false; }

	virtual void Update() override { TryExitState(); }
	
	static constexpr ECreatureStateName StateName = ECreatureStateName::Rest;

	UPROPERTY()
	ACreature* Owner;
};

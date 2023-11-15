// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "EvoSim/Manager/EvoSimLifetimeInterface.h"
#include "CreatureState.generated.h"

class ACreature;

UENUM()
enum class ECreatureStateName : uint8
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
	virtual void ForceEnterState(ACreature* ForcedBy = nullptr) { }

	UFUNCTION()
	virtual bool TryExitState() { return false; }

	virtual void Update() override { TryExitState(); }

	UPROPERTY(BlueprintReadOnly)
	ECreatureStateName StateName = ECreatureStateName::Rest;

	UPROPERTY()
	ACreature* Owner;
};

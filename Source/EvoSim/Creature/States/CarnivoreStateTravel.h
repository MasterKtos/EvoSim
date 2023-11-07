// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureState.h"
#include "CarnivoreStateTravel.generated.h"

enum class EDirection : uint8;
/**
 * 
 */
UCLASS()
class EVOSIM_API UCarnivoreStateTravel : public UCreatureState
{
	GENERATED_BODY()
public:
	UCarnivoreStateTravel();

	virtual bool TryEnterState(const ECreatureStateName FromState) override;
	virtual bool TryExitState() override;
	virtual void Update() override;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<EDirection> MovesToDo;
};

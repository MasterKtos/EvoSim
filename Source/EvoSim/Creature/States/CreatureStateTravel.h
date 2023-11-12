// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureState.h"
#include "CreatureStateTravel.generated.h"

enum class EDirection : uint8;
/**
 * 
 */
UCLASS()
class EVOSIM_API UCreatureStateTravel : public UCreatureState
{
	GENERATED_BODY()

public:
	UCreatureStateTravel();

	virtual bool TryEnterState(const ECreatureStateName FromState) override;
	virtual bool TryExitState() override;
	virtual void Update() override;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<EDirection> MovesToDo;

private:
	UFUNCTION()
	void GetPathForCurrentNeed();
	UFUNCTION()
	bool TryToSatisfyNeeds() const;
};

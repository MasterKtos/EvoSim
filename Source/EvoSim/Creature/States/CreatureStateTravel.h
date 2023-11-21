// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureState.h"
#include "CreatureStateTravel.generated.h"

class ATile;
enum class ECreatureNeed;
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
	UPROPERTY()
	ECreatureNeed TargetedNeed;

protected:
	UFUNCTION()
	virtual void GetPathForCurrentNeed();
	// Populates Food, Water and Bros arrays
	UFUNCTION()
	virtual void GetTargetsInView();
	
	UFUNCTION()
	bool TryToSatisfyNeeds() const;
	
	UPROPERTY()
	TArray<ATile*> Food;
	UPROPERTY()
	TArray<ATile*> Water;
	UPROPERTY()
	TArray<ATile*> Bros;
};

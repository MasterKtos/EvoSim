// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureComponent.h"
#include "CreatureMovementComponent.generated.h"

class USimManager;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVOSIM_API UCreatureMovementComponent : public UCreatureComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCreatureMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void SetNewTarget(const FVector& NewTarget);

private:
	UFUNCTION()
	bool IsAtTarget() const;
	
	UPROPERTY()
	USimManager* SimManager;

	UPROPERTY()
	bool bSliding = false;
	UPROPERTY()
	FVector Target = FVector::Zero();
};

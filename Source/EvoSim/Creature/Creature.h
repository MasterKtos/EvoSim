// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "States/RestStrategy/RestStrategy.h"
#include "Creature.generated.h"

class URestStrategy;
class UMemoryComponent;
class UNeedsEvaluatorComponent;
enum class EDirection : uint8;
class UAIComponent;
class USphereComponent;
class UCreatureMovementComponent;
class UFovComponent;
class AMapManager;
class ATile;

UCLASS()
class EVOSIM_API ACreature : public AActor
{
	GENERATED_BODY()
	
public:	
	ACreature();

	UFUNCTION()
	bool Move(EDirection Direction);
	
	UFUNCTION()
	void ApplyRestMovement() const;

	UFUNCTION()
	virtual void Die();

	UFUNCTION(BlueprintCallable)
	virtual void Reproduce(bool bMother, ACreature* Partner = nullptr);

	UFUNCTION()
	virtual ACreature* IsInDanger();
	UFUNCTION()
	virtual void RunAway(const ACreature* Foe);

	UPROPERTY(BlueprintReadWrite)
	AMapManager* MapManager;
	
	// Those 3 can mutate and change
	UPROPERTY(BlueprintReadWrite)
	float FieldOfView = 0;
	UPROPERTY(BlueprintReadWrite)
	float ViewDistance = 0;
	UPROPERTY(BlueprintReadWrite)
	float Speed = 0;
	UPROPERTY()
	URestStrategy* RestStrategy;
	// -----------------------------

	UPROPERTY(BlueprintReadWrite)
	int Hunger = 0;	
	UPROPERTY(BlueprintReadWrite)
	int Thirst = 0;
	UPROPERTY(BlueprintReadWrite)
	int Randy = 0;
	
	UPROPERTY()
	int DrinkPerUpdate = 10;
	UPROPERTY()
	int EatPerUpdate = 30;

	UPROPERTY()
	int TurnsToReproduce = 3;

	UPROPERTY()
	int HungerPerReproduction = 30;
	UPROPERTY()
	int ThirstPerReproduction = 30;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	ATile* CurrentTile = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UFovComponent* FovComponent;
	UPROPERTY(BlueprintReadOnly)
	UCreatureMovementComponent* MovementComponent;
	UPROPERTY(BlueprintReadOnly)
	USphereComponent* FovSphereComponent;
	UPROPERTY(BlueprintReadOnly)
	UAIComponent* AIComponent;
	UPROPERTY(BlueprintReadOnly)
	UNeedsEvaluatorComponent* NeedsEvaluator;
	UPROPERTY(BlueprintReadOnly)
	UMemoryComponent* MemoryComponent;

protected:
	static ERestStrategyName MutateStrategy(ERestStrategyName Parent1, ERestStrategyName Parent2);
	
	template< class T >
	static FORCEINLINE T MutateFeature(T Value1, T Value2, T MinValue, T MaxValue, T MaxMutationRange)
	{
		T Range = 1;
		const float MutationRate = FMath::RandRange(-Range, Range) * MaxMutationRange;
		const float FinalValue = (Value1 + Value2) * 0.5f + MutationRate;

		if(FinalValue < MinValue)
			return MinValue;
		if(FinalValue > MaxValue)
			return MaxValue;
	
		return FinalValue;
	}
};

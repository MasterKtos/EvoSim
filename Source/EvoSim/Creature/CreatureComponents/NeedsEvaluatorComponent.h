// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureComponent.h"
#include "NeedsEvaluatorComponent.generated.h"

UENUM()
enum class ECreatureNeed
{
	Satisfied = 0x0,
	Eat = 0x1,
	Drink = 0x2,
	DrinkOrEat = (Eat | Drink),
	Reproduce = 0x4
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EVOSIM_API UNeedsEvaluatorComponent : public UCreatureComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UNeedsEvaluatorComponent();

	ECreatureNeed GetCurrentNeed() const;
	bool IsCurrentNeed(ECreatureNeed Need) const;
};

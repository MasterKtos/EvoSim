// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CreatureComponent.h"
#include "NeedsEvaluatorComponent.generated.h"

UENUM()
enum class ECreatureNeed
{
	Satisfied, Eat, Drink, Reproduce
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EVOSIM_API UNeedsEvaluatorComponent : public UCreatureComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UNeedsEvaluatorComponent();

	ECreatureNeed GetCurrentNeed() const;
};

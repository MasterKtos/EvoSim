// Fill out your copyright notice in the Description page of Project Settings.


#include "NeedsEvaluatorComponent.h"

#include "EvoSim/Creature/Creature.h"


// Sets default values for this component's properties
UNeedsEvaluatorComponent::UNeedsEvaluatorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

ECreatureNeed UNeedsEvaluatorComponent::GetCurrentNeed() const
{
	const int Thirst = Owner->Thirst;
	const int Hunger = Owner->Hunger;
	const int Randy = Owner->Randy;
	const int MaxNeed = Owner->Thirst > Owner->Hunger ? Owner->Thirst : Owner->Hunger;

	if(MaxNeed < 30)
	{
		return (Randy>=100 ? ECreatureNeed::Reproduce : ECreatureNeed::Satisfied);
	}
	if(MaxNeed < 50)
	{
		// if(Randy >= 100)
		// 	return ECreatureNeed::Reproduce;
		return ECreatureNeed::DrinkOrEat;
	}
	return Thirst > Hunger ? ECreatureNeed::Drink : ECreatureNeed::Eat;
}

bool UNeedsEvaluatorComponent::IsCurrentNeed(ECreatureNeed Need) const
{
	if(Need == ECreatureNeed::Satisfied)
		return GetCurrentNeed() == ECreatureNeed::Satisfied;
	return (static_cast<uint8>(GetCurrentNeed()) & static_cast<uint8>(Need)) != 0;
}

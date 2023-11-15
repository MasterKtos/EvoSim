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
	if(Owner->Thirst >= Owner->Hunger || Owner->Thirst > 60)
	{
		return ECreatureNeed::Drink;
	}
	if(Owner->Thirst < Owner->Hunger || Owner->Hunger > 60)
	{
		return ECreatureNeed::Eat;
	}
	if(Owner->Randy == 100)
	{
		return ECreatureNeed::Reproduce;
	}
	
	return ECreatureNeed::Satisfied;
}

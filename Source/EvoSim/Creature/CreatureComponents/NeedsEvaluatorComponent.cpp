// Fill out your copyright notice in the Description page of Project Settings.


#include "NeedsEvaluatorComponent.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Map/Tile.h"


// Sets default values for this component's properties
UNeedsEvaluatorComponent::UNeedsEvaluatorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

ECreatureNeed UNeedsEvaluatorComponent::GetCurrentNeed() const
{
	if(Owner->Thirst >= Owner->Hunger || Owner->Thirst > 80)
	{
		return ECreatureNeed::Drink;
	}
	if(Owner->Thirst < Owner->Hunger || Owner->Hunger > 80)
	{
		return ECreatureNeed::Eat;
	}
	if(Owner->Randy > 80)
		return ECreatureNeed::Reproduce;
	
	return ECreatureNeed::Satisfied;
}

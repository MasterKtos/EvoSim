// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateRest.h"

#include "EvoSim/Creature/Creature.h"

bool UCreatureStateRest::TryEnterState(const ECreatureStateName FromState)
{
	return true;
}

bool UCreatureStateRest::TryExitState()
{
	if(Owner->Thirst > 40)
	{
		// TODO: Set AI target to water
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Travel);
	}
	if(Owner->Hunger > 40)
	{
		// TODO: Set AI target to food
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Travel);
	}
	if(Owner->Randy >= 100)
	{
		// TODO: Set AI target to s3x
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Travel);
	}
	return false;
}

void UCreatureStateRest::Update()
{
	Super::Update();
	// TODO: Move to random tile
	
}

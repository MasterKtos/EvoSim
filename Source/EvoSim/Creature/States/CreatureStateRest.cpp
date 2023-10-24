// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateRest.h"

#include "EvoSim/Creature/Creature.h"

UCreatureStateRest::UCreatureStateRest()
{
	StateName = ECreatureStateName::Rest;
}

bool UCreatureStateRest::TryEnterState(const ECreatureStateName FromState)
{
	return true;
}

bool UCreatureStateRest::TryExitState()
{
	if(Owner->Thirst > 40 || Owner->Hunger > 40 || Owner->Randy >= 100)
	{
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Travel);
	}
	return false;
}

void UCreatureStateRest::Update()
{
	Super::Update();
	// TODO: Move to random tile
}

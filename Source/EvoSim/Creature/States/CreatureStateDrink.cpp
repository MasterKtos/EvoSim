// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateDrink.h"

#include "EvoSim/Creature/Creature.h"

UCreatureStateDrink::UCreatureStateDrink()
{
	StateName = ECreatureStateName::Drink;
}

bool UCreatureStateDrink::TryEnterState(const ECreatureStateName FromState)
{
	return FromState == ECreatureStateName::Travel;
}

bool UCreatureStateDrink::TryExitState()
{
	// TODO: Start searching for food if thirst is not critical

	if(Owner->Thirst <= 40)
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Rest);
	
	return false;
}

void UCreatureStateDrink::Update()
{
	Super::Update();

	if(Owner->Thirst - Owner->DrinkPerUpdate < 0)
	{
		Owner->Thirst = 0;
		return;
	}
	Owner->Thirst -= Owner->DrinkPerUpdate;
}

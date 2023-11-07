// Fill out your copyright notice in the Description page of Project Settings.


#include "CarnivoreStateEat.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Creature.h"

UCarnivoreStateEat::UCarnivoreStateEat()
{
	StateName = ECreatureStateName::Eat;
}

bool UCarnivoreStateEat::TryEnterState(const ECreatureStateName FromState)
{
	return (FromState == ECreatureStateName::Travel || FromState == ECreatureStateName::Rest);
}

bool UCarnivoreStateEat::TryExitState()
{
	// TODO: Start searching for water if hunger is not critical

	if(Owner->Hunger <= 40)
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Rest);

	return false;
}

void UCarnivoreStateEat::Update()
{
	Super::Update();
	
	Owner->Hunger = Owner->EatPerUpdate;
	
	if(Owner->Hunger < 0)
		Owner->Hunger = 0;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateReproduce.h"

#include "EvoSim/Creature/Creature.h"

UCreatureStateReproduce::UCreatureStateReproduce()
{
	StateName = ECreatureStateName::Reproduce;
}

bool UCreatureStateReproduce::TryEnterState(const ECreatureStateName FromState)
{
	if(FromState != ECreatureStateName::Travel)
		return false;
	
	// TODO: Check if can reproduce
	
	CurrentTurn = 0;
	return true;
}

bool UCreatureStateReproduce::TryExitState()
{
	// TODO: Exit if there is danger
	
	if(CurrentTurn >= Owner->TurnsToReproduce)
	{
		// TODO: Create new creature
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Rest);
	}

	return false;
}

void UCreatureStateReproduce::Update()
{
	Super::Update();

	CurrentTurn++;
}

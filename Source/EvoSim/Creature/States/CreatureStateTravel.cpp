// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateTravel.h"

bool UCreatureStateTravel::TryEnterState(const ECreatureStateName FromState)
{
	return true;
}

bool UCreatureStateTravel::TryExitState()
{
	// TODO: Check if reached target
	return false;
}

void UCreatureStateTravel::Update()
{
	Super::Update();
	
	// TODO: Check if creature needs to change target 
	// TODO: Check if there is better way to the target
	// TODO: Travel to next tile in path
}

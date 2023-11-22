// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateRest.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/NeedsEvaluatorComponent.h"

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
	if(!Owner->NeedsEvaluator->IsCurrentNeed(ECreatureNeed::Satisfied))
	{
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Travel);
	}
	return false;
}

void UCreatureStateRest::Update()
{
	Owner->ApplyRestMovement();
	
	Super::Update();
}

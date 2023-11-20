// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateEat.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/NeedsEvaluatorComponent.h"

UCreatureStateEat::UCreatureStateEat()
{
	StateName = ECreatureStateName::Eat;
}

bool UCreatureStateEat::TryEnterState(const ECreatureStateName FromState)
{
	return (FromState == ECreatureStateName::Travel || FromState == ECreatureStateName::Rest);
}

bool UCreatureStateEat::TryExitState()
{
	if(!Owner->NeedsEvaluator->IsCurrentNeed(ECreatureNeed::Eat))
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Rest);

	return false;
}

void UCreatureStateEat::Update()
{
	Super::Update();
	
	Owner->Hunger -= Owner->EatPerUpdate;
	if(Owner->Hunger < 0)
		Owner->Hunger = 0;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateEat.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Map/TilePlant.h"

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
	// TODO: Start searching for water if hunger is not critical
	if(Owner->CurrentTile->Type != ETileType::Plant || Owner->Hunger <= 40)
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Rest);

	return false;
}

void UCreatureStateEat::Update()
{
	Super::Update();
	
	ATilePlant* TilePlant = Cast<ATilePlant>(Owner->CurrentTile);

	if(TilePlant == nullptr)
		return;

	if(!TilePlant->Eat())
		return;
		
	Owner->Hunger -= Owner->EatPerUpdate;
	if(Owner->Hunger < 0)
		Owner->Hunger = 0;
	
}

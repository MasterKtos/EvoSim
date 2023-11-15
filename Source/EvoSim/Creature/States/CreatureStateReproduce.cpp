// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateReproduce.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Map/Tile.h"

UCreatureStateReproduce::UCreatureStateReproduce()
{
	StateName = ECreatureStateName::Reproduce;
}

bool UCreatureStateReproduce::TryEnterState(const ECreatureStateName FromState)
{
	if(FromState != ECreatureStateName::Travel)
		return false;

	for(ACreature* Creature : Owner->CurrentTile->CreaturesPresent)
	{
		if(	Creature == Owner ||
			//Creature->Randy != 100 ||
			Creature->StaticClass() != Owner->StaticClass() ||
			!Creature->AIComponent->ForceCurrentState(StateName, Owner))
			continue;

		Partner = Creature;
		bMother = false;
		CurrentTurn = 0;
		return true;
	}
	return false;
}

void UCreatureStateReproduce::ForceEnterState(ACreature* ForcedBy)
{
	Partner = ForcedBy;
	bMother = true;
	CurrentTurn = 0;
}

bool UCreatureStateReproduce::TryExitState()
{
	if(CurrentTurn >= Owner->TurnsToReproduce)
	{
		Owner->Reproduce(bMother, Partner);
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Rest);
	}
	return false;
}

void UCreatureStateReproduce::Update()
{
	Super::Update();

	// TODO: Force Exit if there is danger and tell about it to Partner
	// ForceCurrentState(Travel or RunAway or smth)

	CurrentTurn++;
}

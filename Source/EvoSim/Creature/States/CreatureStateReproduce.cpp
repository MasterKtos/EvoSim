// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateReproduce.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Carnivorous.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Map/Tile.h"

UCreatureStateReproduce::UCreatureStateReproduce()
{
	StateName = ECreatureStateName::Reproduce;
}

bool UCreatureStateReproduce::TryEnterState(const ECreatureStateName FromState)
{
	if(Owner->Randy < 100)
		return false;
	
	if(Owner->CurrentTile->CreaturesPresent.IsEmpty())
		return false;

	for(ACreature* Creature : Owner->CurrentTile->CreaturesPresent)
	{
		if(	Creature == Owner || !IsValid(Creature) ||
			!Creature->IsA(Owner->StaticClass()) ||
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
	// TODO: Force Exit if there is danger and tell about it to Partner
	// ForceCurrentState(Travel or RunAway or smth)
	
	if(CurrentTurn >= Owner->TurnsToReproduce)
	{
		Owner->Reproduce(bMother, Partner);
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Rest);
	}
	return false;
}

void UCreatureStateReproduce::Update()
{
	CurrentTurn++;
	
	Super::Update();
}

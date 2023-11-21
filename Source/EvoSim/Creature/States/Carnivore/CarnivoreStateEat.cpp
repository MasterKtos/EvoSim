// Fill out your copyright notice in the Description page of Project Settings.


#include "CarnivoreStateEat.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Corpse.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/Herbivorous.h"
#include "EvoSim/Creature/CreatureComponents/NeedsEvaluatorComponent.h"
#include "EvoSim/Map/Tile.h"

bool UCarnivoreStateEat::TryEnterState(const ECreatureStateName FromState)
{
	if(!Super::TryEnterState(FromState))
		return false;
	
	for(const auto Direction : TEnumRange<EDirection>())
	{
		const auto Neighbour = Owner->CurrentTile->GetNeighbour(Direction);
		if(!IsValid(Neighbour))
			continue;
		
		if(Neighbour->CreaturesPresent.IsEmpty())
			continue;

		// Previously hunted down prey
		if(!Neighbour->PreyPresent.IsEmpty())
		{
			Prey = Neighbour->PreyPresent.Last();
			return true;
		}

		// Hunt down herbivore
		AHerbivorous* Meat = nullptr;
		if(Neighbour->CreaturesPresent.FindItemByClass<AHerbivorous>(&Meat))
		{
			Meat->GetHuntedDown(Prey);
			return true;
		}
	}
	return false;
}

bool UCarnivoreStateEat::TryExitState()
{ 
	if(!Owner->NeedsEvaluator->IsCurrentNeed(ECreatureNeed::Eat) || !IsValid(Prey))
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Rest);

	return false;
}

void UCarnivoreStateEat::Update()
{
	// it's ugly, but I have no better idea how to handle it better at the moment
	if(IsValid(Prey) && !Prey->Eat())
		if(TryExitState())
			return;

	
	Super::Update();
}

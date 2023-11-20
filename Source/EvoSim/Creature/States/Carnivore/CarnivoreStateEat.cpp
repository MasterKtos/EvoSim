// Fill out your copyright notice in the Description page of Project Settings.


#include "CarnivoreStateEat.h"

#include "EvoSim/AI/AIComponent.h"
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
		
		if(!(Neighbour->CreaturesPresent.Num() > 0 &&
		   Neighbour->CreaturesPresent.FindItemByClass<AHerbivorous>()))
	   		continue;
		
		return true;
	}
	return false;
}

bool UCarnivoreStateEat::TryExitState()
{ 
	if(Owner->NeedsEvaluator->IsCurrentNeed(ECreatureNeed::Eat))
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Rest);

	return false;
}

void UCarnivoreStateEat::Update()
{
	Super::Update();
}

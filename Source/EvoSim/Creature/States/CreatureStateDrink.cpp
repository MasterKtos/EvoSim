// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateDrink.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/NeedsEvaluatorComponent.h"
#include "EvoSim/Map/Tile.h"

UCreatureStateDrink::UCreatureStateDrink()
{
	StateName = ECreatureStateName::Drink;
}

bool UCreatureStateDrink::TryEnterState(const ECreatureStateName FromState)
{
	if (FromState != ECreatureStateName::Travel &&
		FromState != ECreatureStateName::Rest)
			return false;
	
	for(const auto Direction : TEnumRange<EDirection>())
	{
		const auto Neighbour = Owner->CurrentTile->GetNeighbour(Direction);

		if(!IsValid(Neighbour))
			continue;
		if(Neighbour->Type != ETileType::Water)
			continue;
		
		return true;
	}
	
	return false;
}

bool UCreatureStateDrink::TryExitState()
{ 
	if(!Owner->NeedsEvaluator->IsCurrentNeed(ECreatureNeed::Drink))
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Rest);
	
	return false;
}

void UCreatureStateDrink::Update()
{
	Super::Update();

	if(Owner->Thirst - Owner->DrinkPerUpdate < 0)
	{
		Owner->Thirst = 0;
		return;
	}
	Owner->Thirst -= Owner->DrinkPerUpdate;
}

﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureStateRest.h"

#include "Algo/RandomShuffle.h"
#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/NeedsEvaluatorComponent.h"
#include "EvoSim/Map/Tile.h"

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
	if(const auto CurrentNeed = Owner->NeedsEvaluator->GetCurrentNeed();
		CurrentNeed != ECreatureNeed::Satisfied)
	{
		return Owner->AIComponent->ChangeCurrentState(ECreatureStateName::Travel);
	}
	return false;
}

void UCreatureStateRest::Update()
{
	TArray AllDirections = {
		EDirection::N, EDirection::NE, EDirection::E,
		EDirection::SE, EDirection::S, EDirection::SW,
		EDirection::W, EDirection::NW
	};
	Algo::RandomShuffle(AllDirections);
	for(const auto Direction : AllDirections)
	{
		const auto Neighbour = Owner->CurrentTile->GetNeighbour(Direction);
		if(IsValid(Neighbour) && Neighbour->CreaturesPresent.Num() == 0 && Owner->Move(Direction))
		{
			break;
		}
	}
	
	Super::Update();
}

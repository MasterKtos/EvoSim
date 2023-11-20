// Fill out your copyright notice in the Description page of Project Settings.


#include "HerbivoreStateEat.h"

#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Map/TilePlant.h"

bool UHerbivoreStateEat::TryEnterState(const ECreatureStateName FromState)
{
	if(!Super::TryEnterState(FromState))
		return false;

	if(Owner->CurrentTile->Type != ETileType::Plant)
		return false;
	
	return true;
}

void UHerbivoreStateEat::Update()
{
	ATilePlant* TilePlant = Cast<ATilePlant>(Owner->CurrentTile);

	// it's ugly, but I have no better idea how to handle it better at the moment
	if(IsValid(TilePlant) && !TilePlant->Eat())
		if(TryExitState())
			return;

	Super::Update();
	
}

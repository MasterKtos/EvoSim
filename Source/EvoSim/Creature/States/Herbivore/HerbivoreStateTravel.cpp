// Fill out your copyright notice in the Description page of Project Settings.


#include "HerbivoreStateTravel.h"

#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"

void UHerbivoreStateTravel::GetTargetsInView()
{
	Super::GetTargetsInView();
	
	Food = Owner->FovComponent->GetPlantTilesInSight();
	Bros = Owner->FovComponent->GetHerbCreaturesTilesInSight();
}

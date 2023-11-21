// Fill out your copyright notice in the Description page of Project Settings.


#include "CarnivoreStateTravel.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"

void UCarnivoreStateTravel::GetTargetsInView()
{
	Super::GetTargetsInView();
	
	Food = Owner->FovComponent->GetHerbCreaturesTilesInSight();
	Bros = Owner->FovComponent->GetMeatCreaturesTilesInSight();
}

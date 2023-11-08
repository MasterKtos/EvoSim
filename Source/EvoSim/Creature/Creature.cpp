// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"

#include "Components/SphereComponent.h"
#include "CreatureComponents/CreatureMovementComponent.h"
#include "CreatureComponents/FovComponent.h"
#include "EvoSim/Map/Tile.h"

ACreature::ACreature()
{
	PrimaryActorTick.bCanEverTick = false;

	FovComponent = CreateDefaultSubobject<UFovComponent>(TEXT("FovComponent"));
	MovementComponent = CreateDefaultSubobject<UCreatureMovementComponent>(TEXT("MovementComponent"));
	AIComponent = CreateDefaultSubobject<UAIComponent>(TEXT("AIComponent"));
	FovSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	SetRootComponent(FovSphereComponent);
}

bool ACreature::Move(const EDirection Direction)
{
	ATile* NeighbourTile = CurrentTile->GetNeighbour(Direction); 
	if(!IsValid(NeighbourTile))
		return false;

	if(NeighbourTile->Type == ETileType::Water || NeighbourTile->Type == ETileType::Obstacle)
		return false;

	CurrentTile->CreaturesPresent.Remove(this);
	CurrentTile = NeighbourTile;
	CurrentTile->CreaturesPresent.Add(this);
	
	MovementComponent->SetNewTarget(CurrentTile->GetActorLocation());
	return true;
}

void ACreature::Reproduce(bool bMother)
{
	Hunger += HungerPerReproduction;
	Thirst += ThirstPerReproduction;
}


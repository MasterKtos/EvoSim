// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"

#include "Components/SphereComponent.h"
#include "CreatureComponents/CreatureMovementComponent.h"
#include "CreatureComponents/FovComponent.h"
#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Map/Tile.h"

ACreature::ACreature()
{
	PrimaryActorTick.bCanEverTick = true;

	FovComponent = CreateDefaultSubobject<UFovComponent>(TEXT("FovComponent"));
	MovementComponent = CreateDefaultSubobject<UCreatureMovementComponent>(TEXT("MovementComponent"));
	AIComponent = CreateDefaultSubobject<UAIComponent>(TEXT("AIComponent"));
	FovSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
}

void ACreature::BeginPlay()
{
	Super::BeginPlay();

	Speed = 100.f;
	FieldOfView = 360;
	ViewDistance = 7;
	Hunger = 45;	
	Thirst = 40;

	FovSphereComponent->SetSphereRadius(ViewDistance * 100);
}

bool ACreature::Move(const EDirection Direction)
{
	ATile* NeighbourTile = CurrentTile->GetNeighbour(Direction); 
	if(!IsValid(NeighbourTile))
		return false;
		
	CurrentTile = NeighbourTile;
	
	MovementComponent->SetNewTarget(CurrentTile->GetActorLocation());
	return true;
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"

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
}

void ACreature::BeginPlay()
{
	Super::BeginPlay();

	Speed = 100.f;
	FieldOfView = 360;
	ViewDistance = 7;
}

bool ACreature::Move(TArray<EDirection>::ElementType Direction) const
{
	const ATile* NeighbourTile = CurrentTile->GetNeighbour(Direction);
	if(NeighbourTile == nullptr)
		return false;

	MovementComponent->SetNewTarget(NeighbourTile->GetActorLocation());
	return true;
}


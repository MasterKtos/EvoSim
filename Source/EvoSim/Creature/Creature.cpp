// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"

#include "Components/SphereComponent.h"
#include "CreatureComponents/CreatureMovementComponent.h"
#include "CreatureComponents/FovComponent.h"
#include "CreatureComponents/MemoryComponent.h"
#include "CreatureComponents/NeedsEvaluatorComponent.h"
#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Manager/SimManager.h"
#include "EvoSim/Map/Tile.h"
#include "States/RestStrategy/RestStrategy.h"

ACreature::ACreature()
{
	PrimaryActorTick.bCanEverTick = false;

	FovComponent = CreateDefaultSubobject<UFovComponent>(TEXT("FovComponent"));
	MovementComponent = CreateDefaultSubobject<UCreatureMovementComponent>(TEXT("MovementComponent"));
	AIComponent = CreateDefaultSubobject<UAIComponent>(TEXT("AIComponent"));
	FovSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	NeedsEvaluator = CreateDefaultSubobject<UNeedsEvaluatorComponent>(TEXT("NeedsEvaluatorComponent"));
	MemoryComponent = CreateDefaultSubobject<UMemoryComponent>(TEXT("MemoryComponent"));
	RestStrategy = CreateDefaultSubobject<URestStrategy>(TEXT("RestStrategy"));
	RestStrategy->SetStrategy(ERestStrategyName::Random);
	
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

void ACreature::ApplyRestMovement() const
{
	RestStrategy->ApplyMovement();
}

void ACreature::Die()
{
	Cast<USimManager>(GetWorld()->GetGameInstance())->RemoveFromUpdate(this->AIComponent);
	CurrentTile->CreaturesPresent.Remove(this);
	Destroy();
}

void ACreature::Reproduce(bool bMother, ACreature* Partner)
{
	Hunger += HungerPerReproduction;
	Thirst += ThirstPerReproduction;
	Randy = 0;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"

#include "CreatureComponents/FovComponent.h"

ACreature::ACreature()
{
	PrimaryActorTick.bCanEverTick = true;

	FovComponent = CreateDefaultSubobject<UFovComponent>(TEXT("FovComponent"));
}

void ACreature::BeginPlay()
{
	Super::BeginPlay();

	FieldOfView = 270;
	ViewDistance = 4;
}

void ACreature::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	if(FovComponent != nullptr)
		FovComponent->UpdateTilesInSight();
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Herbivorous.h"

#include "Corpse.h"
#include "Components/SphereComponent.h"
#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Manager/SimManager.h"
#include "EvoSim/Map/Tile.h"
#include "States/CreatureState.h"
#include "States/CreatureStateDrink.h"
#include "States/CreatureStateReproduce.h"
#include "States/CreatureStateRest.h"
#include "States/Herbivore/HerbivoreStateEat.h"
#include "States/Herbivore/HerbivoreStateTravel.h"


AHerbivorous::AHerbivorous()
{	
	PrimaryActorTick.bCanEverTick = false;
}

void AHerbivorous::Reproduce(const bool bMother, ACreature* Partner)
{
	Super::Reproduce(bMother);

	if(!bMother)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	if (AHerbivorous* Child = GetWorld()->SpawnActor<AHerbivorous>(GetClass(), this->GetActorLocation(), this->GetActorRotation(), SpawnParams))
	{
		Child->CurrentTile = CurrentTile;
		Child->MapManager = MapManager;

		Child->Speed = MutateFeature(Speed, Partner->Speed, 0.1f, 1.f, 0.1f);
		Child->ViewDistance = static_cast<float>(MutateFeature(static_cast<int>(ViewDistance), static_cast<int>(Partner->ViewDistance), 1, 20, 2));
		Child->FieldOfView = static_cast<float>(MutateFeature(static_cast<int>(FieldOfView), static_cast<int>(Partner->FieldOfView), 90, 360, 36));
	}
}

void AHerbivorous::GetHuntedDown(ACorpse* &Remains)
{
	Remains = GetWorld()->SpawnActor<ACorpse>(ACorpse::StaticClass(), this->GetActorLocation(), this->GetActorRotation(), FActorSpawnParameters());
	Remains->CurrentTile = CurrentTile;
	CurrentTile->PreyPresent.Add(Remains);
	Die();
}

void AHerbivorous::BeginPlay()
{
	Super::BeginPlay();

	if(const USimManager* GameInstance = Cast<USimManager>(GetGameInstance()))
	{
		Speed = GameInstance->HerbSpeed;
		FieldOfView = GameInstance->FOV;
		ViewDistance = GameInstance->ViewDistance;
	}
	else
	{
		UE_LOG(LogActor, Warning, TEXT("GameInstance cast failed!"));
		Destroy();
	}
	
	Hunger = 45;	
	Thirst = 40;

	FovSphereComponent->SetSphereRadius(ViewDistance * 100);
	AIComponent->InitializeStateMap({
		{ECreatureStateName::Rest, NewObject<UCreatureStateRest>(AIComponent->GetOuter())},
		{ECreatureStateName::Eat, NewObject<UHerbivoreStateEat>(AIComponent->GetOuter())},
		{ECreatureStateName::Drink, NewObject<UCreatureStateDrink>(AIComponent->GetOuter())},
		{ECreatureStateName::Travel, NewObject<UHerbivoreStateTravel>(AIComponent->GetOuter())},
		{ECreatureStateName::Reproduce, NewObject<UCreatureStateReproduce>(AIComponent->GetOuter())},
	 });
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "Herbivorous.h"

#include "Components/SphereComponent.h"
#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Manager/SimManager.h"
#include "States/CreatureState.h"
#include "States/CreatureStateDrink.h"
#include "States/CreatureStateEat.h"
#include "States/CreatureStateReproduce.h"
#include "States/CreatureStateRest.h"
#include "States/CreatureStateTravel.h"


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
	}
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
		{ECreatureStateName::Rest, NewObject<UCreatureStateRest>()},
		{ECreatureStateName::Eat, NewObject<UCreatureStateEat>()},
		{ECreatureStateName::Drink, NewObject<UCreatureStateDrink>()},
		{ECreatureStateName::Travel, NewObject<UCreatureStateTravel>()},
		{ECreatureStateName::Reproduce, NewObject<UCreatureStateReproduce>()},
	 });
}


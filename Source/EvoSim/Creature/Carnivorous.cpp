// Fill out your copyright notice in the Description page of Project Settings.


#include "Carnivorous.h"

#include "Components/SphereComponent.h"
#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Manager/SimManager.h"
#include "States/CreatureStateDrink.h"
#include "States/CreatureStateReproduce.h"
#include "States/CreatureStateRest.h"
#include "States/Carnivore/CarnivoreStateEat.h"
#include "States/Carnivore/CarnivoreStateTravel.h"


ACarnivorous::ACarnivorous()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACarnivorous::Reproduce(const bool bMother, ACreature* Partner)
{
	Super::Reproduce(bMother);
	
	if(!bMother)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	if (ACarnivorous* Child = GetWorld()->SpawnActor<ACarnivorous>(GetClass(), this->GetActorLocation(), this->GetActorRotation(), SpawnParams))
	{
		Child->CurrentTile = CurrentTile;
		Child->MapManager = MapManager;
	}
}

void ACarnivorous::BeginPlay()
{
	Super::BeginPlay();
	
	if(const USimManager* GameInstance = Cast<USimManager>(GetGameInstance()))
	{
		Speed = GameInstance->MeatSpeed;
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
		{ECreatureStateName::Eat, NewObject<UCarnivoreStateEat>()},
		{ECreatureStateName::Drink, NewObject<UCreatureStateDrink>()},
		{ECreatureStateName::Travel, NewObject<UCarnivoreStateTravel>()},
		{ECreatureStateName::Reproduce, NewObject<UCreatureStateReproduce>()},
	 });
}

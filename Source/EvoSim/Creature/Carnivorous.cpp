﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Carnivorous.h"

#include "Components/SphereComponent.h"
#include "EvoSim/Manager/SimManager.h"


ACarnivorous::ACarnivorous()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACarnivorous::Reproduce(bool bMother)
{
	Super::Reproduce(bMother);
	
	if(!bMother)
		return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	if (ACarnivorous* Child = GetWorld()->SpawnActor<ACarnivorous>(GetClass(), this->GetActorLocation(), this->GetActorRotation(), SpawnParams))
	{
		Child->CurrentTile = CurrentTile;
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
	
	bHerbivorous = false;
	Hunger = 45;	
	Thirst = 40;

	FovSphereComponent->SetSphereRadius(ViewDistance * 100);
}
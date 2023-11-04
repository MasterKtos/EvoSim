// Fill out your copyright notice in the Description page of Project Settings.


#include "Herbivorous.h"

#include "Components/SphereComponent.h"
#include "EvoSim/Manager/SimManager.h"


AHerbivorous::AHerbivorous()
{
	PrimaryActorTick.bCanEverTick = false;

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
	
	bHerbivorous = true;
	Hunger = 45;	
	Thirst = 40;

	FovSphereComponent->SetSphereRadius(ViewDistance * 100);
}


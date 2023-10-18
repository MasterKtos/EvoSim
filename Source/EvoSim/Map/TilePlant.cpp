// Fill out your copyright notice in the Description page of Project Settings.


#include "TilePlant.h"


// Sets default values
ATilePlant::ATilePlant()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATilePlant::Update()
{
	Super::Update();
	
	if(Type == ETileType::Land)
	{
		if(TimeToResetCounter >= TimeToReset)
		{
			RegrowPlant();
			TimeToResetCounter = 0;
		}
		else TimeToResetCounter++;
	}
}

void ATilePlant::Eat()
{
	PlantMeshComponent->SetVisibility(false, true);
	SetTileType(ETileType::Land);
}

void ATilePlant::RegrowPlant()
{
	PlantMeshComponent->SetVisibility(true, true);
	SetTileType(ETileType::Plant);
}


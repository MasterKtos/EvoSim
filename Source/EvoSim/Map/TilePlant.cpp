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
	
	if(Durability < MaxDurability)
	{
		if(TimeToResetCounter >= TimeToReset)
		{
			if(Durability == 0)
				RegrowPlant();

			Durability++;	
			TimeToResetCounter = 0;
		}
		else TimeToResetCounter++;
	}
}

void ATilePlant::Eat()
{
	TimeToResetCounter = 0;
	Durability--;
	if(Durability < 1)
	{
		PlantMeshComponent->SetVisibility(false, true);
		SetTileType(ETileType::Land);
	}
}

void ATilePlant::RegrowPlant()
{
	PlantMeshComponent->SetVisibility(true, true);
	SetTileType(ETileType::Plant);
}


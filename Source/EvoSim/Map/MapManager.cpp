// Fill out your copyright notice in the Description page of Project Settings.

#include "MapManager.h"

// Sets default values
AMapManager::AMapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AMapManager::GenerateMap(FInitialParameters Parameters)
{
	Tiles = Parameters.InitialMap;

	for(auto& Tile : Tiles)
	{
		
	}
}

void AMapManager::UpdateTiles()
{
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "MapManager.h"
#include "Tile.h"

// Sets default values
AMapManager::AMapManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AMapManager::GenerateMap(const FInitialParameters& Parameters)
{
	for (const auto TileType : Parameters.InitialMap)
	{
		auto* NewTile = Cast<ATile>(GetWorld()->SpawnActor(TilePrefab.Get()));
		NewTile->SetTileType(TileType);
		Tiles.Add(NewTile);
	}

	TilesRowSize = Parameters.InitialMapRowNum;
	const int TilesRowNum = Tiles.Num() / TilesRowSize;

	const static float TileSize = Tiles[0]->GetComponentsBoundingBox().GetExtent().X * 2;
	const static FVector3d StartPoint = {-TilesRowSize/2.0 * TileSize, -TilesRowNum/2.0 * TileSize, 0};

	// Set up nibbors
	for (int i = 0; i < TilesRowNum; ++i)
	{
		for (int j = 0; j < TilesRowSize; ++j)
		{
			const auto CurrentTile = GetTileFromCoords(j, i);
			CurrentTile->Coords = {static_cast<double>(j), static_cast<double>(i)};
			checkf(CurrentTile, TEXT("There's a nullptr in input tile map"));
	
			CurrentTile->SetNeighbours(
					i!=0 ? GetTileFromCoords(j, i-1) : nullptr,
					i!=TilesRowNum ? GetTileFromCoords(j, i+1) : nullptr,
					j!=0 ? GetTileFromCoords(j-1, i) : nullptr,
					j!=TilesRowSize ? GetTileFromCoords(j+1, i) : nullptr
				);

			CurrentTile->SetActorLocation(StartPoint + FVector3d(TileSize * j, TileSize * i, 0));
		}
	}
}

void AMapManager::UpdateTiles()
{
	for(ATile* Tile : Tiles)
	{
		Tile->Update();
	}
}

int AMapManager::MapCoordsToIndex(int CoordX, int CoordY) const
{
	return CoordY * TilesRowSize + CoordX;
}

ATile* AMapManager::GetTileFromCoords(int CoordX, int CoordY)
{
	const int TileIndex = MapCoordsToIndex(CoordX, CoordY);
	return Tiles.IsValidIndex(TileIndex) ? Tiles[TileIndex] : nullptr;
}

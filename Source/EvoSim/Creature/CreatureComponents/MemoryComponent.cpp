// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryComponent.h"


UMemoryComponent::UMemoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UMemoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// Real size can change if Array will be too small
	constexpr int MemorySize = 10;
	TilesToRemember.SetNum(MemorySize);
	
	for (int Index = 0; Index < MemorySize; Index++)
	{
		TilesToRemember[Index] = {NO_VALUE, nullptr};
	}
}

void UMemoryComponent::RememberTile(ATile* Tile)
{
	// Enables for only one loop instead of two inside TilesToRemember
	int EmptySpace = -1;
	
	// Check if this tile is already present inside TArray
	for (int Index = 0; Index < TilesToRemember.Num(); Index++)
	{
		if(EmptySpace == -1 && TilesToRemember[Index].Turns == NO_VALUE)
		{
			EmptySpace = Index;
		}
		if(TilesToRemember[Index].Tile == Tile)
		{
			TilesToRemember[Index].Turns = TIME_TO_REMEMBER;
			return;
		}
	}

	if(EmptySpace != -1)
	{
		TilesToRemember[EmptySpace].Turns = TIME_TO_REMEMBER;
		TilesToRemember[EmptySpace].Tile = Tile;
		return;
	}
	
	TilesToRemember.Add({TIME_TO_REMEMBER, Tile});
}

TArray<ATile*> UMemoryComponent::GetRememberedTiles(const ETileType TileType1, const ETileType TileType2)
{
	TArray<ATile*> Tiles;
	if(TileType1 == ETileType::Obstacle)
	{
		for (auto [Turns, Tile] : TilesToRemember)
			if(Turns != NO_VALUE)
				Tiles.Add(Tile);
	}
	else
	{
		for (auto [Turns, Tile] : TilesToRemember)
			if(Turns != NO_VALUE && (Tile->Type == TileType1 || Tile->Type == TileType2))
				Tiles.Add(Tile);
	}
	
	return Tiles;
}

void UMemoryComponent::CheckTilesToForget()
{
	for (int Index = 0; Index < TilesToRemember.Num(); Index++)
	{
		if (TilesToRemember[Index].Turns != NO_VALUE)
		{
			TilesToRemember[Index].Turns -= 1;
			return;
		}
		TilesToRemember[Index].Tile = nullptr;
	}
}

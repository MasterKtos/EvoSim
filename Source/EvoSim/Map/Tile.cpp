// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

ATile* ATile::GetNeighbour(const EDirection Direction) const
{
	switch(Direction)
	{
		case EDirection::N:  return Up;
		case EDirection::NE: return IsValid(Up) ? Up->Left : nullptr;
		case EDirection::E:  return Left;
		case EDirection::SE: return IsValid(Down) ? Down->Left : nullptr;
		case EDirection::S:  return Down;
		case EDirection::SW: return IsValid(Down) ? Down->Right : nullptr;
		case EDirection::W:  return Right;
		case EDirection::NW: return IsValid(Up) ? Up->Right : nullptr;
		default: return nullptr;
	}
}

void ATile::Update()
{
	if(Type != ETileType::Plant)
		return;
	// Grow da plant
}

void ATile::SetNeighbours(ATile* UpTile, ATile* DownTile, ATile* LeftTile, ATile* RightTile)
{
	Up = UpTile;
	Down = DownTile;
	Left = LeftTile;
	Right = RightTile;
}

void ATile::SetTileType_Implementation(ETileType NewType)
{
	Type = NewType;
}

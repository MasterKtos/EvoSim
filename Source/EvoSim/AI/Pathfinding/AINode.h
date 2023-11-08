// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EvoSim/Map/Tile.h"
#include "UObject/Object.h"
#include "AINode.generated.h"

/// Used by pathfinding
UCLASS()
class EVOSIM_API UAINode : public UObject
{
	GENERATED_BODY()

public:
	FORCEINLINE int GetCost() const { return SourceCost+DestinationCost; }
	FORCEINLINE int IsWalkable() const
	{
		// Perform mask check on type
		return IsValid(Tile) && (static_cast<uint8>(Tile->Type) &
			(static_cast<uint8>(ETileType::Water) |
			static_cast<uint8>(ETileType::Obstacle))) == 0;
	}

	// UAINodeHeap
	int HeapIndex = 0;
	int CompareTo(UAINode* Other);
	bool Equals(UAINode* Other);
	// ~UAINodeHeap
	
	UPROPERTY()
	UAINode* Parent;
	UPROPERTY()
	EDirection ParentDirection;
	UPROPERTY()
	ATile* Tile;
	UPROPERTY()
	TMap<UAINode*, EDirection> Neighbours;

	UPROPERTY()
	uint32 SourceCost;
	UPROPERTY()
	uint32 DestinationCost;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "AIManager.h"

#include "AINode.h"
#include "AINodeHeap.h"
#include "EvoSim/Map/Tile.h"

// Sets default values
AAIManager::AAIManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AAIManager::BeginPlay()
{
	Super::BeginPlay();

}

TArray<EDirection> AAIManager::FindPathToTile(ATile* From, ATile* To)
{
	UAINodeHeap* OpenedNodes = NewObject<UAINodeHeap>();
	OpenedNodes->Init(50*50);
	TSet<ATile*> ClosedNodes = {};

	UAINode* FirstNode = NewObject<UAINode>();
	FirstNode->Tile = From;
	OpenedNodes->Add(FirstNode);

	UAINode* LastNode = NewObject<UAINode>();
	LastNode->Tile = To;
	
	while(OpenedNodes->Num() > 0)
	{
		// Find node with lowest cost
		UAINode* CurrentNode = Cast<UAINode>(OpenedNodes->RemoveFirst());
		ClosedNodes.Add(CurrentNode->Tile);

		// Found node!
		if(CurrentNode->Tile->Coords == To->Coords)
		{
			return GetPath(CurrentNode);
		}

		if(CurrentNode->Neighbours.IsEmpty())
		{
			for (const auto Direction : TEnumRange<EDirection>())
			{
				UAINode* Neighbour = NewObject<UAINode>();
				Neighbour->Tile = CurrentNode->Tile->GetNeighbour(Direction);

				if(!IsValid(Neighbour->Tile))
					continue;
				
				Neighbour->Parent = CurrentNode;
				Neighbour->ParentDirection = Direction;
				// Found node!
				if(Neighbour->Tile->Coords == To->Coords)
				{
					return GetPath(Neighbour);
				}
				CurrentNode->Neighbours.Add(Neighbour, Direction);
			}
		}

		for (const auto& Neighbour : CurrentNode->Neighbours)
		{
			auto* NeighbourNode = Neighbour.Key;
			if(!NeighbourNode->IsWalkable() || ClosedNodes.Contains(NeighbourNode->Tile))
				continue;

			const uint8 NewNeighbourSourceCost = CurrentNode->SourceCost + GetDistance(CurrentNode, NeighbourNode);
			if(NewNeighbourSourceCost < NeighbourNode->SourceCost || !OpenedNodes->Contains(NeighbourNode))
			{
				NeighbourNode->SourceCost = NewNeighbourSourceCost;
				NeighbourNode->DestinationCost = GetDistance(NeighbourNode, LastNode);

				if(!OpenedNodes->Contains(NeighbourNode))
					OpenedNodes->Add(NeighbourNode);
			}
		}
	}
	return {};
}

TArray<EDirection> AAIManager::FindPathToTile(ATile* From, TArray<ATile*> To)
{
	int BestScore = 100;
	TArray<EDirection> BestPath = {};
	TArray<ATile*> SecondaryPriorityTiles = {};
	
	for (ATile* Tile : To)
	{
		if(From == Tile)
			return {};

		// Try to avoid going to a tile that already has a creature on it
		if(Tile->CreaturesPresent.Num() > 0)
		{
			SecondaryPriorityTiles.Add(Tile);
			continue;
		}
		
		TArray<EDirection> ThisPath = FindPathToTile(From, Tile);

		if(!ThisPath.IsEmpty() && ThisPath.Num() < BestScore)
		{
			BestScore = ThisPath.Num();
			BestPath = ThisPath;
		}
	}
	if(BestPath.IsEmpty())
	{
		for (ATile* Tile : SecondaryPriorityTiles)
		{
			TArray<EDirection> ThisPath = FindPathToTile(From, Tile);

			if(!ThisPath.IsEmpty() && ThisPath.Num() < BestScore)
			{
				BestScore = ThisPath.Num();
				BestPath = ThisPath;
			}
		}
	}
	return BestPath;
}


uint8 AAIManager::GetDistance(const UAINode* FromNode, const UAINode* ToNode)
{
	const FVector2D Distance = FVector2D(
		FMath::Abs(FromNode->Tile->Coords.X - ToNode->Tile->Coords.X),
		FMath::Abs(FromNode->Tile->Coords.Y - ToNode->Tile->Coords.Y));

	if(Distance.X > Distance.Y)
		return 14*Distance.Y + 10*(Distance.X-Distance.Y);
	return 14*Distance.X + 10*(Distance.Y-Distance.X);
}

TArray<EDirection> AAIManager::GetPath(const UAINode* FromNode)
{
	TArray<EDirection> Path = {};

	const UAINode* CurrentNode = FromNode;
	while(IsValid(CurrentNode->Parent))
	{
		EDirection DirectionFromParentToNode = CurrentNode->ParentDirection;
		Path.Add(DirectionFromParentToNode);
		CurrentNode = CurrentNode->Parent;
	}
	// Algo::Reverse(Path);
	return Path;
}

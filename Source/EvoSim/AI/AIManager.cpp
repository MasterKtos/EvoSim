// Fill out your copyright notice in the Description page of Project Settings.


#include "AIManager.h"

#include "AINode.h"
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
	TArray<UAINode*> OpenedNodes = {};
	TSet<ATile*> ClosedNodes = {};

	UAINode* FirstNode = NewObject<UAINode>();
	FirstNode->Tile = From;
	OpenedNodes.Add(FirstNode);

	UAINode* LastNode = NewObject<UAINode>();
	LastNode->Tile = To;
	
	while(OpenedNodes.Num() > 0)
	{
		// Find node with lowest cost
		UAINode* CurrentNode = OpenedNodes[0];
		for (auto* Node : OpenedNodes)
		{
			if(Node->GetCost() < CurrentNode->GetCost() ||
				Node->GetCost() == CurrentNode->GetCost() && Node->DestinationCost < CurrentNode->DestinationCost)
				CurrentNode = Node;
		}
		
		OpenedNodes.Remove(CurrentNode);
		ClosedNodes.Add(CurrentNode->Tile);

		// Found node!
		if(CurrentNode->Tile->Coords == To->Coords)
		{
			return GetPath(CurrentNode, FirstNode);
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
					return GetPath(Neighbour, FirstNode);
				}
				CurrentNode->Neighbours.Add(Neighbour, Direction);
			}
		}

		for (auto& Neighbour : CurrentNode->Neighbours)
		{
			auto* NeighbourNode = Neighbour.Key;
			if(!NeighbourNode->IsWalkable() || ClosedNodes.Contains(NeighbourNode->Tile))
				continue;

			const uint8 NewNeighbourSourceCost = CurrentNode->SourceCost + GetDistance(CurrentNode, NeighbourNode);
			if(NewNeighbourSourceCost < NeighbourNode->SourceCost || !OpenedNodes.Contains(NeighbourNode))
			{
				NeighbourNode->SourceCost = NewNeighbourSourceCost;
				NeighbourNode->DestinationCost = GetDistance(NeighbourNode, LastNode);

				if(!OpenedNodes.Contains(NeighbourNode))
					OpenedNodes.Add(NeighbourNode);
			}
		}
	}
	return {};
}

TArray<EDirection> AAIManager::FindPathToTile(ATile* From, TArray<ATile*> To)
{
	int BestScore = 100;
	TArray<EDirection> BestPath;
	
	for (ATile* Tile : To)
	{
		if(From == Tile)
			continue;
		
		TArray<EDirection> ThisPath = FindPathToTile(From, Tile);

		if(!ThisPath.IsEmpty() && ThisPath.Num() < BestScore)
		{
			BestScore = ThisPath.Num();
			BestPath = ThisPath;
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

TArray<EDirection> AAIManager::GetPath(UAINode* FromNode, UAINode* ToNode)
{
	TArray<EDirection> Path = {};

	UAINode* CurrentNode = FromNode;
	while(IsValid(CurrentNode->Parent))
	{
		// EDirection DirectionFromParentToNode = *CurrentNode->Parent->Neighbours.Find(CurrentNode);
		// EDirection DirectionFromParentToNode = static_cast<EDirection>((static_cast<uint8>(CurrentNode->ParentDirection)+4)%8);
		EDirection DirectionFromParentToNode = CurrentNode->ParentDirection;
		Path.Add(DirectionFromParentToNode);
		CurrentNode = CurrentNode->Parent;
	}
	Algo::Reverse(Path);
	return Path;
}

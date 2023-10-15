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
	TSet<UAINode*> ClosedNodes = {};

	UAINode* FirstNode = NewObject<UAINode>();
	FirstNode->Tile = From;
	OpenedNodes.Add(FirstNode);

	UAINode* LastNode = NewObject<UAINode>();
	LastNode->Tile = To;
	
	while(OpenedNodes.Num() > 0)
	{
		// Find node with lowest cost
		UAINode* CurrentNode = OpenedNodes[0];
		for (const auto Node : OpenedNodes)
		{
			if(Node->GetCost() < CurrentNode->GetCost() ||
				Node->GetCost() == CurrentNode->GetCost() && Node->DestinationCost < CurrentNode->DestinationCost)
				CurrentNode = Node;
		}
		
		OpenedNodes.Remove(CurrentNode);
		ClosedNodes.Add(CurrentNode);

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
				
				CurrentNode->Neighbours.Add(Neighbour, Direction);
			}
		}

		for (auto& Neighbour : CurrentNode->Neighbours)
		{
			auto NeighbourNode = Neighbour.Key;			
			if(!NeighbourNode->IsWalkable() || ClosedNodes.Contains(NeighbourNode))
				continue;

			const uint8 NewNeighbourSourceCost = CurrentNode->SourceCost + GetDistance(CurrentNode, NeighbourNode);
			if(NewNeighbourSourceCost < NeighbourNode->SourceCost || !OpenedNodes.Contains(NeighbourNode))
			{
				NeighbourNode->SourceCost = NewNeighbourSourceCost;
				NeighbourNode->DestinationCost = GetDistance(NeighbourNode, LastNode);
				NeighbourNode->Parent = CurrentNode;

				if(!OpenedNodes.Contains(NeighbourNode))
					OpenedNodes.Add(NeighbourNode);
			}
		}
	}
	return {};
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
	while(CurrentNode != ToNode)
	{
		EDirection DirectionFromParentToNode = *CurrentNode->Parent->Neighbours.Find(CurrentNode);
		Path.Add(DirectionFromParentToNode);
		CurrentNode = CurrentNode->Parent;
	}
	Algo::Reverse(Path);
	return Path;
}

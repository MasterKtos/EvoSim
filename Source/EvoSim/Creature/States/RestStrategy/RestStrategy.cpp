// Fill out your copyright notice in the Description page of Project Settings.


#include "RestStrategy.h"

#include "Algo/RandomShuffle.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"
#include "EvoSim/Map/Tile.h"

void URestStrategy::SetStrategy(const ERestStrategyName Name)
{
	StrategyName = Name;
}

void URestStrategy::ApplyMovement() const
{
	switch (StrategyName) {
		case ERestStrategyName::Random: RandomMovement(); break;
		case ERestStrategyName::CloseToBros: CloseToBrosMovement(); break;
		case ERestStrategyName::AwayFromBros: AwayFromBrosMovement(); break;
		case ERestStrategyName::None: // falls through
		default: break;
	}
}

void URestStrategy::RandomMovement() const
{
	TArray AllDirections = {
		EDirection::N, EDirection::NE, EDirection::E,
		EDirection::SE, EDirection::S, EDirection::SW,
		EDirection::W, EDirection::NW
	};
	Algo::RandomShuffle(AllDirections);
	for(const auto Direction : AllDirections)
	{
		const auto Neighbour = Owner->CurrentTile->GetNeighbour(Direction);
		if(IsValid(Neighbour) && Neighbour->CreaturesPresent.Num() == 0 && Owner->Move(Direction))
		{
			break;
		}
	}
}

void URestStrategy::CloseToBrosMovement() const
{
	Owner->FovComponent->UpdateTilesInSight();

	auto BrosInSight = Owner->FovComponent->GetMeatCreaturesTilesInSight();
	if(BrosInSight.IsEmpty())
	{
		RandomMovement();
		return;
	}
	
	float ClosestDist = 1000;
	FVector ClosestBroPos = {};
	
	for(const ATile* Bro : BrosInSight)
	{
		const float Dist = FVector::Dist(Bro->GetActorLocation(), Owner->GetActorLocation());
		if(Dist <= 10)
		{
			RandomMovement();
			return;
		}
		if(Dist < ClosestDist)
		{
			ClosestDist = Dist;
			ClosestBroPos = Bro->GetActorLocation();
		}
	}

	FVector DirAwayFromBro = ClosestBroPos - Owner->GetActorLocation();
	DirAwayFromBro.Normalize();

	const TMap<EDirection, FVector> DirectionToVector = {
		{EDirection::N, {0, -1, 0}},
		{EDirection::NE, {0.5, -0.5, 0}},
		{EDirection::E, {1, 0, 0}},
		{EDirection::SE, {0.5, 0.5, 0}},
		{EDirection::S, {0, 1, 0}},
		{EDirection::SW, {-0.5, 0.5, 0}},
		{EDirection::W, {-1, 0, 0}},
		{EDirection::NW, {-0.5, -0.5, 0}}
	};

	EDirection SmallestDotDirection = EDirection::S;
	for(auto Dir : DirectionToVector)
	{
		if(!IsValid(Owner->CurrentTile->GetNeighbour(Dir.Key)))
			continue;
		const auto DotVal = FVector::Dist(DirAwayFromBro, Dir.Value);
		if(FMath::Abs(DotVal) < 0.5)
		{
			SmallestDotDirection = Dir.Key;
			break;
		}
	}
	if(!Owner->Move(SmallestDotDirection))
		RandomMovement();
}

void URestStrategy::AwayFromBrosMovement() const
{
	Owner->FovComponent->UpdateTilesInSight();

	auto BrosInSight = Owner->FovComponent->GetMeatCreaturesTilesInSight();
	if(BrosInSight.IsEmpty())
	{
		RandomMovement();
		return;
	}
	
	float ClosestDist = 1000;
	FVector ClosestBroPos = {};
	
	for(const ATile* Bro : BrosInSight)
	{
		const float Dist = FVector::Dist(Bro->GetActorLocation(), Owner->GetActorLocation());
		if(Dist <= 10)
		{
			RandomMovement();
			return;
		}
		if(Dist < ClosestDist)
		{
			ClosestDist = Dist;
			ClosestBroPos = Bro->GetActorLocation();
		}
	}

	FVector DirAwayFromBro = Owner->GetActorLocation() - ClosestBroPos;
	DirAwayFromBro.Normalize();

	const TMap<EDirection, FVector> DirectionToVector = {
		{EDirection::N, {0, -1, 0}},
		{EDirection::NE, {0.5, -0.5, 0}},
		{EDirection::E, {1, 0, 0}},
		{EDirection::SE, {0.5, 0.5, 0}},
		{EDirection::S, {0, 1, 0}},
		{EDirection::SW, {-0.5, 0.5, 0}},
		{EDirection::W, {-1, 0, 0}},
		{EDirection::NW, {-0.5, -0.5, 0}}
	};

	EDirection SmallestDotDirection = EDirection::S;
	for(auto Dir : DirectionToVector)
	{
		if(!IsValid(Owner->CurrentTile->GetNeighbour(Dir.Key)))
			continue;
		const auto DotVal = FVector::Dist(DirAwayFromBro, Dir.Value);
		if(FMath::Abs(DotVal) < 0.5)
		{
			SmallestDotDirection = Dir.Key;
			break;
		}
	}
	if(!Owner->Move(SmallestDotDirection))
		RandomMovement();
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "FovComponent.h"

#include "ComponentReregisterContext.h"
#include "Components/SphereComponent.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Map/Tile.h"
#include "Kismet/KismetSystemLibrary.h"

UFovComponent::UFovComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFovComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACreature>(GetOwner());
	if(!ensure(Owner))
		UE_LOG(LogActorComponent, Log, TEXT("FovComponent | No Owner (or owner is not a Creature)."));

	IgnoredActors.Add(Owner);
}

TArray<AActor*> UFovComponent::GetOverlappingActors(UClass* ActorsOfClass) const
{
	TArray<AActor*> OverlappingActors;
	UKismetSystemLibrary::ComponentOverlapActors(Owner->FovSphereComponent, Owner->GetTransform(),
		TraceObjectTypes, ActorsOfClass, IgnoredActors, OverlappingActors);
	return OverlappingActors;
}

void UFovComponent::UpdateTilesInSight()
{
	WaterTiles.Empty();
	PlantTiles.Empty();
	CreaturesInSight.Empty();
	
	const FVector OwnerLocation = Owner->GetActorLocation();

	TArray<ATile*> OverlappingTiles;

	{
		TArray<AActor*> OverlappingTilesActors = GetOverlappingActors(ATile::StaticClass());
		for(AActor* TileActor : OverlappingTilesActors)
		{
			OverlappingTiles.Add(Cast<ATile>(TileActor));
		}
	
		TArray<AActor*> OverlappingCreaturesActors = GetOverlappingActors(ACreature::StaticClass());
		for(AActor* CreatureActor : OverlappingCreaturesActors)
		{
			CreaturesInSight.Add(Cast<ACreature>(CreatureActor));
		}
	}
	
	for (ATile* Tile : OverlappingTiles)
	{
		if(Tile->Type == ETileType::Obstacle)
			continue;
		
		// Is obstacle in the line of sight?
		static const FVector TileLocation = Tile->GetActorLocation();
		
		FHitResult HitResult;
		static FVector End = TileLocation - FVector(0,0,30);
		static FVector Start = OwnerLocation;
		Start.Z = End.Z;
		
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, FCollisionQueryParams()))
			continue;

		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 5);
		
		// Is in field of view?
		static FVector CreatureTileVector = (OwnerLocation - TileLocation).GetSafeNormal();
		static FVector CreatureForwardVector = Owner->GetActorForwardVector();

		static float DotProduct = FVector::DotProduct(CreatureTileVector, CreatureForwardVector);
		static float CrossProductMagnitude = FVector::CrossProduct(CreatureTileVector, CreatureForwardVector).Size();

		static float AngleInDegrees = FMath::RadiansToDegrees(FMath::Atan2(CrossProductMagnitude, DotProduct));

		if(AngleInDegrees * 2 > Owner->FieldOfView)
		{
			// Check if on any of the Tiles that are removed from the pool, 
			// were any creatures since it's less than 50% of all
			for(ACreature* Creature : CreaturesInSight)
			{
				if(Creature->CurrentTile == Tile)
					CreaturesInSight.Remove(Creature);
			}
			continue;
		}

		// Tile is in field of view. Check it's type.
		if(Tile->Type == ETileType::Land)
			continue;
		
		if(Tile->Type == ETileType::Water)
		{
			WaterTiles.Add(Tile);
		}
		else
		{
			PlantTiles.Add(Tile);
		}
	}
}

const TArray<ATile*>& UFovComponent::GetWaterTilesInSight() const
{
	return WaterTiles;
}

const TArray<ATile*>& UFovComponent::GetPlantTilesInSight() const
{
	return PlantTiles;
}

const TArray<ACreature*>& UFovComponent::GetCreaturesInSight() const
{
	return CreaturesInSight;
}


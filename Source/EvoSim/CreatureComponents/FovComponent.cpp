// Fill out your copyright notice in the Description page of Project Settings.


#include "FovComponent.h"

#include "ComponentReregisterContext.h"
#include "VectorTypes.h"
#include "EvoSim/Creature.h"
#include "EvoSim/Map/MapManager.h"
#include "EvoSim/Map/Tile.h"

UFovComponent::UFovComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFovComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACreature>(GetOwner());
	if(Owner == nullptr)
		UE_LOG(LogActorComponent, Log, TEXT("FovComponent | No Owner."));
}

void UFovComponent::UpdateTilesInSight()
{
	if(Owner->MapManager->Tiles.IsEmpty())
		return;
	
	WaterTiles.Empty();
	PlantTiles.Empty();
	MeatTiles.Empty();
	
	const FVector OwnerLocation3D = Owner->GetActorLocation();
	const FVector2D OwnerLocation = FVector2D(OwnerLocation3D.X, OwnerLocation3D.Y);

	for (ATile* Tile : Owner->MapManager->Tiles)
	{
		// Is correct type?
		if(Tile->Type != ETileType::Water && Tile->Type != ETileType::Plant)
			continue;
			
		const FVector TileLocation3D = Tile->GetActorLocation();
		const FVector2D TileLocation = FVector2D(TileLocation3D.X, TileLocation3D.Y);

		// Is correct distance away?
		if(UE::Geometry::Distance(TileLocation, OwnerLocation) > Owner->ViewDistance * 100)
			continue;

		// Is in field of view?
		FVector CreatureTileVector = (OwnerLocation3D - TileLocation3D).GetSafeNormal();
		FVector CreatureForwardVector = Owner->GetActorForwardVector();

		float DotProduct = FVector::DotProduct(CreatureTileVector, CreatureForwardVector);
		FVector CrossProduct = FVector::CrossProduct(CreatureTileVector, CreatureForwardVector);
		float CrossProductMagnitude = CrossProduct.Size();

		float AngleInRadians = FMath::Atan2(CrossProductMagnitude, DotProduct);
		float AngleInDegrees = FMath::RadiansToDegrees(AngleInRadians);

		if(AngleInDegrees * 2 > Owner->FieldOfView)
			continue;
		
		// Is obstacle in the way?
		FHitResult HitResult;
		FVector End = TileLocation3D;
		FVector Start = OwnerLocation3D;
		Start.Z = End.Z;
		
		if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_WorldStatic, FCollisionQueryParams()))
			continue;
		
		DrawDebugLine(GetWorld(), Start + FVector(0,0,30), End + FVector(0,0,30), FColor::Red, false, 0.0f, 0, 5);

		// Tile is in field of view.
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

const TArray<ATile*>& UFovComponent::GetMeatInSight() const
{
	return MeatTiles;
}


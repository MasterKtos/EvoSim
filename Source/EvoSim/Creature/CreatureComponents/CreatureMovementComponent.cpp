// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureMovementComponent.h"

#include "ComponentReregisterContext.h"
#include "VectorTypes.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Manager/SimManager.h"

UCreatureMovementComponent::UCreatureMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCreatureMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACreature>(GetOwner());
	if(!ensure(Owner))
	{
		UE_LOG(LogActorComponent, Log, TEXT("FovComponent | No Owner."));
		SetComponentTickEnabled(false);
		return;
	}

	Target = Owner->GetActorLocation();
	SimManager = Cast<USimManager>(GetWorld()->GetGameInstance());
}

void UCreatureMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(IsAtTarget())
		return;
	
	// Owner->SetActorLocation(FMath::VInterpConstantTo(Owner->GetActorLocation(), Target, DeltaTime, (2-SimManager->TickRate) * 120));
	Owner->SetActorLocation(Target);
}

void UCreatureMovementComponent::SetNewTarget(const FVector& NewTarget)
{
	Owner->SetActorLocation(Target);
	Target = NewTarget;
	
	// TODO: move this one to tick and lerp
	const FVector2D OwnerLocation2D = FVector2D(Owner->GetActorLocation().X, Owner->GetActorLocation().Y);
	const FVector2D Target2D = FVector2D(Target.X, Target.Y);
	const FVector2D VectorBetweenPoints = OwnerLocation2D - Target2D;
	const float NewYaw = FMath::Atan2(VectorBetweenPoints.Y, VectorBetweenPoints.X) * 180.0f / PI;
	Owner->SetActorRotation(FRotator(0, NewYaw, 0));
}

bool UCreatureMovementComponent::IsAtTarget() const
{
	return UE::Geometry::Distance(Owner->GetActorLocation(), Target) < 1;
}


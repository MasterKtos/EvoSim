// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureMovementComponent.h"

#include "ComponentReregisterContext.h"
#include "EvoSim/Creature/Creature.h"

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
}

void UCreatureMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(const FVector OwnerLocation = Owner->GetActorLocation(); OwnerLocation != Target)
		Owner->SetActorLocation(FMath::VInterpConstantTo(OwnerLocation, Target, DeltaTime, Owner->Speed));
}

void UCreatureMovementComponent::SetNewTarget(const FVector& NewTarget)
{
	Owner->SetActorLocation(Target);
	Target = NewTarget;
}


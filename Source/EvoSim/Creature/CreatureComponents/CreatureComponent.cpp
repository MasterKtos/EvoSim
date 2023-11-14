// Fill out your copyright notice in the Description page of Project Settings.


#include "CreatureComponent.h"

#include "ComponentReregisterContext.h"
#include "EvoSim/Creature/Creature.h"

// Called when the game starts
void UCreatureComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = Cast<ACreature>(GetOwner());
	if(!ensure(Owner))
		UE_LOG(LogActorComponent, Log, TEXT("No Owner (or owner is not a Creature)."));
}

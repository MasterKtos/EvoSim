// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CreatureComponent.generated.h"


class ACreature;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EVOSIM_API UCreatureComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	ACreature* Owner;
};

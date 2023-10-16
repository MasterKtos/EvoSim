// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EvoSim/Manager/ManagerInterface.h"
#include "AIComponent.generated.h"


enum class EDirection : uint8;
class ACreature;
class AAIManager;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVOSIM_API UAIComponent : public UActorComponent, public IManagerInterface
{
	GENERATED_BODY()

public:	
	UAIComponent();

	virtual void BeginPlay() override;

	virtual void Update() override;

private:
	UPROPERTY()
	ACreature* Owner;

	UPROPERTY()
	TArray<EDirection> MovesToDo;
};

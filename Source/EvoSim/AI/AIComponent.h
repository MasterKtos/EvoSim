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

	UFUNCTION()
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void Update() override;

private:
	UFUNCTION()
	void FindNewPath();
	
	UPROPERTY()
	ACreature* Owner;

	UPROPERTY()
	TArray<EDirection> MovesToDo;
};

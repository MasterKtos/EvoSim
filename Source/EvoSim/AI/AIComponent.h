// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "..\Manager\EvoSimLifetimeInterface.h"
#include "AIComponent.generated.h"


class UCreatureState;
enum class ECreatureStateName : uint8;
enum class EDirection : uint8;
class ACreature;
class AAIManager;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EVOSIM_API UAIComponent : public UActorComponent, public IEvoSimLifetime
{
	GENERATED_BODY()

public:	
	UAIComponent();

	UFUNCTION()
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void Update() override;

	UFUNCTION()
	bool ChangeCurrentState(ECreatureStateName NewStateName);

	UPROPERTY(BlueprintReadOnly)
	UCreatureState* CurrentCreatureState;
	
private:
	UFUNCTION()
	void FindNewPath();
	
	UPROPERTY()
	ACreature* Owner;

	UPROPERTY()
	TArray<EDirection> MovesToDo;

	UPROPERTY()
	TMap<ECreatureStateName, UCreatureState*> CreatureStateMap;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIManager.generated.h"

enum class EDirection : uint8;
class UAINode;
class ATile;

UCLASS()
class EVOSIM_API AAIManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAIManager();

	UFUNCTION(BlueprintCallable)
	static TArray<EDirection> FindPathToTile(ATile* From, ATile* To);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	static uint8 GetDistance(const UAINode* FromNode, const UAINode* ToNode);
	UFUNCTION()
	static TArray<EDirection> GetPath(UAINode* FromNode, UAINode* ToNode);
};

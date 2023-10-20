// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EvoSimLifetimeInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEvoSimLifetime : public UInterface
{
	GENERATED_BODY()
};

class EVOSIM_API IEvoSimLifetime
{
	GENERATED_BODY()

	public:
	virtual void Update() = 0;
};

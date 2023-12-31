﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "Carnivorous.generated.h"

UCLASS()
class EVOSIM_API ACarnivorous : public ACreature
{
	GENERATED_BODY()

public:
	ACarnivorous();

	virtual void Reproduce(bool bMother, ACreature* Partner) override;

	bool bIsHunting = false;
	
protected:
	virtual void BeginPlay() override;

};

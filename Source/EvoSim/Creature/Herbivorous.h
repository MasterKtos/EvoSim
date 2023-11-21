// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Creature.h"
#include "Herbivorous.generated.h"

class ACorpse;
class UAIComponentHerbivore;

UCLASS()
class EVOSIM_API AHerbivorous : public ACreature
{
	GENERATED_BODY()

public:
	AHerbivorous();

	virtual void Reproduce(bool bMother, ACreature* Partner) override;
	void GetHuntedDown(ACorpse* &Remains);
	
protected:
	virtual void BeginPlay() override;
};

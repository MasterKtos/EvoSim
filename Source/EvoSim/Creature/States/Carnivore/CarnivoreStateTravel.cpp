// Fill out your copyright notice in the Description page of Project Settings.


#include "CarnivoreStateTravel.h"

#include "EvoSim/AI/AIComponent.h"
#include "EvoSim/Creature/Carnivorous.h"
#include "EvoSim/Creature/Creature.h"
#include "EvoSim/Creature/CreatureComponents/FovComponent.h"
#include "EvoSim/Creature/CreatureComponents/NeedsEvaluatorComponent.h"
#include "EvoSim/Map/Tile.h"

void UCarnivoreStateTravel::GetTargetsInView()
{
	Super::GetTargetsInView();
	const auto Prey = Owner->FovComponent->GetCorpseTilesInSight();
	Food = Prey.IsEmpty() ? Owner->FovComponent->GetHerbCreaturesTilesInSight() : Prey;
	Bros = Owner->FovComponent->GetMeatCreaturesTilesInSight();
}

void UCarnivoreStateTravel::GetPathForCurrentNeed()
{
	Super::GetPathForCurrentNeed();

	if(!Owner->NeedsEvaluator->IsCurrentNeed(ECreatureNeed::Eat) || MovesToDo.IsEmpty())
		return;

	Cast<ACarnivorous>(Owner)->bIsHunting = true;

	for(const auto BroTile : Bros)
	{
		if(BroTile->CreaturesPresent.IsEmpty())
			continue;

		ACarnivorous* Bro;
		BroTile->CreaturesPresent.FindItemByClass<ACarnivorous>(&Bro);
		if(!IsValid(Bro))
			continue;

		if(!Bro->NeedsEvaluator->IsCurrentNeed(ECreatureNeed::Eat))
			continue;

		//retrace path;
		ATile* TempTile = Owner->CurrentTile;
		for(int i=MovesToDo.Num()-1; i>=0; i--)
		{
			TempTile = TempTile->GetNeighbour(MovesToDo[i]);
			if(!IsValid(TempTile))
				return;
		}
		Bro->AIComponent->ForcePathTo(TempTile);
	}
}

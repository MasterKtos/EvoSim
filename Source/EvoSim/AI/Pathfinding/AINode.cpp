// Fill out your copyright notice in the Description page of Project Settings.

#include "AINode.h"

int UAINode::CompareTo(UAINode* Other)
{
	int Diff = GetCost() - Other->GetCost(); 
	if(Diff == 0)
		Diff = DestinationCost - Other->DestinationCost;
	return -Diff;
}

bool UAINode::Equals(UAINode* Other)
{
	return this->Tile == Other->Tile;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AINodeHeap.generated.h"


class UAINode;

UCLASS()
class EVOSIM_API UAINodeHeap : public UObject
{
	GENERATED_BODY()
	
public:
	UAINodeHeap();
	void Init(int MaxItems);

	void Add(UAINode* Item);
	UAINode* RemoveFirst();
	void UpdateItem(UAINode* Item);
	
	bool Contains(const UAINode* Item);
	
	FORCEINLINE uint8 Num() const;
	
private:
	void SortUp(UAINode* Item);
	void SortDown(UAINode* Item);
	void SwapItems(UAINode* First, UAINode* Second);

	UPROPERTY()
	TArray<UAINode*> Items;
	
	uint8 CurrentItemCount = 0;
};

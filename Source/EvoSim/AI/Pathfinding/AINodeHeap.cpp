// Fill out your copyright notice in the Description page of Project Settings.


#include "AINodeHeap.h"

#include "AINode.h"

UAINodeHeap::UAINodeHeap()
{
}

void UAINodeHeap::Init(const int MaxItems)
{
	Items.Reserve(MaxItems);
}

void UAINodeHeap::Add(UAINode* Item)
{
	Item->HeapIndex = CurrentItemCount;
	Items.Insert(Item, CurrentItemCount);
	SortUp(Item);
	CurrentItemCount++;
}

UAINode* UAINodeHeap::RemoveFirst()
{
	UAINode* FirstItem = Items[0];
	
	CurrentItemCount--;
	Items[0] = Items[CurrentItemCount];
	Items[0]->HeapIndex = 0;
	
	SortDown(Items[0]);
	return FirstItem;
}

void UAINodeHeap::UpdateItem(UAINode* Item)
{
	SortUp(Item);
}

bool UAINodeHeap::Contains(const UAINode* Item)
{
	return Item == Items[Item->HeapIndex];
}

uint8 UAINodeHeap::Num() const
{
	return CurrentItemCount;
}

void UAINodeHeap::SortUp(UAINode* Item)
{
	while(true)
	{
		const int ParentIndex = (Item->HeapIndex - 1) / 2;
		
		if(Item->CompareTo(Items[ParentIndex]) <= 0)
			break;
		
		SwapItems(Item, Items[ParentIndex]);
	}
}

void UAINodeHeap::SortDown(UAINode* Item)
{
	while(true)
	{
		const int ChildIndexLeft = Item->HeapIndex * 2 + 1;
		const int ChildIndexRight = Item->HeapIndex * 2 + 2;

		if(ChildIndexLeft >= CurrentItemCount)
			return;
		
		int SwapIndex = ChildIndexLeft;
		
		if(ChildIndexRight < CurrentItemCount && Items[ChildIndexLeft]->CompareTo(Items[ChildIndexRight]) < 0)
			SwapIndex = ChildIndexRight;

		if(Item->CompareTo(Items[SwapIndex]) < 0)
		{
			SwapItems(Item, Items[SwapIndex]);
		}
		else return;
	}
}

void UAINodeHeap::SwapItems(UAINode* First, UAINode* Second)
{
	Items.Swap(First->HeapIndex, Second->HeapIndex);
	const int Temp = First->HeapIndex;
	First->HeapIndex = Second->HeapIndex;
	Second->HeapIndex = Temp;
}

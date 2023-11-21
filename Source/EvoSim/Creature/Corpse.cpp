// Fill out your copyright notice in the Description page of Project Settings.


#include "Corpse.h"

#include "EvoSim/Manager/SimManager.h"


ACorpse::ACorpse()
{
	PrimaryActorTick.bCanEverTick = true;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CorpseMesh"));
	RootComponent = SphereMesh;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(SphereMeshAsset.Object);
}

void ACorpse::Update()
{
	Lifetime--;
	if(Lifetime == 0)
	{
		GameInstance->RemoveFromUpdate(this);
		Destroy();
	}
}

void ACorpse::BeEaten()
{
	if(Durability-- == 0)
	{
		GameInstance->RemoveFromUpdate(this);
		Destroy();
	}
}

void ACorpse::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<USimManager>(GetGameInstance());
	GameInstance->AddToUpdate(this);
	Durability = GameInstance->CorpseDurability;
}



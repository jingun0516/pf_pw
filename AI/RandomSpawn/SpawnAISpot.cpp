// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RandomSpawn/SpawnAISpot.h"

// Sets default values
ASpawnAISpot::ASpawnAISpot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnAISpot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnAISpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


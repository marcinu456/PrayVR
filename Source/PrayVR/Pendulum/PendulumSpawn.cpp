// Created by Cookie Core


#include "PendulumSpawn.h"

// Sets default values
APendulumSpawn::APendulumSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APendulumSpawn::BeginPlay()
{
	Super::BeginPlay();

	APendulum* const SpawnedActorRef = GetWorld()->SpawnActor<APendulum>(PendulumClass, GetActorLocation(), GetActorRotation());

	PendulumActors.Add(SpawnedActorRef);

}

// Called every frame
void APendulumSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


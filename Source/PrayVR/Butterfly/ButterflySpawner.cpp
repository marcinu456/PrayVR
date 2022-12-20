// Created by Cookie Core


#include "ButterflySpawner.h"

#include "ButterflyActor.h"

// Sets default values
AButterflySpawner::AButterflySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AButterflySpawner::BeginPlay()
{
	Super::BeginPlay();

	TArray<UStaticMeshComponent*> Components;
	//ButterflyActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	//ensure(Components.Num() > 0);
	//const FVector Origin = GetActorLocation();

	//for (size_t i = 0; i < numberOfButterfly; i++)
	//{
	//	const FVector Loc(Origin.X + i * 15, Origin.Y, Origin.Z);
	//	AButterflyActor* const SpawnedActorRef = GetWorld()->SpawnActor<AButterflyActor>(ButterflyActor, Loc, GetActorRotation());
	//	ButterflyActors.Add(SpawnedActorRef);
	//
	//}
}

// Called every frame
void AButterflySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AButterflySpawner::UpdatePosition(FVector position)
{
	float LocalDeltaTime = ButterflyChange;


	position.X = (position.X + sigma * (position.Y - position.X) * LocalDeltaTime);
	position.Y = (position.Y + (-position.X * position.Z + rho * position.X - position.Y) * LocalDeltaTime);
	position.Z = (position.Z + (position.X * position.Y - beta * position.Z) * LocalDeltaTime);

	return position;

}
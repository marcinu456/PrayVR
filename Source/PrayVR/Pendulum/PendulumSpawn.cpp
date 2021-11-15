// Created by Cookie Core


#include "PendulumSpawn.h"
#include "MathUtil.h"
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

	int32 numberOfPendulus = 50;
	for (int32 i = 0; i < numberOfPendulus; i++)
	{
		APendulum* const SpawnedActorRef = GetWorld()->SpawnActor<APendulum>(PendulumClass, GetActorLocation(), GetActorRotation());
		//TSoftObjectPtr<APendulum> SpawnedActorRef = GetWorld()->SpawnActor<APendulum>(PendulumClass, GetActorLocation(), GetActorRotation());

		SpawnedActorRef->SetParameters(TMathUtilConstants<float>::Pi / 2.0 + 0.15, 150, 1, TMathUtilConstants<float>::Pi / 2.0 + 0.15 + 0.0001 * (i / float(numberOfPendulus)), 150, 1);


		PendulumActors.Add(SpawnedActorRef);
	}

}

// Called every frame
void APendulumSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


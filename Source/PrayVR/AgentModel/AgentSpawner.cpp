// Created by Cookie Core


#include "AgentSpawner.h"

#include "PlantAgent.h"
#include "RabbitAgent.h"
#include "WolfAgent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAgentSpawner::AAgentSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAgentSpawner::BeginPlay()
{
	Super::BeginPlay();

	const FVector Origin = GetActorLocation();

	TArray<UStaticMeshComponent*> Components;
	PlantActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	ensure(Components.Num() > 0);


	for (size_t i = 0; i < PLANT_COUNT; i++)
	{
		const FVector Loc(Origin.X + FMath::RandRange(-500, 500), Origin.Y + FMath::RandRange(-500, 500), Origin.Z);
		APlantAgent* const SpawnedActorRef = GetWorld()->SpawnActor<APlantAgent>(PlantActor, Loc, GetActorRotation());
		SpawnedActorRef->hp = PLANT_MAX_HP;
		//Plants.Add(SpawnedActorRef);
	}


	RabbitActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	ensure(Components.Num() > 0);


	for (size_t i = 0; i < RABBIT_COUNT; i++)
	{
		const FVector Loc(Origin.X + FMath::RandRange(-500, 500), Origin.Y + FMath::RandRange(-500, 500), Origin.Z);
		auto const SpawnedActorRef = GetWorld()->SpawnActor<ARabbitAgent>(RabbitActor, Loc, GetActorRotation());
		SpawnedActorRef->hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
		//Rabbits.Add(SpawnedActorRef);
	}


	WolfActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	ensure(Components.Num() > 0);


	for (size_t i = 0; i < WOLF_COUNT; i++)
	{
		const FVector Loc(Origin.X + FMath::RandRange(-500, 500), Origin.Y + FMath::RandRange(-500, 500), Origin.Z);
		auto const SpawnedActorRef = GetWorld()->SpawnActor<AWolfAgent>(WolfActor, Loc, GetActorRotation());
		SpawnedActorRef->hp = WOLF_MAX_HUNGRY_HP_LEVEL;
		//Wolfes.Add(SpawnedActorRef);
	}
}

// Called every frame
void AAgentSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// plant

	TArray<AActor*> Plants;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlantAgent::StaticClass(), Plants);

	if (iter % PLANT_REPRODUCE_TIME == 0 && Plants.Num() <= 5) {
		const FVector Origin = GetActorLocation();
		TArray<UStaticMeshComponent*> Components;
		PlantActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
		ensure(Components.Num() > 0);

		for (int i = 0; i < PLANT_REPRODUCE_COUNT; i++) {
			const FVector Loc(Origin.X + FMath::RandRange(-500, 500), Origin.Y + FMath::RandRange(-500, 500), Origin.Z);
			APlantAgent* const SpawnedActorRef = GetWorld()->SpawnActor<APlantAgent>(PlantActor, Loc, GetActorRotation());
			SpawnedActorRef->hp = PLANT_MAX_HP;
			//Plants.Add(SpawnedActorRef);
		}
		iter = 0;

	}



	// Rabbits
	TArray<AActor*> Rabbits;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARabbitAgent::StaticClass(), Rabbits);

	if (Rabbits.Num() == 0)
	{
		const FVector Origin = GetActorLocation();
		TArray<UStaticMeshComponent*> Components;
		RabbitActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
		ensure(Components.Num() > 0);
		for (int i = 0; i < RABBIT_COUNT; i++) {
			const FVector Loc(Origin.X + FMath::RandRange(-500, 500), Origin.Y + FMath::RandRange(-500, 500), Origin.Z);
			auto const SpawnedActorRef = GetWorld()->SpawnActor<ARabbitAgent>(RabbitActor, Loc, GetActorRotation());
			SpawnedActorRef->hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
		}
	}



	// Wolfes

	TArray<AActor*> Wolfes;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWolfAgent::StaticClass(), Wolfes);

	if (Wolfes.Num() <= 0)
	{
		const FVector Origin = GetActorLocation();
		TArray<UStaticMeshComponent*> Components;
		WolfActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
		ensure(Components.Num() > 0);
		for (int i = 0; i < WOLF_COUNT; i++) {
			const FVector Loc(Origin.X + FMath::RandRange(-500, 500), Origin.Y + FMath::RandRange(-500, 500), Origin.Z);
			auto const SpawnedActorRef = GetWorld()->SpawnActor<AWolfAgent>(WolfActor, Loc, GetActorRotation());
			SpawnedActorRef->hp = WOLF_MAX_HUNGRY_HP_LEVEL;
		}
	}


	iter++;
}



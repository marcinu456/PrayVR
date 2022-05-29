// Created by Cookie Core


#include "AgentSpawner.h"

#include "AgentControl.h"
#include "PlantAgent.h"
#include "RabbitAgent.h"
#include "WolfAgent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAgentSpawner::AAgentSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	ControlBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ControlBar"));
	ControlBar->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AAgentSpawner::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);

	auto AgentActionBar = Cast<UAgentControl>(ControlBar->GetUserWidgetObject());
	if (AgentActionBar)
	{
		AgentActionBar->SetParentPicker(this);
	}

	//const FVector Origin = GetActorLocation();
	//
	//TArray<UStaticMeshComponent*> Components;
	//PlantActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	//ensure(Components.Num() > 0);
	//
	//
	//for (size_t i = 0; i < PLANT_COUNT; i++)
	//{
	//	const FVector Loc(Origin.X + FMath::RandRange(-50, 50), Origin.Y + FMath::RandRange(-50, 50), Origin.Z);
	//	APlantAgent* const SpawnedActorRef = GetWorld()->SpawnActor<APlantAgent>(PlantActor, Loc, GetActorRotation());
	//	SpawnedActorRef->hp = PLANT_MAX_HP;
	//	//Plantser.Add(SpawnedActorRef);
	//}
	//
	//
	//RabbitActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	//ensure(Components.Num() > 0);
	//
	//
	//for (size_t i = 0; i < RABBIT_COUNT; i++)
	//{
	//	const FVector Loc(Origin.X + FMath::RandRange(-50, 50), Origin.Y + FMath::RandRange(-50, 50), Origin.Z);
	//	auto const SpawnedActorRef = GetWorld()->SpawnActor<ARabbitAgent>(RabbitActor, Loc, GetActorRotation());
	//	SpawnedActorRef->hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
	//	//Rabbits.Add(SpawnedActorRef);
	//}
	//
	//
	//WolfActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	//ensure(Components.Num() > 0);
	//
	//
	//for (size_t i = 0; i < WOLF_COUNT; i++)
	//{
	//	const FVector Loc(Origin.X + FMath::RandRange(-50, 50), Origin.Y + FMath::RandRange(-50, 50), Origin.Z);
	//	auto const SpawnedActorRef = GetWorld()->SpawnActor<AWolfAgent>(WolfActor, Loc, GetActorRotation());
	//	SpawnedActorRef->hp = WOLF_MAX_HUNGRY_HP_LEVEL;
	//	//Wolfes.Add(SpawnedActorRef);
	//}
}

// Called every frame
void AAgentSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	// plant

	//TArray<AActor*> Plantser;

	TArray<APlantAgent*> Plants;
	TArray<ARabbitAgent*> Rabbits;
	TArray<AWolfAgent*> Wolfes;


	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlantAgent::StaticClass(), Plantser);


	for(auto& AgentBase: AgentBases)
	{
		auto CastPlantsSpawner = Cast<APlantAgent>(AgentBase);
		if (CastPlantsSpawner)
		{
			Plants.Add(CastPlantsSpawner);
		}
		auto CastWolfesSpawner = Cast<AWolfAgent>(AgentBase);
		if (CastWolfesSpawner)
		{
			Wolfes.Add(CastWolfesSpawner);
		}
		auto CastRabbitsSpawner = Cast<ARabbitAgent>(AgentBase);
		if (CastRabbitsSpawner)
		{
			Rabbits.Add(CastRabbitsSpawner);
		}
	}



	if (iter % PLANT_REPRODUCE_TIME == 0 && Plants.Num() <= 5) {
		const FVector Origin = GetActorLocation();
		TArray<UStaticMeshComponent*> Components;
		PlantActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
		ensure(Components.Num() > 0);

		for (int i = 0; i < PLANT_REPRODUCE_COUNT; i++) {
			const FVector Loc(Origin.X + FMath::RandRange(-SizeOfSpawn/2, SizeOfSpawn/2), Origin.Y + FMath::RandRange(-SizeOfSpawn/2, SizeOfSpawn/2), Origin.Z);
			APlantAgent* const SpawnedActorRef = GetWorld()->SpawnActor<APlantAgent>(PlantActor, Loc, GetActorRotation());
			if (SpawnedActorRef)
			{
				SpawnedActorRef->hp = PLANT_MAX_HP;
				SpawnedActorRef->SetUpAgent(true);
			}
			//Plantser.Add(SpawnedActorRef);
		}
		iter = 0;

	}



	// Rabbits

	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARabbitAgent::StaticClass(), Rabbits);


	if (Rabbits.Num() == 0)
	{
		const FVector Origin = GetActorLocation();
		TArray<UStaticMeshComponent*> Components;
		RabbitActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
		ensure(Components.Num() > 0);
		for (int i = 0; i < RABBIT_COUNT; i++) {
			const FVector Loc(Origin.X + FMath::RandRange(-SizeOfSpawn/2, SizeOfSpawn/2), Origin.Y + FMath::RandRange(-SizeOfSpawn/2, SizeOfSpawn/2), Origin.Z);
			auto const SpawnedActorRef = GetWorld()->SpawnActor<ARabbitAgent>(RabbitActor, Loc, GetActorRotation());
			if (SpawnedActorRef)
			{
				SpawnedActorRef->hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
				SpawnedActorRef->SetUpAgent(true);
			}
		}
	}



	// Wolfes


	//UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWolfAgent::StaticClass(), Wolfes);


	if (Wolfes.Num() <= 0)
	{
		const FVector Origin = GetActorLocation();
		TArray<UStaticMeshComponent*> Components;
		WolfActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
		ensure(Components.Num() > 0);
		for (int i = 0; i < WOLF_COUNT; i++) {
			const FVector Loc(Origin.X + FMath::RandRange(-SizeOfSpawn/2, SizeOfSpawn/2), Origin.Y + FMath::RandRange(-SizeOfSpawn/2, SizeOfSpawn/2), Origin.Z);
			auto const SpawnedActorRef = GetWorld()->SpawnActor<AWolfAgent>(WolfActor, Loc, GetActorRotation());
			if (SpawnedActorRef)
			{
				SpawnedActorRef->hp = WOLF_MAX_HUNGRY_HP_LEVEL;
				SpawnedActorRef->SetUpAgent(true);
			}
		}
	}


	iter++;

	//UE_LOG(LogTemp, Warning, TEXT("numberofagents %d"), AgentBases.Num());

	for(int32 i=0; i< AgentBases.Num();i++)
	{
		if(FVector::Dist(AgentBases[i]->GetActorLocation(), GetActorLocation())> SizeOfSpawn)
		{
			AgentBases[i]->OnDestroy();
			break;
		}
	}

}

void AAgentSpawner::RespondToOnPlayerJump(float location)
{
	UE_LOG(LogTemp, Warning, TEXT("AAgentSpawner::WhenPlayerJump %f"),location);

}

void AAgentSpawner::AddAgent(AAgentBase* _Agent)
{
	if (AgentBases.Num() < 120)
	{
		AgentBases.Add(_Agent);
	}
	else
	{
		_Agent->OnDestroy();
	}

	//UE_LOG(LogTemp, Warning, TEXT("AAgentSpawner::AddAgent(AAgentBase* _Agent)"));
	//auto CastSpawner = Cast<ARabbitAgent>(_Agent);
	//if(CastSpawner)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("CastAsRabbit"));
	//}
	UE_LOG(LogTemp, Warning, TEXT("numberofagents %d"), AgentBases.Num());
}

void AAgentSpawner::DeleteAgent(AAgentBase* _Agent)
{
	AgentBases.Remove(_Agent);

	UE_LOG(LogTemp, Warning, TEXT("numberofagents %d"), AgentBases.Num());
}

void AAgentSpawner::StartAgents()
{
	UE_LOG(LogTemp, Warning, TEXT("AAgentSpawner::StartAgents()"));




	SetActorTickEnabled(true);

	for (int32 i = 0; i < AgentBases.Num(); i++)
	{
		AgentBases[i]->SetUpAgent(true);
	}

}

void AAgentSpawner::ResetAgents()
{
	UE_LOG(LogTemp, Warning, TEXT("AAgentSpawner::ResetAgentsd()"));
	SetActorTickEnabled(false);

	for (int32 i = 0; i < AgentBases.Num(); i++)
	{
		AgentBases[i]->SetUpAgent(false);
	}
}



// Created by Cookie Core


#include "PlantAgent.h"

APlantAgent::APlantAgent()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

void APlantAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (hp != 0) {
		hp--;
	}
	else {
		OnDestroy();
	}
}
// Created by Cookie Core


#include "ButterflyActor.h"

// Sets default values
AButterflyActor::AButterflyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CellRootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButterflyMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AButterflyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AButterflyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaTime = ButterflyChange;
	auto position = GetActorLocation();

	position.X = (position.X + sigma * (position.Y - position.X) * DeltaTime);
	position.Y = (position.Y + (-position.X * position.Z + rho * position.X - position.Y) * DeltaTime);
	position.Z = (position.Z + (position.X * position.Y - beta * position.Z) * DeltaTime);

	position.X += 100;

	SetActorLocation(position);
}


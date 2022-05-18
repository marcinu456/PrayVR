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
	DeltaTime = 0.002;
	auto position = GetActorLocation();

	position.X = (position.X + 10.0 * (position.Y - position.X) * DeltaTime)* ButterflyChange;
	position.Y = (position.Y + (-position.X * position.Z + 28.0 * position.X - position.Y) * DeltaTime)*ButterflyChange;
	position.Z = (position.Z + (position.X * position.Y - (8.0 / 3.0) * position.Z) * DeltaTime)* ButterflyChange;

	SetActorLocation(position);
}


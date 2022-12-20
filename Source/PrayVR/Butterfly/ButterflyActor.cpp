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
	
	//StaticMeshComponent->SetWorldLocation(GetActorLocation());
	//StaticMeshComponent->SetRelativeLocation(GetActorLocation());
	for (int32 i = 0; i < 10; i++)
	{
		//auto StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ButterflyMesh"));
		//StaticMeshComponent->SetupAttachment(RootComponent);
		StaticMeshComponents.Add(StaticMeshComponent);
	}
}

// Called every frame
void AButterflyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(bIsCPPTick)
	{
		for(auto& StaticMesh : StaticMeshComponents)
		{
			auto pos = UpdatePosition(StaticMesh->GetRelativeLocation());
			StaticMesh->SetRelativeLocation(pos);
		}
		//auto position = GetActorLocation();
		//auto position = StaticMeshComponent->GetComponentToWorld().GetLocation();

		//SetActorLocation(UpdatePosition(position));
		//StaticMeshComponent->SetWorldLocation(position);
	}
}

FVector AButterflyActor::UpdatePosition(FVector position)
{
	float LocalDeltaTime = ButterflyChange;


	position.X = (position.X + sigma * (position.Y - position.X) * LocalDeltaTime);
	position.Y = (position.Y + (-position.X * position.Z + rho * position.X - position.Y) * LocalDeltaTime);
	position.Z = (position.Z + (position.X * position.Y - beta * position.Z) * LocalDeltaTime);

	return position;
	
}
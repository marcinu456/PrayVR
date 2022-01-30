// Created by Cookie Core


#include "PlantAgent.h"

#include "Components/SphereComponent.h"

APlantAgent::APlantAgent()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	Sphere1->InitSphereRadius(100.0f);
	Sphere1->SetupAttachment(StaticMeshComponent);

	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &APlantAgent::OnOverlapBegin);       // set up a notification for when this component overlaps something
	Sphere1->OnComponentEndOverlap.AddDynamic(this, &APlantAgent::OnOverlapEnd);
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

void APlantAgent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void APlantAgent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
}

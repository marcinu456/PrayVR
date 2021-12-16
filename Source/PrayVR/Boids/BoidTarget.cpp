// Created by Cookie Core


#include "BoidTarget.h"

// Sets default values
ABoidTarget::ABoidTarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ABoidTarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABoidTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


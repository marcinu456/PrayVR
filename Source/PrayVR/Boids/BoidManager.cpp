// Created by Cookie Core


#include "BoidManager.h"

// Sets default values
ABoidManager::ABoidManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoidManager::BeginPlay()
{
	Super::BeginPlay();
}


void ABoidManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!Active) {
		return;
	}


	if (ManagedBoids.Num() != 0) {
		for (ABoid* Boid : ManagedBoids) {
			Boid->CalculateBoidRotation();
			Boid->UpdateBoidRotation(DeltaTime);
			Boid->CalculateBoidPosition(DeltaTime);
			Boid->UpdateBoidPosition();
		}
	}
}

void ABoidManager::AddManagedBoid(ABoid* Boid) {
	ManagedBoids.AddUnique(Boid);
	//UE_LOG(LogTemp, Log, TEXT("Start managing %s"), *Boid->GetName());
}

void ABoidManager::RemoveManagedBoid(ABoid* Boid) {
	ManagedBoids.Remove(Boid);
	//UE_LOG(LogTemp, Log, TEXT("Stop managing %s"), *Boid->GetName());
}


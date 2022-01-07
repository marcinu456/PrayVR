// Created by Cookie Core

#include "AgentBase.h"

// Sets default values
AAgentBase::AAgentBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAgentBase::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAgentBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAgentBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AAgentBase::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}


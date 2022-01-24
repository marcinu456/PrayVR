// Created by Cookie Core

#include "AgentBase.h"

#include "AgentSpawner.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

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

	TArray<AActor*> Spawners;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAgentSpawner::StaticClass(), Spawners);


	for (auto& Spawner : Spawners)
	{
		auto CastSpawner = Cast<AAgentSpawner>(Spawner);
		CastSpawner->AddAgent(this);
	}

	Sphere1->SetGenerateOverlapEvents(false);

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

void AAgentBase::OnDestroy()
{
	TArray<AActor*> Spawners;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAgentSpawner::StaticClass(), Spawners);


	for (auto& Spawner : Spawners)
	{
		auto CastSpawner = Cast<AAgentSpawner>(Spawner);
		CastSpawner->DeleteAgent(this);
	}
	UE_LOG(LogTemp, Warning, TEXT("AAgentBase::OnDestroy()"));

	Destroy();
}

void AAgentBase::SetOverlap(bool bOverlap)
{
	Sphere1->SetGenerateOverlapEvents(bOverlap);

}

void AAgentBase::SetBasicMaterial()
{
	if(StaticMeshComponent)
	StaticMeshComponent->SetMaterial(0, BasicMaterial);

	//UE_LOG(LogTemp, Warning, TEXT("  AAgentBase::SetBasicMaterial()"));

}

void AAgentBase::SetBeginMaterial()
{
	if (StaticMeshComponent)
	StaticMeshComponent->SetMaterial(0, BeginOverMaterial);
}

void AAgentBase::SetClickedMaterial()
{
	if (StaticMeshComponent)
	StaticMeshComponent->SetMaterial(0, ClickedMaterial);
}


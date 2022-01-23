// Created by Cookie Core


#include "WolfAgent.h"

#include "AgentSpawner.h"
#include "RabbitAgent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AWolfAgent::AWolfAgent()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);


	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	Sphere1->InitSphereRadius(100.0f);
	Sphere1->SetupAttachment(StaticMeshComponent);

	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &AWolfAgent::OnOverlapBegin);       // set up a notification for when this component overlaps something
	Sphere1->OnComponentEndOverlap.AddDynamic(this, &AWolfAgent::OnOverlapEnd);

	//Sphere1->SetGenerateOverlapEvents(false);


}

void AWolfAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

void AWolfAgent::Move()
{
	Super::Move();

	// Wolfes


	if (hp <= WOLF_MAX_HUNGRY_HP_LEVEL) {
		TArray<AActor*> Rabbits;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARabbitAgent::StaticClass(), Rabbits);

		if (Rabbits.Num() > 0) {
			size_t atractorIndex = 0;
			auto atractor = Rabbits[atractorIndex]->GetActorLocation() - GetActorLocation();
			float atractortDist = atractor.Size();
			for (int j = 1; j < Rabbits.Num(); j++) {
				auto rabbit = Rabbits[j];
				auto vec = rabbit->GetActorLocation() - GetActorLocation();
				float dist = vec.Size();
				if (dist < atractortDist) {
					atractorIndex = j;
					atractor = vec;
					atractortDist = dist;
				}
			}
			SetActorLocation(GetActorLocation() + atractor / atractortDist * WOLF_VELOCITY);

			atractorRabbit = Cast<ARabbitAgent>(Rabbits[atractorIndex]);

			//if ((GetActorLocation() - Rabbits[atractorIndex]->GetActorLocation()).Size() < SIZE) {
			//	Rabbits.RemoveAt(atractorIndex);
			//	hp = WOLF_MAX_HP;
			//}
		}
	}
	else {
		TArray<AActor*> Wolfes;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWolfAgent::StaticClass(), Wolfes);

		int i = 0;
		for (int j = 0; j < Wolfes.Num(); j++) {

			if (Cast<AWolfAgent>(Wolfes[j]) == this)
			{
				i = j;
				break;
			}

		}


		size_t atractorIndex = 0;
		auto atractor = GetActorLocation();
		float atractortDist = 1000;
		for (int j = 1; j < Wolfes.Num(); j++) {
			auto partner = Cast<AWolfAgent>(Wolfes[j]);
			auto vec = partner->GetActorLocation() - GetActorLocation();
			float dist = vec.Size();
			if (dist < atractortDist && partner->hp > WOLF_MAX_HUNGRY_HP_LEVEL && j != i) {
				atractorIndex = j;
				atractor = vec;
				atractortDist = dist;
			}
		}
		auto partner = Cast<AWolfAgent>(Wolfes[atractorIndex]);

		if (this != partner) {
			SetActorLocation(GetActorLocation() + atractor / atractortDist * WOLF_VELOCITY);

			atractorWolf = partner;

		}
	}

	if (hp != 0) {
		hp--;
	}
	else {
		OnDestroy();
	}

	//if(FVector::Dist(AgentSpawner->GetActorLocation(), GetActorLocation()) > 200)
	//{
	//	OnDestroy();
	//}
}


void AWolfAgent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (Cast<ARabbitAgent>(OtherActor) == atractorRabbit && atractorRabbit)
	{
		atractorRabbit->OnDestroy();
		hp = WOLF_MAX_HP;
		atractorRabbit = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Some Wolf warning castActor"));
	}
	else if (Cast<AWolfAgent>(OtherActor) == atractorWolf && atractorWolf)
	{
		UE_LOG(LogTemp, Warning, TEXT("Some warning OtherActor"));

		hp = WOLF_MAX_HUNGRY_HP_LEVEL;
		atractorWolf->hp = WOLF_MAX_HUNGRY_HP_LEVEL;
		for (int j = 0; j < WOLF_REPRODUCE_COUNT; j++) {

			//TArray<UStaticMeshComponent*> Components;
			//
			//WolfActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
			//ensure(Components.Num() > 0);

			const FVector Loc(GetActorLocation().X + FMath::RandRange(-50, 50), GetActorLocation().Y + FMath::RandRange(-50, 50), GetActorLocation().Z);
			auto const SpawnedActorRef = GetWorld()->SpawnActor<AWolfAgent>(WolfActor, Loc, GetActorRotation());
			SpawnedActorRef->hp = WOLF_MAX_HUNGRY_HP_LEVEL;
		}
		atractorWolf = nullptr;
	}


}

void AWolfAgent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	if (Cast<ARabbitAgent>(OtherActor) == atractorRabbit && atractorRabbit)
	{
		atractorRabbit = nullptr;
	}
	else if (Cast<AWolfAgent>(OtherActor) == atractorWolf && atractorWolf)
	{
		atractorWolf = nullptr;
	}



}
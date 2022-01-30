// Created by Cookie Core


#include "RabbitAgent.h"

#include "AgentSpawner.h"
#include "PlantAgent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

ARabbitAgent::ARabbitAgent()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	Sphere1 = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	Sphere1->InitSphereRadius(100.0f);
	Sphere1->SetupAttachment(StaticMeshComponent);

	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &ARabbitAgent::OnOverlapBegin);       // set up a notification for when this component overlaps something
	Sphere1->OnComponentEndOverlap.AddDynamic(this, &ARabbitAgent::OnOverlapEnd);

	//Sphere1->SetGenerateOverlapEvents(false);
}

//void ARabbitAgent::SetBasicMaterial()
//{
//	Super::SetBasicMaterial();
//
//	if (StaticMeshComponent)
//		StaticMeshComponent->SetMaterial(0, BasicMaterial);
//}
//
//void ARabbitAgent::SetBeginMaterial()
//{
//	Super::SetBeginMaterial();
//
//	if (StaticMeshComponent)
//		StaticMeshComponent->SetMaterial(0, BeginOverMaterial);
//}
//
//void ARabbitAgent::SetClickedMaterial()
//{
//	Super::SetClickedMaterial();
//
//	if (StaticMeshComponent)
//		StaticMeshComponent->SetMaterial(0, ClickedMaterial);
//}

void ARabbitAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}

void ARabbitAgent::Move()
{
	Super::Move();

	float ConstantZ = GetActorLocation().Z;

	if (hp <= RABBIT_MAX_HUNGRY_HP_LEVEL) {
		TArray<AActor*> Plants;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlantAgent::StaticClass(), Plants);
		if (Plants.Num() > 0) {
			size_t atractorIndex = 0;
			auto atractor = Cast<APlantAgent>(Plants[atractorIndex])->GetActorLocation() - GetActorLocation();
			float atractortDist = atractor.Size();// Plants[atractorIndex]->GetActorLocation(), rabbit->GetActorLocation());
			for (int j = 1; j < Plants.Num(); j++) {
				auto* plant = Cast<APlantAgent>(Plants[j]);
				FVector vec = plant->GetActorLocation() - GetActorLocation();
				float dist = vec.Size();// FVector::Distance(plant->GetActorLocation(), rabbit->GetActorLocation());
				if (dist < atractortDist) {
					atractorIndex = j;
					atractor = vec;
					atractortDist = dist;
				}
			}
			//UE_LOG(LogTemp, Warning, TEXT("atractor X=%f , Y=%f / atractortDist %f "), atractor.X, atractor.Y, atractortDist);
			SetActorLocation(GetActorLocation() + atractor / atractortDist * RABBIT_VELOCITY);
			//UE_LOG(LogTemp, Warning, TEXT("Some warning message"));

			atractorPlant = Cast<APlantAgent>(Plants[atractorIndex]);

			//if ((GetActorLocation() - Plants[atractorIndex]->GetActorLocation()).Size() < SIZE) {
			//	Plants[atractorIndex]->Destroy();
			//	Plants.RemoveAt(atractorIndex);
			//
			//	hp = RABBIT_MAX_HP;
			//}

		}
	}
	else {
		TArray<AActor*> Rabbits;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ARabbitAgent::StaticClass(), Rabbits);

		int i = 0;
		for (int j = 0; j < Rabbits.Num(); j++) {

			if (Cast<ARabbitAgent>(Rabbits[j]) == this)
			{
				i = j;
				break;
			}

		}


		size_t atractorIndex = 0;
		auto atractor = GetActorLocation();
		float atractortDist = 1000;
		for (int j = 1; j < Rabbits.Num(); j++) {
			auto partner = Cast<ARabbitAgent>(Rabbits[j]);
			auto vec = partner->GetActorLocation() - GetActorLocation();
			float dist = vec.Size();
			if (dist < atractortDist && partner->hp > RABBIT_MAX_HUNGRY_HP_LEVEL && j != i) {
				atractorIndex = j;
				atractor = vec;
				atractortDist = dist;
			}
		}
		auto partner = Cast<ARabbitAgent>(Rabbits[atractorIndex]);
		if (this != partner) {
			SetActorLocation(GetActorLocation() + atractor / atractortDist * RABBIT_VELOCITY);

			atractorRabbit = partner;

		}
	}

	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, ConstantZ));


	if (hp != 0) {
		hp--;
	}
	else {
		OnDestroy();
	}

	//if (FVector::Dist(AgentSpawner->GetActorLocation(), GetActorLocation()) > 200)
	//{
	//	OnDestroy();
	//}
}

void ARabbitAgent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (Cast<APlantAgent>(OtherActor) == atractorPlant && atractorPlant)
	{
		atractorPlant->OnDestroy();
		hp = RABBIT_MAX_HP;
		atractorPlant = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("Some Rabbit warning castActor"));
	}
	else if (Cast<ARabbitAgent>(OtherActor) == atractorRabbit && atractorRabbit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Some warning OtherActor"));
		hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
		atractorRabbit->hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
		for (int j = 0; j < RABBIT_REPRODUCE_COUNT; j++) {

			//TArray<UStaticMeshComponent*> Components;
			//
			//RabbitActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
			//ensure(Components.Num() > 0);

			const FVector Loc(GetActorLocation().X + FMath::RandRange(-50, 50), GetActorLocation().Y + FMath::RandRange(-50, 50), GetActorLocation().Z);
			auto const SpawnedActorRef = GetWorld()->SpawnActor<ARabbitAgent>(RabbitActor, Loc, GetActorRotation());
			if (SpawnedActorRef)
			{
				SpawnedActorRef->hp = RABBIT_MAX_HUNGRY_HP_LEVEL;
				SpawnedActorRef->SetUpAgent(true);
			}

		}
		atractorRabbit = nullptr;

	}

}

void ARabbitAgent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	Super::OnOverlapEnd(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	if (Cast<APlantAgent>(OtherActor) == atractorPlant && atractorPlant)
	{
		atractorPlant = nullptr;

	}
	else if (Cast<ARabbitAgent>(OtherActor) == atractorRabbit && atractorRabbit)
	{
		atractorRabbit = nullptr;
	}

}
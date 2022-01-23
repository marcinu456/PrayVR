// Created by Cookie Core


#include "AgentSpawnBox.h"

#include "RabbitAgent.h"
#include "PrayVR/Butterfly/ButterflyActor.h"
#include "PrayVR/Character/HandController.h"
#include "PrayVR/Character/Agents/HandController_Agents.h"

// Sets default values
AAgentSpawnBox::AAgentSpawnBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	StaticMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AAgentSpawnBox::OnOverlapBegin);       // set up a notification for when this component overlaps something
	StaticMeshComponent->OnComponentEndOverlap.AddDynamic(this, &AAgentSpawnBox::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AAgentSpawnBox::BeginPlay()
{
	Super::BeginPlay();

	if (AgentSpawnActor)
	{

		
	}
}

// Called every frame
void AAgentSpawnBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAgentSpawnBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	ActorCast = Cast<AHandController_Agents>(OtherActor);


}

void AAgentSpawnBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//ActorCast = Cast<AHandController_Agents>(OtherActor);

	if (ActorCast && AgentSpawnActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("AAgentSpawnBox::OnOverlapEnd"));
		//const FVector Origin = GetActorLocation();

		//const FVector Loc(Origin.X + FMath::RandRange(-500, 500), Origin.Y + FMath::RandRange(-500, 500), Origin.Z);
		//auto const SpawnedActorRef = GetWorld()->SpawnActor<AAgentBase>(AgentSpawnActor, Loc, GetActorRotation());
		//SpawnedActorRef->SetActorTickEnabled(false);
		//SpawnedActorRef->SetActorLocation(ActorCast->GetActorLocation());
		//SpawnedActorRef->AttachToActor(OtherActor, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
	}

	if(ActorCast == Cast<AHandController_Agents>(OtherActor))
	{
		ActorCast = nullptr;
	}

	//TODO find why agent component crash editor/ probobly error with overlap, added to agent hand controller info about agents
	//TODO find if i can spawn with agent base
	//TODO 3 bp child, next move to agent hand contoller and create rest with board for agents, and better movable
}

void AAgentSpawnBox::SpawnAgent()
{
	if (ActorCast && AgentSpawnActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("AAgentSpawnBox::OnOverlapBegin"));


		if (ActorCast)
		{
			const FVector Origin = GetActorLocation();

			const FVector Loc(Origin.X + FMath::RandRange(-500, 500), Origin.Y + FMath::RandRange(-500, 500), Origin.Z);
			auto const SpawnedActorRef = GetWorld()->SpawnActor<AAgentBase>(AgentSpawnActor, ActorCast->GetActorLocation(), ActorCast->GetActorRotation());
			ActorCast->Agent = SpawnedActorRef;
			SpawnedActorRef->AttachToActor(ActorCast, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
		}
	}
}


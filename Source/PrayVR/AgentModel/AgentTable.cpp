// Created by Cookie Core


#include "AgentTable.h"

#include "AgentBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AAgentTable::AAgentTable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("SphereCollision"));

	BoxCollision->SetupAttachment(StaticMeshComponent);

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAgentTable::OnOverlapBegin);       // set up a notification for when this component overlaps something
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AAgentTable::OnOverlapEnd);
}

// Called when the game starts or when spawned
void AAgentTable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAgentTable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAgentTable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AAgentTable::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
}

void AAgentTable::SetUpAgent(AAgentBase* Agent)
{

	if(Agent)
	{
		auto AgentLoc = Agent->GetActorLocation();
		auto AgentRot = Agent->GetActorRotation();

		auto NewAgentLoc = FVector(AgentLoc.X, AgentLoc.Y, GetActorLocation().Z+10);
		auto NewAgentRoc = FRotator(GetActorRotation().Pitch, AgentRot.Yaw, GetActorRotation().Roll);
		Agent->SetActorLocationAndRotation(NewAgentLoc, NewAgentRoc);
	}
}


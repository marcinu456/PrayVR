// Created by Cookie Core


#include "PendulumSpawn.h"
#include "MathUtil.h"
#include "PendulumControl.h"
// Sets default values
APendulumSpawn::APendulumSpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	//ControlBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ControlBar"));
	//ControlBar->SetupAttachment(GetRootComponent());

	CurrentNumberOfPendulum = 0;
	MaxNumberOfPendulum = 50;
}

// Called when the game starts or when spawned
void APendulumSpawn::BeginPlay()
{
	Super::BeginPlay();

	//auto PaintingActionBar = Cast<UPendulumControl>(ControlBar->GetUserWidgetObject());
	//if (PaintingActionBar)
	//{
	//	PaintingActionBar->SetParentPicker(this);
	//}


}

// Called every frame
void APendulumSpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APendulumSpawn::AddPendulum()
{
	if (CurrentNumberOfPendulum < MaxNumberOfPendulum)
	{
		CurrentNumberOfPendulum++;
		APendulum* const SpawnedActorRef = GetWorld()->SpawnActor<APendulum>(PendulumClass, GetActorLocation(), GetActorRotation());
		//TSoftObjectPtr<APendulum> SpawnedActorRef = GetWorld()->SpawnActor<APendulum>(PendulumClass, GetActorLocation(), GetActorRotation());

		SpawnedActorRef->SetParameters(TMathUtilConstants<float>::Pi / 2.0 + 0.15, 150, 1, TMathUtilConstants<float>::Pi / 2.0 + 0.15 + 0.0001 * (CurrentNumberOfPendulum / float(MaxNumberOfPendulum)), 150, 1);


		PendulumActors.Add(SpawnedActorRef);

	}
}

void APendulumSpawn::DeletePendulum()
{
	if (CurrentNumberOfPendulum > 0 && PendulumActors.Num() > 0)
	{
		CurrentNumberOfPendulum--;
		auto SpawnedActorRef = PendulumActors.Pop();
		SpawnedActorRef->Destroy();
		//UE_LOG(LogTemp, Warning, TEXT("Some warning DeletePendulum %f"), PendulumActors.Num());

	}
}

void APendulumSpawn::StartPendulum()
{

	for (auto& Pendulum : PendulumActors)
	{
		Pendulum->SetActorTickEnabled(true);
		UE_LOG(LogTemp, Warning, TEXT("Some warning StartPendulum"));

	}

}

void APendulumSpawn::ResetPendulum()
{

	for (auto& Pendulum : PendulumActors)
	{
		Pendulum->SetActorTickEnabled(false);
		Pendulum->ResetParameters();

	}

}
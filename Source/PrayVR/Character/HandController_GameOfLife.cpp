// Created by Cookie Core


#include "HandController_GameOfLife.h"

#include "Components/StaticMeshComponent.h"

AHandController_GameOfLife::AHandController_GameOfLife()
{
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetupAttachment(GetRootComponent());
}

void AHandController_GameOfLife::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TraceForward();
}

void AHandController_GameOfLife::TriggerPressed()
{
	Super::TriggerPressed();

	TraceForward();
	if (FocusActor)
	{
		auto  CastInterface = Cast<ACellActor>(FocusActor);
		if (CastInterface)
		{
			CastInterface->Clicked();
		}
	}

}

void AHandController_GameOfLife::TriggerReleased()
{
	Super::TriggerReleased();
}

void AHandController_GameOfLife::TraceForward()
{

	FHitResult Hit;


	bool bHit = ThirdPersonCameraInteraction(Hit);
	


	if (bHit)
	{
		auto HitActor = Hit.GetActor();

		if (HitActor != FocusActor)
		{
			if (FocusActor)
			{
				ACellActor* CastInterface = Cast<ACellActor>(FocusActor);
				if (CastInterface)
				{
					CastInterface->EndCursorOver();
				}
			}
			ACellActor* CastInterface = Cast<ACellActor>(HitActor);
			if (CastInterface)
			{
				CastInterface->BeginCursorOver();
			}
			FocusActor = Cast<ACellActor>(HitActor);
		}

	}
	else
	{
		ACellActor* CastInterface = Cast<ACellActor>(FocusActor);
		if (CastInterface)
		{
			CastInterface->EndCursorOver();
		}
		FocusActor = nullptr;
	}
}

bool AHandController_GameOfLife::ThirdPersonCameraInteraction(FHitResult& Hit)
{
	FVector Loc;
	FRotator Rot;

	Rot = Cube->GetComponentRotation();
	Loc = Cube->GetComponentLocation();

	
	GetActorForwardVector();
	auto StartLocation = Loc;//FirstPersonCameraComponent->GetComponentLocation();
	auto EndLocation = StartLocation + (Rot.Vector() * InteractRange);//FirstPersonCameraComponent->GetForwardVector() * InteractRange;

	return GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility);
}

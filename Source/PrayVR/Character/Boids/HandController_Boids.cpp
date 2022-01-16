// Created by Cookie Core


#include "HandController_Boids.h"

#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PrayVR/Boids/BoidTarget.h"

AHandController_Boids::AHandController_Boids()
{
	StartTarget = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StartTarget"));
	StartTarget->SetupAttachment(GetRootComponent());
	StartTarget->CastShadow = false;

	DestinationTarget = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestinationTarget"));
	DestinationTarget->SetupAttachment(GetRootComponent());
	DestinationTarget->CastShadow = false;

	TargetPos = 200;
}

void AHandController_Boids::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHandController_Boids::TriggerPressed()
{
	Super::TriggerPressed();
	Pointer->PressPointerKey(EKeys::LeftMouseButton);
	//UE_LOG(LogTemp, Error, TEXT("AHandController_Boids::TriggerPressed()"));

}

void AHandController_Boids::TriggerReleased()
{
	Super::TriggerReleased();
	Pointer->ReleasePointerKey(EKeys::LeftMouseButton);

}

void AHandController_Boids::GripPressed()
{
	Super::GripPressed();

	//UE_LOG(LogTemp, Warning, TEXT("AHandController_Boids::GripPressed()"));


	auto Frector = StartTarget->GetRelativeLocation();
	auto Srector = StartTarget->GetForwardVector();
	FVector StarPos1 = Frector;

	FVector EndPos1 = FVector(Srector.X+ TargetPos, Srector.Y, Srector.Z);;// *1800;




	UE_LOG(LogTemp, Warning, TEXT("AHandController_Boids::GripPressed %f"), TargetPos);

	//TODO zamiast actora zrób kompent tutaj i do niego niech ci¹gn¹ te boidsy

	BoidTarget = Cast<ABoidTarget>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoidTarget::StaticClass()));
	if (!BoidTarget) {
		UE_LOG(LogTemp, Error, TEXT("Failed to find BoidTarget in scene"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Finded BoidTarget in scene"));
		DestinationTarget->SetRelativeLocation(EndPos1);// *TargetPos);
		BoidTarget->SetActorLocation(Srector+TargetPos);// *TargetPos);
	}
}

void AHandController_Boids::GripReleased()
{
	Super::GripReleased();

	UE_LOG(LogTemp, Warning, TEXT("AHandController_Boids::GripReleased()"));

}

void AHandController_Boids::ThumbStick(float Rate)
{
	Super::ThumbStick(Rate);

	if(TargetPos>= 200)
	{
		TargetPos += Rate;
	}
	else
	{
		TargetPos= 200;
	}


}

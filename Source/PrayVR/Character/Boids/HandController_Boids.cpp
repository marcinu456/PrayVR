// Created by Cookie Core


#include "HandController_Boids.h"

AHandController_Boids::AHandController_Boids()
{

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

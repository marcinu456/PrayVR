// Created by Cookie Core


#include "HandController.h"


AHandController::AHandController()
{
	PrimaryActorTick.bCanEverTick = true;

	MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("MotionController"));
	SetRootComponent(MotionController);
	MotionController->SetShowDeviceModel(true);
}

void AHandController::BeginPlay()
{
	Super::BeginPlay();

}

void AHandController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Created by Cookie Core


#include "VRPawnBoids.h"

#include "Components/InputComponent.h"

// Sets default values
AVRPawnBoids::AVRPawnBoids()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);
}

// Called when the game starts or when spawned
void AVRPawnBoids::BeginPlay()
{
	Super::BeginPlay();
	if (RightHandControllerClass)
	{
		RightHandController = GetWorld()->SpawnActor<AHandController>(RightHandControllerClass);
		RightHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightHandController->SetOwner(this);
		RightHandController->SetHand(EControllerHand::Right);
	}
	if (LeftHandControllerClass)
	{
		LeftHandController = GetWorld()->SpawnActor<AHandController>(LeftHandControllerClass);
		LeftHandController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		LeftHandController->SetOwner(this);
		LeftHandController->SetHand(EControllerHand::Left);
	}
}


// Called to bind functionality to input
void AVRPawnBoids::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("TriggerRight"), EInputEvent::IE_Pressed, this, &AVRPawnBoids::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("TriggerRight"), EInputEvent::IE_Released, this, &AVRPawnBoids::RightTriggerReleased);
}


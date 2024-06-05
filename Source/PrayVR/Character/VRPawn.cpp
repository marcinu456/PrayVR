// Created by Cookie Core


#include "VRPawn.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Engine/World.h"

#include "UObject/Object.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "NavigationSystem.h"
#include "Components/PostProcessComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "MotionControllerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

AVRPawn::AVRPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	VRRoot = CreateDefaultSubobject<USceneComponent>(TEXT("VRRoot"));
	SetRootComponent(VRRoot);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRRoot);

	TargetPath = CreateDefaultSubobject<USplineComponent>(TEXT("TargetPath"));
	TargetPath->SetupAttachment(VRRoot);

	TargetDestinationMarker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestinationMarker"));
	TargetDestinationMarker->SetupAttachment(GetRootComponent());
	TargetDestinationMarker->SetCollisionProfileName("NoCollision");
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	// Epic Comment :D // Setup Player Height for various Platforms (PS4, Vive, Oculus)
	FName DeviceName = UHeadMountedDisplayFunctionLibrary::GetHMDDeviceName();

	if (DeviceName == "SteamVR" || DeviceName == "OculusHMD")
	{
		// Epic Comment :D // Windows (Oculus / Vive)
//		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::LocalFloor);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Some warning message %s"), *DeviceName.ToString());

	TargetDestinationMarker-> SetVisibility(false);


	if (RightHandControllerClass)
	{
		RightController = GetWorld()->SpawnActor<AHandController>(RightHandControllerClass);
		RightController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		RightController->SetOwner(this);
		RightController->SetHand(EControllerHand::Right);
	}
	if (LeftHandControllerClass)
	{
		LeftController = GetWorld()->SpawnActor<AHandController>(LeftHandControllerClass);
		LeftController->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::SnapToTargetIncludingScale);
		LeftController->SetOwner(this);
		LeftController->SetHand(EControllerHand::Left);
	}
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateDestinationMarker();
}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("GripLeft"), IE_Pressed, this, &AVRPawn::GripLeft);
	PlayerInputComponent->BindAction(TEXT("GripLeft"), IE_Released, this, &AVRPawn::ReleaseLeft);
	PlayerInputComponent->BindAction(TEXT("GripRight"), IE_Pressed, this, &AVRPawn::GripRight);
	PlayerInputComponent->BindAction(TEXT("GripRight"), IE_Released, this, &AVRPawn::ReleaseRight);
	PlayerInputComponent->BindAction(TEXT("TriggerRight"), EInputEvent::IE_Pressed, this, &AVRPawn::RightTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("TriggerRight"), EInputEvent::IE_Released, this, &AVRPawn::RightTriggerReleased);
	PlayerInputComponent->BindAction(TEXT("TriggerLeft"), EInputEvent::IE_Pressed, this, &AVRPawn::LeftTriggerPressed);
	PlayerInputComponent->BindAction(TEXT("TriggerLeft"), EInputEvent::IE_Released, this, &AVRPawn::LeftTriggerPressed);

	PlayerInputComponent->BindAction(TEXT("ResetVR"), IE_Pressed, this, &AVRPawn::ResetVR);

}

bool AVRPawn::FindTeleportDestination(TArray<FVector>& OutPath, FVector& OutLocation)
{
	if (!RightController)
	{
		return false;
	}
	FVector Start = RightController->GetActorLocation();

	FVector Look = RightController->GetActorForwardVector();


	//FPredictProjectilePathParams Params(TeleportProjectileRadius, Start, Look * TeleportProjectileSpeed,
	//	TeleportSimulationTime, ECC_Visibility, this);

	//Params.bTraceComplex = true; //You can disable if you have better collision on scene

	FPredictProjectilePathResult Result;

	//bool bHit = UGameplayStatics::PredictProjectilePath(this, Params, Result);

	//if (!bHit)
	//{
	//	return false;
	//}
	//
	//
	////OutPath.Empty();
	//for (auto& PointData : Result.PathData)
	//{
	//	OutPath.Add(PointData.Location);
	//}
	//
	//FNavLocation NavLocation;
	//bool bOnNavMesh = UNavigationSystemV1::GetCurrent(GetWorld())->ProjectPointToNavigation(Result.HitResult.Location, NavLocation, TeleportProjectionExtent);
	//
	//if (!bOnNavMesh)
	//{
	//	return false;
	//}
	//
	//OutLocation = NavLocation.Location;

	return true;
}

void AVRPawn::UpdateDestinationMarker()
{
	TArray<FVector> Path;
	FVector Location;
	bool bHasDestination = FindTeleportDestination(Path, Location);

	if (bHasDestination)
	{
		TargetDestinationMarker-> SetWorldLocation(Location);
		TargetDestinationMarker-> SetVisibility(true);

		DrawTeleportPath(Path);
	}
	else
	{
		TargetDestinationMarker-> SetVisibility(false);
		DrawTeleportPath(TArray<FVector>());

	}

}


void AVRPawn::DrawTeleportPath(const TArray<FVector>& Path)
{
	UpdateSpline(Path);

	for (auto SplineMesh : TargetPathMeshPool)
	{
		SplineMesh->SetVisibility(false);
	}

	int32 SegmentNum = Path.Num() - 1;
	for (int32 i = 0; i < SegmentNum; ++i)
	{
		if (TargetPathMeshPool.Num() <= i)
		{
			USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
			SplineMesh->SetMobility(EComponentMobility::Movable);
			SplineMesh->AttachToComponent(TargetPath, FAttachmentTransformRules::KeepRelativeTransform);
			SplineMesh->SetStaticMesh(TargetArchMesh);
			SplineMesh->SetMaterial(0, TargetArchMaterial);
			SplineMesh->RegisterComponent();

			TargetPathMeshPool.Add(SplineMesh);
		}

		USplineMeshComponent* SplineMesh = TargetPathMeshPool[i];
		SplineMesh->SetVisibility(true);

		FVector StarPos, StartTangent, EndPos, EndTangent;
		TargetPath->GetLocalLocationAndTangentAtSplinePoint(i, StarPos, StartTangent);
		TargetPath->GetLocalLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent);
		SplineMesh->SetStartAndEnd(StarPos, StartTangent, EndPos, EndTangent);
	}


}

void AVRPawn::UpdateSpline(const TArray<FVector>& Path)
{
	TargetPath->ClearSplinePoints(false);
	int32 index = 0;
	for (auto& Point : Path)
	{
		FVector LocalPosition = TargetPath->GetComponentTransform().InverseTransformPosition(Point);
		TargetPath->AddPoint(FSplinePoint(index, LocalPosition, ESplinePointType::Curve), false);
		index++;
	}

	TargetPath->UpdateSpline();
}

void AVRPawn::ResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
	UE_LOG(LogTemp, Warning, TEXT("Some warning ResetVR"));
}

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

	TeleportPath = CreateDefaultSubobject<USplineComponent>(TEXT("TeleportPath"));
	TeleportPath->SetupAttachment(VRRoot);

	DestinationMarker = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DestinationMarker"));
	DestinationMarker->SetupAttachment(GetRootComponent());
	DestinationMarker->SetCollisionProfileName("NoCollision");

	PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComponent"));
	PostProcessComponent->SetupAttachment(GetRootComponent());
}

void AVRPawn::BeginPlay()
{
	Super::BeginPlay();

	// Epic Comment :D // Setup Player Height for various Platforms (PS4, Vive, Oculus)
	FName DeviceName = UHeadMountedDisplayFunctionLibrary::GetHMDDeviceName();

	if (DeviceName == "SteamVR" || DeviceName == "OculusHMD")
	{
		// Epic Comment :D // Windows (Oculus / Vive)
		UHeadMountedDisplayFunctionLibrary::SetTrackingOrigin(EHMDTrackingOrigin::Floor);
	}

	UE_LOG(LogTemp, Warning, TEXT("Some warning message %s"), *DeviceName.ToString());

	DestinationMarker->SetVisibility(false);

	if (BlinkerMaterialBase)
	{
		BlinkerMaterialInstance = UMaterialInstanceDynamic::Create(BlinkerMaterialBase, this);
		PostProcessComponent->AddOrUpdateBlendable(BlinkerMaterialInstance);

		BlinkerMaterialInstance->SetScalarParameterValue("RadiusSize", .6);
	}


	if (HandControllerClass)
	{
		LeftController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
		if (LeftController)
		{
			LeftController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
			LeftController->SetOwner(this);
			LeftController->SetHand(EControllerHand::Left);
		}

		RightController = GetWorld()->SpawnActor<AHandController>(HandControllerClass);
		if (RightController)
		{
			RightController->AttachToComponent(VRRoot, FAttachmentTransformRules::KeepRelativeTransform);
			RightController->SetOwner(this);
			RightController->SetHand(EControllerHand::Right);
		}

		if (RightController && LeftController)
		{
			LeftController->PairController(RightController);
		}
	}
}

// Called every frame
void AVRPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewCameraOffset = Camera->GetComponentLocation() - GetActorLocation();
	NewCameraOffset.Z = 0;
	AddActorWorldOffset(NewCameraOffset);
	VRRoot->AddWorldOffset(-NewCameraOffset);

	UpdateDestinationMarker();
	UpdateBlinkers();


}

// Called to bind functionality to input
void AVRPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move_Y"), this, &AVRPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Move_X"), this, &AVRPawn::MoveRight);
	PlayerInputComponent->BindAction(TEXT("Teleport"), IE_Released, this, &AVRPawn::BeginTeleport);
	PlayerInputComponent->BindAction(TEXT("GripLeft"), IE_Pressed, this, &AVRPawn::GripLeft);
	PlayerInputComponent->BindAction(TEXT("GripLeft"), IE_Released, this, &AVRPawn::ReleaseLeft);
	PlayerInputComponent->BindAction(TEXT("GripRight"), IE_Pressed, this, &AVRPawn::GripRight);
	PlayerInputComponent->BindAction(TEXT("GripRight"), IE_Released, this, &AVRPawn::ReleaseRight);
}

bool AVRPawn::FindTeleportDestination(TArray<FVector>& OutPath, FVector& OutLocation)
{
	if (!RightController)
	{
		return false;
	}
	FVector Start = RightController->GetActorLocation();

	FVector Look = RightController->GetActorForwardVector();


	FPredictProjectilePathParams Params(TeleportProjectileRadius, Start, Look * TeleportProjectileSpeed,
		TeleportSimulationTime, ECC_Visibility, this);

	Params.bTraceComplex = true; //You can disable if you have better collision on scene

	FPredictProjectilePathResult Result;

	bool bHit = UGameplayStatics::PredictProjectilePath(this, Params, Result);

	if (!bHit)
	{
		return false;
	}


	//OutPath.Empty();
	for (auto& PointData : Result.PathData)
	{
		OutPath.Add(PointData.Location);
	}

	FNavLocation NavLocation;
	bool bOnNavMesh = UNavigationSystemV1::GetCurrent(GetWorld())->ProjectPointToNavigation(Result.HitResult.Location, NavLocation, TeleportProjectionExtent);

	if (!bOnNavMesh)
	{
		return false;
	}

	OutLocation = NavLocation.Location;

	return true;
}

void AVRPawn::UpdateDestinationMarker()
{
	TArray<FVector> Path;
	FVector Location;
	bool bHasDestination = FindTeleportDestination(Path, Location);

	if (bHasDestination)
	{
		DestinationMarker->SetWorldLocation(Location);
		DestinationMarker->SetVisibility(true);

		DrawTeleportPath(Path);
	}
	else
	{
		DestinationMarker->SetVisibility(false);
		DrawTeleportPath(TArray<FVector>());

	}

}

void AVRPawn::UpdateBlinkers()
{
	if (!RadiusVsVelocity)
	{
		return;
	}
	float Speed = GetVelocity().Size();
	float Radius = RadiusVsVelocity->GetFloatValue(Speed);
	BlinkerMaterialInstance->SetScalarParameterValue("RadiusSize", Radius);

	FVector2D Centre = GetBlinkerCentre();

	BlinkerMaterialInstance->SetVectorParameterValue("Centre", FLinearColor(Centre.X, Centre.Y, 0));

}

void AVRPawn::DrawTeleportPath(const TArray<FVector>& Path)
{
	UpdateSpline(Path);

	for (auto SplineMesh : TeleportPathMeshPool)
	{
		SplineMesh->SetVisibility(false);
	}

	int32 SegmentNum = Path.Num() - 1;
	for (int32 i = 0; i < SegmentNum; ++i)
	{
		if (TeleportPathMeshPool.Num() <= i)
		{
			USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
			SplineMesh->SetMobility(EComponentMobility::Movable);
			SplineMesh->AttachToComponent(TeleportPath, FAttachmentTransformRules::KeepRelativeTransform);
			SplineMesh->SetStaticMesh(TeleportArchMesh);
			SplineMesh->SetMaterial(0, TeleportArchMaterial);
			SplineMesh->RegisterComponent();

			TeleportPathMeshPool.Add(SplineMesh);
		}

		USplineMeshComponent* SplineMesh = TeleportPathMeshPool[i];
		SplineMesh->SetVisibility(true);

		FVector StarPos, StartTangent, EndPos, EndTangent;
		TeleportPath->GetLocalLocationAndTangentAtSplinePoint(i, StarPos, StartTangent);
		TeleportPath->GetLocalLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent);
		SplineMesh->SetStartAndEnd(StarPos, StartTangent, EndPos, EndTangent);
	}


}

void AVRPawn::UpdateSpline(const TArray<FVector>& Path)
{
	TeleportPath->ClearSplinePoints(false);
	int32 index = 0;
	for (auto& Point : Path)
	{
		FVector LocalPosition = TeleportPath->GetComponentTransform().InverseTransformPosition(Point);
		TeleportPath->AddPoint(FSplinePoint(index, LocalPosition, ESplinePointType::Curve), false);
		index++;
	}

	TeleportPath->UpdateSpline();
}

FVector2D AVRPawn::GetBlinkerCentre()
{
	return FVector2D(.5, .5);
	/* Maybe Sometimes
	FVector MovementDirection = GetVelocity().GetSafeNormal();
	if(MovementDirection.IsNearlyZero())
	{
		return FVector2D(.5, .5);
	}
	FVector WorldStationaryLaction;

	if(FVector::DotProduct(Camera->GetForwardVector(),MovementDirection)>0)
	{
		WorldStationaryLaction = Camera->GetComponentLocation() + MovementDirection * 100;
	}
	else
	{
		WorldStationaryLaction = Camera->GetComponentLocation() - MovementDirection * 100;
	}

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC)
	{
		return FVector2D(.5, .5);
	}

	FVector2D ScreenStationaryLocation;
	PC->ProjectWorldLocationToScreen(WorldStationaryLaction, ScreenStationaryLocation);

	int32 SizeX, SizeY;
	PC->GetViewportSize(SizeX, SizeY);
	ScreenStationaryLocation.X /= SizeX;
	ScreenStationaryLocation.Y /= SizeY;
	return ScreenStationaryLocation;
	*/
}

void AVRPawn::MoveForward(float throttle)
{
	AddMovementInput(throttle * Camera->GetForwardVector());
}

void AVRPawn::MoveRight(float throttle)
{
	AddMovementInput(throttle * Camera->GetRightVector());
}


void AVRPawn::BeginTeleport()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	StartFade(0, 1);
	FTimerHandle Handle;

	GetWorldTimerManager().SetTimer(Handle, this, &AVRPawn::FinishTeleport, TeleportFadeTime, false);
}

void AVRPawn::FinishTeleport()
{
	FVector Destination = DestinationMarker->GetComponentLocation();
	Destination +=/* GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * */ GetActorUpVector();
	SetActorLocation(Destination);
	StartFade(1, 0);
}

void AVRPawn::StartFade(float FromAlpha, float ToAlpha)
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (PC)
	{
		PC->PlayerCameraManager->StartCameraFade(FromAlpha, ToAlpha, TeleportFadeTime, FLinearColor::Black);
	}
}
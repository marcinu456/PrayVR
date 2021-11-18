// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "HandController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "VRCharacter.generated.h"

UCLASS(config = Game)
class PRAYVR_API AVRCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVRCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool FindTeleportDestination(TArray<FVector>& OutPath, FVector& OutLocation);
	void UpdateDestinationMarker();
	void UpdateBlinkers();
	void DrawTeleportPath(const TArray<FVector>& Path);
	void UpdateSpline(const TArray<FVector>& Path);
	FVector2D GetBlinkerCentre();

	void MoveForward(float throttle);
	void MoveRight(float throttle);

	void GripLeft() { LeftController->Grip(); }
	void ReleaseLeft() { LeftController->Release(); }
	void GripRight() { RightController->Grip(); }
	void ReleaseRight() { RightController->Release(); }


	void SetupTeleport();
	void BeginTeleport();
	void FinishTeleport();

	void StartFade(float FromAlpha, float ToAlpha);

	void ResetVR();

	void Rotation(float Rotate);

	void TurnAtRate(float Rate);

	DECLARE_DELEGATE_OneParam(FFooDelegate, float);

private:

	UPROPERTY(VisibleAnywhere)
		class USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
		class UCameraComponent* Camera;

	UPROPERTY()
		AHandController* LeftController;
	UPROPERTY()
		AHandController* RightController;



	UPROPERTY(VisibleAnywhere)
		class USplineComponent* TeleportPath;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* DestinationMarker;

	UPROPERTY()
		class UPostProcessComponent* PostProcessComponent;

	UPROPERTY()
		class UMaterialInstanceDynamic* BlinkerMaterialInstance;

	UPROPERTY()
		TArray<class USplineMeshComponent*> TeleportPathMeshPool;

private: // Configuration Parameters

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(EditAnywhere)
		float TeleportProjectileRadius = 10;

	UPROPERTY(EditAnywhere)
		float TeleportProjectileSpeed = 800;

	UPROPERTY(EditAnywhere)
		float TeleportSimulationTime = 2;

	UPROPERTY(EditAnywhere)
		float TeleportFadeTime = 1;

	UPROPERTY(EditAnywhere)
		FVector TeleportProjectionExtent = FVector(100, 100, 100);

	UPROPERTY(EditAnywhere)
		class UMaterialInterface* BlinkerMaterialBase;

	UPROPERTY(EditAnywhere)
		class UCurveFloat* RadiusVsVelocity;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMesh* TeleportArchMesh;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface* TeleportArchMaterial;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AHandController> HandControllerClass;

	bool bStarTeleport = false;

	FVector StartLocation;


	void RightTriggerPressed() { if (RightController) RightController->TriggerPressed(); }
	void RightTriggerReleased() { if (RightController) RightController->TriggerReleased(); }

	void LeftTriggerPressed() { if (LeftController) LeftController->TriggerPressed(); }
	void LeftTriggerReleased() { if (LeftController) LeftController->TriggerReleased(); }


};

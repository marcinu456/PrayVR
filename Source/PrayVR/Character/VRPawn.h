// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Camera/CameraComponent.h"
#include "HandController.h"
#include "VRPawn.generated.h"

UCLASS()
class PRAYVR_API AVRPawn : public APawn
{
	GENERATED_BODY()

public:
	AVRPawn();

protected:
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	bool FindTeleportDestination(TArray<FVector>& OutPath, FVector& OutLocation);
	void UpdateDestinationMarker();
	void DrawTeleportPath(const TArray<FVector>& Path);
	void UpdateSpline(const TArray<FVector>& Path);


	void GripLeft() { LeftController->GripPressed(); }
	void ReleaseLeft() { LeftController->GripReleased(); }

	void GripRight() { RightController->GripPressed(); }
	void ReleaseRight() { RightController->GripReleased(); }

	void RightTriggerPressed() { if (RightController) RightController->TriggerPressed(); }
	void RightTriggerReleased() { if (RightController) RightController->TriggerReleased(); }

	void LeftTriggerPressed() { if (LeftController) LeftController->TriggerPressed(); }
	void LeftTriggerReleased() { if (LeftController) LeftController->TriggerReleased(); }

	void ResetVR();


private:

	// Components
	UPROPERTY(VisibleAnywhere)
		USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	UPROPERTY()
		AHandController* LeftController;
	UPROPERTY()
		AHandController* RightController;

	UPROPERTY(VisibleAnywhere)
		class USplineComponent* TargetPath;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMesh* TargetArchMesh;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface* TargetArchMaterial;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* TargetDestinationMarker; //TODO CreateTargetActorComponent

	UPROPERTY()
		TArray<class USplineMeshComponent*> TargetPathMeshPool;

private: // Configuration Parameters

	// Config
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AHandController> RightHandControllerClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AHandController> LeftHandControllerClass;



};

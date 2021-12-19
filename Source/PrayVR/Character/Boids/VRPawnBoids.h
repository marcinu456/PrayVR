// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "PrayVR/Character/HandController.h"
#include "VRPawnBoids.generated.h"

UCLASS()
class PRAYVR_API AVRPawnBoids : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVRPawnBoids();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
private:

	void RightTriggerPressed() { if (RightHandController) RightHandController->TriggerPressed(); }
	void RightTriggerReleased() { if (RightHandController) RightHandController->TriggerReleased(); }



	// Config
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AHandController> RightHandControllerClass;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AHandController> LeftHandControllerClass;



	// Components
	UPROPERTY(VisibleAnywhere)
		USceneComponent* VRRoot;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* Camera;

	// Reference
	UPROPERTY()
		AHandController* RightHandController;

	UPROPERTY()
		AHandController* LeftHandController;
};

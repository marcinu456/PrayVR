// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MotionControllerComponent.h"

#include "HandController.generated.h"

UCLASS()
class PRAYVR_API AHandController : public AActor
{
	GENERATED_BODY()

public:
	AHandController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetHand(EControllerHand Hand) { MotionController->SetTrackingSource(Hand); }

private:
	// Components
	UPROPERTY(VisibleAnywhere)
		UMotionControllerComponent* MotionController;

};
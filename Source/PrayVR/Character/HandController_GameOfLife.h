// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "HandController.h"
#include "PrayVR/GameOfLife/CellActor.h"
#include "HandController_GameOfLife.generated.h"

/**
 * 
 */
UCLASS()
class PRAYVR_API AHandController_GameOfLife : public AHandController
{
	GENERATED_BODY()
public:
	AHandController_GameOfLife();

	void Tick(float DeltaTime) override;


	void TriggerPressed() override;
	void TriggerReleased() override;


private:

	void TraceForward();

	UFUNCTION(BlueprintCallable, Category = Interaction)
		bool ThirdPersonCameraInteraction(FHitResult& Hit);

	ACellActor* FocusActor;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* Cube;

	UPROPERTY(EditAnywhere)
		float InteractRange = 500;
};

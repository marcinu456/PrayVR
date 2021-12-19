// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "PrayVR/Character/HandController.h"
#include "HandController_Boids.generated.h"

/**
 * 
 */
UCLASS()
class PRAYVR_API AHandController_Boids : public AHandController
{
	GENERATED_BODY()
public:
	AHandController_Boids();

	void Tick(float DeltaTime) override;


	void TriggerPressed() override;
	void TriggerReleased() override;


private:


	//TODO add targetBoids
};

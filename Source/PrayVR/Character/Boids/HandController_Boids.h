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
protected:
	void BeginPlay() override;
public:
	void Tick(float DeltaTime) override;


	void TriggerPressed() override;
	void TriggerReleased() override;

	void GripPressed() override;
	void GripReleased() override;

	void ThumbStick(float Rate) override;

private:


	//TODO add targetBoids


	//UPROPERTY()
	//	TArray<class USplineMeshComponent*> ColumnsPathMeshPool;

	//UPROPERTY(VisibleAnywhere)
	//	class USplineComponent* TargetSpline;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* StartTarget;
	UPROPERTY(EditDefaultsOnly)
		class UStaticMeshComponent* DestinationTarget;

	//UPROPERTY(EditDefaultsOnly)
	//	class UMaterialInterface* FirstColumnArchMaterial;

	float TargetPos;

	class ABoidTarget* BoidTarget;

	bool Grip;

	void MoveTarget();
};

// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

struct FOtherBoidInfo {
	ABoid* Other;
	float Distance;

	FOtherBoidInfo(ABoid* Other_,
		float Distance_) : Other(Other_), Distance(Distance_) {
	}
};

UCLASS()
class PRAYVR_API ABoid : public AActor
{
	GENERATED_BODY()
	
public:
	ABoid();

	virtual void CalculateBoidRotation();

	virtual void UpdateBoidRotation(float DeltaTime);

	virtual void CalculateBoidPosition(float DeltaTime);

	virtual void UpdateBoidPosition();

	virtual TArray<ABoid*> CalculateClosestBoids(int32 Amount);

protected:
	virtual void BeginPlay() override;

	virtual void BeginDestroy() override;

	virtual void CalculateSeparation(FVector& Spearation, ABoid* Boid);

	virtual void CalculateAlignment(FVector& Alignment, ABoid* Boid);

	virtual void CalculateCohesion(FVector& Cohesion, ABoid* Boid);

	virtual FVector CalculateTarget();

protected:
	// Components
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UBoxComponent* BoxCollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UArrowComponent* ArrowComponent;

	// Settings

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (ClampMin = "1"))
		int32 AmountOfBoidsToObserve = 10;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
		float ForwardSpeed = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
		float TurnSpeed = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
		float CloseBoidDistanceCutOff = 300.f;

private:
	class ABoidManager* Manager;

	class ABoidTarget* BoidTarget;

	FRotator NextBoidRotation;
	FVector NextBoidWorldOffset;

};

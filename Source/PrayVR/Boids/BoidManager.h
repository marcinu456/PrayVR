// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "Boid.h"
#include "GameFramework/Actor.h"
#include "BoidManager.generated.h"

UCLASS(Config = Boids)
class PRAYVR_API ABoidManager : public AActor
{
	GENERATED_BODY()
	
public:
	ABoidManager();

public:
	virtual void Tick(float DeltaTime) override;

	virtual void AddManagedBoid(ABoid* Boid);

	virtual void RemoveManagedBoid(ABoid* Boid);

	bool IsBoidsFollowTarget() const { return BoidsFollowTarget; }

	float GetSeparationWeight() const { return SeparationWeight; }

	float GetAlignmentWeight() const { return AlignmentWeight; }

	float GetCohesionWeight() const { return CohesionWeight; }

	float GetTargetWeight() const { return TargetWeight; }

	TArray<ABoid*> GetManagedBoids() const { return ManagedBoids; }

protected:
	virtual void BeginPlay() override;

protected:
	// Settings
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings")
		bool Active = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		bool BoidsFollowTarget = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float SeparationWeight = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float AlignmentWeight = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float CohesionWeight = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
		float TargetWeight = 2.f;

	// Info
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Info")
		TArray<ABoid*> ManagedBoids;

};

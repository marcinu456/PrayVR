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

	void SetBoidsFollowTarget(bool bFollow)
	{
		BoidsFollowTarget = bFollow;
		UE_LOG(LogTemp, Warning, TEXT("SetBoidsFollowTarget"));

	}

	float GetSeparationWeight() const { return SeparationWeight; }

	void SetSeparationWeight(float value)
	{
		SeparationWeight = value;
	}

	float GetAlignmentWeight() const { return AlignmentWeight; }

	void SetAlignmentWeight(float value)
	{
		AlignmentWeight = value;
	}

	float GetCohesionWeight() const { return CohesionWeight; }

	void SetCohesionWeight(float value)
	{
		CohesionWeight = value;
	}

	float GetTargetWeight() const { return TargetWeight; }

	void SetTargetWeight(float value)
	{
		TargetWeight = value;
	}

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

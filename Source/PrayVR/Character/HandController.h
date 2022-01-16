// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "MotionControllerComponent.h"
#include "Components/WidgetInteractionComponent.h"

#include "HandController.generated.h"

UCLASS()
class PRAYVR_API AHandController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHandController();

	void SetHand(EControllerHand Hand) { MotionController->SetTrackingSource(Hand); }
	void PairController(AHandController* Controller);

	virtual void GripPressed();
	virtual void GripReleased();

	virtual void TriggerPressed();
	virtual void TriggerReleased();

	virtual void ThumbStick(float Rate);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UWidgetInteractionComponent* Pointer;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// Callbacks

	UFUNCTION()
		void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
		void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	//UFUNCTION() Check why this isn't work
	//	void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//	void ComponentEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Parameters
	UPROPERTY(EditDefaultsOnly)
		class UHapticFeedbackEffect_Base* HapticEffect;



	// Helpers

	bool CanClimb() const;

	// Default sub object

	UPROPERTY(VisibleAnywhere)
		UMotionControllerComponent* MotionController;

	// State
	bool bCanClimb = false;

	bool bIsClimbing = false;
	FVector ClimbingStartLocation;
	AHandController* OtherController;
};

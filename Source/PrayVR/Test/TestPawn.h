// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "TestPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerJump, float, location);


UCLASS()
class PRAYVR_API ATestPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
	FOnPlayerJump PlayerJump;

private:
	void SwitchMode();
	void SpeedUp();
	void SlowDown();
	void Reset();
	void Random();

	UFUNCTION()
	void TestFunc(float location)
	{
		UE_LOG(LogTemp, Warning, TEXT("location"));

	}
};

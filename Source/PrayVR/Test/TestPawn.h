// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "TestPawn.generated.h"

UCLASS()
class PRAYVR_API ATestPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void SwitchMode();
	void SpeedUp();
	void SlowDown();
	void Reset();
	void Random();
};

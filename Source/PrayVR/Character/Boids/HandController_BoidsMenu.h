// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "PrayVR/Character/HandController.h"
#include "HandController_BoidsMenu.generated.h"

/**
 * 
 */
UCLASS()
class PRAYVR_API AHandController_BoidsMenu : public AHandController
{
	GENERATED_BODY()
public:
	AHandController_BoidsMenu();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Components
	UPROPERTY(VisibleAnywhere)
		UWidgetComponent* BoidsMenu;
};

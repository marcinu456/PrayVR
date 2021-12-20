// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "PrayVR/Boids/BoidManager.h"
#include "BoidsMenu.generated.h"

/**
 * 
 */
UCLASS()
class PRAYVR_API UBoidsMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	bool Initialize() override;

	void SetParentBoidsManager(ABoidManager* _ParentBoidsManager)
	{
		ParentBoidsManager = _ParentBoidsManager;
		SetUpWidget();
		UE_LOG(LogTemp, Warning, TEXT("SetParentBoidsManager"));
	}

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* FollowTargetButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UTextBlock* FollowTargetText;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		USlider* SeparationSlider;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		USlider* AlignmentSlider;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		USlider* CohesionSlider;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		USlider* TargetSlider;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* QuitButton;

private:
	UPROPERTY()
		ABoidManager* ParentBoidsManager;

	void SetUpWidget();

	UFUNCTION()
	void FollowTargetButtonClicked();

	UFUNCTION()
	void SeparationSliderValueChanged(float value);

	UFUNCTION()
		void AlignmentSliderValueChanged(float value);

	UFUNCTION()
		void CohesionSliderValueChanged(float value);

	UFUNCTION()
		void TargetSliderValueChanged(float value);

	UFUNCTION()
		void BackToPreviousLevel();
};

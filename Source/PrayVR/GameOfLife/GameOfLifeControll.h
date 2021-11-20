// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GridActor.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "GameOfLifeControll.generated.h"

/**
 * 
 */
UCLASS()
class PRAYVR_API UGameOfLifeControll : public UUserWidget
{
	GENERATED_BODY()
public:
	bool Initialize() override;

	void SetParentPicker(AGridActor* _ParentPicker) { ParentPicker = _ParentPicker; }

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* SpeedUpButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* SlowDownButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* StartButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* ResetButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UEditableTextBox* NumberOfPendulum;

private:
	UFUNCTION()
		void SpeedUpButtonClicked()
	{
		if (ParentPicker)
		{
			//ParentPicker->AddPendulum();
			//NumberOfPendulum->SetText(FText::FromString(FString::FromInt(ParentPicker->GetNumberOfPendulum())));
		}
	}

	UFUNCTION()
		void SlowDownButtonClicked()
	{
		if (ParentPicker)
		{
			//ParentPicker->DeletePendulum();
			//NumberOfPendulum->SetText(FText::FromString(FString::FromInt(ParentPicker->GetNumberOfPendulum())));
		}
	}

	UFUNCTION()
		void StartButtonClicked()
	{
		if (ParentPicker)
		{
			ParentPicker->ToPlayMode();
			StartButton->SetIsEnabled(false);
			SpeedUpButton->SetIsEnabled(true);
			SlowDownButton->SetIsEnabled(true);
			ResetButton->SetIsEnabled(true);
		}
	}

	UFUNCTION()
		void ResetButtonClicked()
	{
		if (ParentPicker)
		{
			ParentPicker->ToEditMode();
			ParentPicker->Reset();
			StartButton->SetIsEnabled(true);
			SpeedUpButton->SetIsEnabled(false);
			SlowDownButton->SetIsEnabled(false);
			ResetButton->SetIsEnabled(false);
		}
	}

	UPROPERTY()
		AGridActor* ParentPicker;
};

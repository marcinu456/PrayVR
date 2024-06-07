// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "PendulumSpawn.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "PendulumControl.generated.h"

/**
 * 
 */
UCLASS()
class PRAYVR_API UPendulumControl : public UUserWidget
{
	GENERATED_BODY()
public:
	bool Initialize() override;

	UFUNCTION(BlueprintCallable)
	void SetParentPicker(APendulumSpawn* _ParentPicker) { ParentPicker = _ParentPicker; }

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* AddButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* DeleteButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* StartButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* ResetButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UEditableTextBox* NumberOfPendulum;

private:
	UFUNCTION()
		void AddButtonClicked()
	{
		if (ParentPicker)
		{
			ParentPicker->AddPendulum();
			NumberOfPendulum->SetText(FText::FromString(FString::FromInt(ParentPicker->GetNumberOfPendulum())));
		}
	}

	UFUNCTION()
		void DeleteButtonClicked()
	{
		if (ParentPicker)
		{
			ParentPicker->DeletePendulum();
			NumberOfPendulum->SetText(FText::FromString(FString::FromInt(ParentPicker->GetNumberOfPendulum())));
		}
	}

	UFUNCTION()
		void StartButtonClicked()
	{
		if (ParentPicker)
		{
			ParentPicker->StartPendulum();
			StartButton->SetIsEnabled(false);
			AddButton->SetIsEnabled(false);
			DeleteButton->SetIsEnabled(false);
			ResetButton->SetIsEnabled(true);
		}
	}

	UFUNCTION()
		void ResetButtonClicked()
	{
		if (ParentPicker)
		{
			ParentPicker->ResetPendulum();
			StartButton->SetIsEnabled(true);
			AddButton->SetIsEnabled(true);
			DeleteButton->SetIsEnabled(true);
			ResetButton->SetIsEnabled(false);
		}
	}

	UPROPERTY()
		APendulumSpawn* ParentPicker;
};

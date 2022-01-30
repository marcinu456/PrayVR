// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "AgentSpawner.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "AgentControl.generated.h"

class AAgentSpawner;
/**
 * 
 */
UCLASS()
class PRAYVR_API UAgentControl : public UUserWidget
{
	GENERATED_BODY()

public:
	bool Initialize() override;

	void SetParentPicker(AAgentSpawner* _ParentPicker) { ParentPicker = _ParentPicker; }
private:

	UPROPERTY()
		AAgentSpawner* ParentPicker;

protected:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* StartButton;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (BindWidget))
		UButton* ResetButton;

private:
	UFUNCTION()
		void StartButtonClicked()
	{
		if (ParentPicker)
		{
			ParentPicker->StartAgents();
			StartButton->SetIsEnabled(false);
			ResetButton->SetIsEnabled(true);
		}
	}

	UFUNCTION()
		void ResetButtonClicked()
	{
		if (ParentPicker)
		{
			ParentPicker->ResetAgents();
			StartButton->SetIsEnabled(true);
			ResetButton->SetIsEnabled(false);
		}
	}

};

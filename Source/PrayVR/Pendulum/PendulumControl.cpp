// Created by Cookie Core


#include "PendulumControl.h"

bool UPendulumControl::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!AddButton) return false;
	AddButton->OnClicked.AddDynamic(this, &UPendulumControl::AddButtonClicked);

	if (!DeleteButton) return false;
	DeleteButton->OnClicked.AddDynamic(this, &UPendulumControl::DeleteButtonClicked);

	if (!StartButton) return false;
	StartButton->OnClicked.AddDynamic(this, &UPendulumControl::StartButtonClicked);

	if (!ResetButton) return false;
	ResetButton->OnClicked.AddDynamic(this, &UPendulumControl::ResetButtonClicked);
	ResetButton->SetIsEnabled(false);

	return true;
}
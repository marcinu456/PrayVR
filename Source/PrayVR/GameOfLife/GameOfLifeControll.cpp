// Created by Cookie Core


#include "GameOfLifeControll.h"

bool UGameOfLifeControll::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!SpeedUpButton) return false;
	SpeedUpButton->OnClicked.AddDynamic(this, &UGameOfLifeControll::SpeedUpButtonClicked);

	if (!SlowDownButton) return false;
	SlowDownButton->OnClicked.AddDynamic(this, &UGameOfLifeControll::SlowDownButtonClicked);
	SpeedUpButton->SetIsEnabled(false);

	if (!StartButton) return false;
	StartButton->OnClicked.AddDynamic(this, &UGameOfLifeControll::StartButtonClicked);
	SlowDownButton->SetIsEnabled(false);

	if (!ResetButton) return false;
	ResetButton->OnClicked.AddDynamic(this, &UGameOfLifeControll::ResetButtonClicked);
	ResetButton->SetIsEnabled(false);

	return true;
}
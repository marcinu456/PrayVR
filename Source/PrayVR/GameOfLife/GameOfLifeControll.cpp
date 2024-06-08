// Created by Cookie Core


#include "GameOfLifeControll.h"

bool UGameOfLifeControll::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!SpeedUpButton) return false;
	SpeedUpButton->OnClicked.AddDynamic(this, &UGameOfLifeControll::SpeedUpButtonClicked);
	//SpeedUpButton->SetIsEnabled(false);

	if (!SlowDownButton) return false;
	SlowDownButton->OnClicked.AddDynamic(this, &UGameOfLifeControll::SlowDownButtonClicked);
	//SlowDownButton->SetIsEnabled(false);

	if (!StartButton) return false;
	StartButton->OnClicked.AddDynamic(this, &UGameOfLifeControll::StartButtonClicked);

	if (!ResetButton) return false;
	ResetButton->OnClicked.AddDynamic(this, &UGameOfLifeControll::ResetButtonClicked);
	ResetButton->SetIsEnabled(false);

	if (!RandomButton) return false;
	RandomButton->OnClicked.AddDynamic(this, &UGameOfLifeControll::RandomButtonClicked);

	return true;
}
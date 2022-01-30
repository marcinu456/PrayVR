// Created by Cookie Core


#include "AgentControl.h"

bool UAgentControl::Initialize()
{
	if (!Super::Initialize()) return false;



	if (!StartButton) return false;
	StartButton->OnClicked.AddDynamic(this, &UAgentControl::StartButtonClicked);

	if (!ResetButton) return false;
	ResetButton->OnClicked.AddDynamic(this, &UAgentControl::ResetButtonClicked);
	ResetButton->SetIsEnabled(false);

	return true;
}

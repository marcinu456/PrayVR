// Created by Cookie Core


#include "BoidsMenu.h"

bool UBoidsMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	
	if (!FollowTargetButton) return false;
	FollowTargetButton->OnClicked.AddDynamic(this, &UBoidsMenu::FollowTargetButtonClicked);

	if (!SeparationSlider) return false;
	SeparationSlider->OnValueChanged.AddDynamic(this, &UBoidsMenu::SeparationSliderValueChanged);

	if (!AlignmentSlider) return false;
	AlignmentSlider->OnValueChanged.AddDynamic(this, &UBoidsMenu::AlignmentSliderValueChanged);

	if (!CohesionSlider) return false;
	CohesionSlider->OnValueChanged.AddDynamic(this, &UBoidsMenu::CohesionSliderValueChanged);

	if (!TargetSlider) return false;
	TargetSlider->OnValueChanged.AddDynamic(this, &UBoidsMenu::TargetSliderValueChanged);

	return true;

}

void UBoidsMenu::SetUpWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("SetUpWidget "));

	if(!ParentBoidsManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not found  ParentBoidsManager "));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Founded  ParentBoidsManager "));

	}

	if(ParentBoidsManager->IsBoidsFollowTarget())
	{
		FollowTargetText->SetText(FText::FromString("✔"));
	}
	else
	{
		FollowTargetText->SetText(FText::FromString(""));
	}


	AlignmentSlider->SetValue(ParentBoidsManager->GetAlignmentWeight());
	SeparationSlider->SetValue(ParentBoidsManager->GetSeparationWeight());
	CohesionSlider->SetValue(ParentBoidsManager->GetCohesionWeight());
	TargetSlider->SetValue(ParentBoidsManager->GetTargetWeight());

}

void UBoidsMenu::FollowTargetButtonClicked()
{
	if (ParentBoidsManager->IsBoidsFollowTarget())
	{
		FollowTargetText->SetText(FText::FromString(""));
		ParentBoidsManager->SetBoidsFollowTarget(false);
	}
	else
	{
		FollowTargetText->SetText(FText::FromString("✔"));
		ParentBoidsManager->SetBoidsFollowTarget(true);
	}
	UE_LOG(LogTemp, Warning, TEXT("FollowTargetButtonClicked %d "), ParentBoidsManager->IsBoidsFollowTarget());

}

void UBoidsMenu::SeparationSliderValueChanged(float value)
{
	ParentBoidsManager->SetSeparationWeight(value);
}

void UBoidsMenu::AlignmentSliderValueChanged(float value)
{
	ParentBoidsManager->SetAlignmentWeight(value);
}

void UBoidsMenu::CohesionSliderValueChanged(float value)
{
	ParentBoidsManager->SetCohesionWeight(value);
}

void UBoidsMenu::TargetSliderValueChanged(float value)
{
	ParentBoidsManager->SetTargetWeight(value);
}

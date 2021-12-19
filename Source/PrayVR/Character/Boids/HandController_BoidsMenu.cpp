// Created by Cookie Core


#include "HandController_BoidsMenu.h"

#include "BoidsMenu.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

AHandController_BoidsMenu::AHandController_BoidsMenu()
{
	BoidsMenu = CreateDefaultSubobject<UWidgetComponent>(TEXT("BoidsMenu"));
	BoidsMenu->SetupAttachment(GetRootComponent());
}

void AHandController_BoidsMenu::BeginPlay()
{
	Super::BeginPlay();

	auto TempBoidMenu = Cast<UBoidsMenu>(BoidsMenu->GetUserWidgetObject());
	if (TempBoidMenu)
	{
		auto Manager = Cast<ABoidManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoidManager::StaticClass()));
		if (Manager) {
			TempBoidMenu->SetParentBoidsManager(Manager);
			UE_LOG(LogTemp, Warning, TEXT("Finded BoidManager in scene AHandController_BoidsMenu as"));
		}
		else {
			UE_LOG(LogTemp, Error, TEXT("Failed to find BoidManager in scene AHandController_BoidsMenu"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Cast<UBoidsMenu>"));

	}
}

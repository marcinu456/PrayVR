// Created by Cookie Core


#include "TestGameState.h"

#include "Kismet/GameplayStatics.h"
#include "PrayVR/GameOfLife/GridActor3D.h"



void ATestGameState::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> Rabbits;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGridActor3D::StaticClass(), Rabbits);


	for (auto& Rabbit : Rabbits)
	{
		GridActors.Add(Cast<AGridActor3D>(Rabbit));
	}


	/*for (FTransform T : Transforms) {
		GridActors.Add(GetWorld()->SpawnActor<AGridActor3D>(GridActor, T));
	}*/

	EditMode = true;
}

void ATestGameState::SetEditMode(const bool Editing) {
	if (Editing) {
		for (AGridActor3D* Grid : GridActors) {
			Grid->ToEditMode();
		}
	}
	else {
		for (AGridActor3D* Grid : GridActors) {
			Grid->ToPlayMode();
		}
	}
	EditMode = Editing;
}

void ATestGameState::StartTimers() {
	for (AGridActor3D* Grid : GridActors) {
		Grid->StartTimer();
	}
}

void ATestGameState::ClearTimers() {
	for (AGridActor3D* Grid : GridActors) {
		Grid->ClearTimer();
	}
}

void ATestGameState::Reset() {
	for (AGridActor3D* Grid : GridActors) {
		Grid->Reset();
	}
	SetEditMode(true);
}

void ATestGameState::Random()
{
	for (AGridActor3D* Grid : GridActors) {
		Grid->RandomGrid();
	}
	SetEditMode(true);
}

void ATestGameState::SpeedUp() {
	if (AdvanceTime >= 0.2f) {
		AdvanceTime -= 0.1f;
	}
}

void ATestGameState::SlowDown() {
	if (AdvanceTime <= 9.9f) {
		AdvanceTime += 0.1f;
	}
}
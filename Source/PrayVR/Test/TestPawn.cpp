// Created by Cookie Core


#include "TestPawn.h"

#include "TestGameState.h"
#include "Kismet/GameplayStatics.h"

void ATestPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Switch Mode", IE_Pressed, this, &ATestPawn::SwitchMode);
	PlayerInputComponent->BindAction("Speed Up", IE_Pressed, this, &ATestPawn::SpeedUp);
	PlayerInputComponent->BindAction("Slow Down", IE_Pressed, this, &ATestPawn::SlowDown);
	PlayerInputComponent->BindAction("Reset", IE_Pressed, this, &ATestPawn::Reset);
	PlayerInputComponent->BindAction("Randomgrid", IE_Pressed, this, &ATestPawn::Random);

	
	PlayerJump.AddDynamic(this, &ATestPawn::TestFunc);
}

void ATestPawn::SwitchMode()
{
	UE_LOG(LogTemp, Warning, TEXT("switching mode"));
	ATestGameState* const MyGameState = Cast<ATestGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (MyGameState)
	{
		if (MyGameState->GetEditMode()) {
			MyGameState->SetEditMode(false);
			MyGameState->StartTimers();
		}
		else {
			MyGameState->SetEditMode(true);
			MyGameState->ClearTimers();
		}
	}
}

void ATestPawn::SpeedUp()
{
	ATestGameState* const MyGameState = Cast<ATestGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (MyGameState)
	{
		MyGameState->SpeedUp();
		if (!MyGameState->GetEditMode()) {
			MyGameState->ClearTimers();
			MyGameState->StartTimers();
		}
		//UE_LOG(LogTemp, Warning, TEXT("speed up, time: %f"), MyGameState->GetAdvanceTime());
	}
}

void ATestPawn::SlowDown()
{
	ATestGameState* const MyGameState = Cast<ATestGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (MyGameState)
	{
		MyGameState->SlowDown();
		if (!MyGameState->GetEditMode()) {
			MyGameState->ClearTimers();
			MyGameState->StartTimers();
		}
		//UE_LOG(LogTemp, Warning, TEXT("slow down, time: %f"), MyGameState->GetAdvanceTime());
	}
}

void ATestPawn::Reset()
{

	UE_LOG(LogTemp, Warning, TEXT("resetting"));
	ATestGameState* const MyGameState = Cast<ATestGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (MyGameState)
	{
		MyGameState->Reset();
	}
}

void ATestPawn::Random()
{
	UE_LOG(LogTemp, Warning, TEXT("random"));
	ATestGameState* const MyGameState = Cast<ATestGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (MyGameState)
	{
		MyGameState->Random();
	}

	//TestFunc(1);
	PlayerJump.Broadcast(2137.f);
	
}

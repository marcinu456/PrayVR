// Created by Cookie Core


#include "HandController_Agents.h"

#include "PrayVR/AgentModel/AgentBase.h"
#include "PrayVR/AgentModel/AgentSpawnBox.h"

void AHandController_Agents::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bool bNewCanPickupAgent = CanPickUp();
	if (!bCanPickupAgent && bNewCanPickupAgent)
	{
		APawn* Pawn = Cast<APawn>(GetAttachParentActor());
		if (Pawn)
		{
			APlayerController* Controller = Cast<APlayerController>(Pawn->GetController());
			if (Controller)
			{
				Controller->PlayHapticEffect(HapticEffect, MotionController->GetTrackingSource());
			}
		}
	}

	AgentSpawnBox = Cast<AAgentSpawnBox>(OtherActor);

	bCanPickupAgent = bNewCanPickupAgent;
}

void AHandController_Agents::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bCanPickupAgent = CanPickUp();

	if (AgentSpawnBox)
	{
		AgentSpawnBox = nullptr;
	}
}

bool AHandController_Agents::CanPickUp()
{

	TArray<AActor*> OverlappingActors;
	//MotionController->GetOverlappingActors(OverlappingActors);
	GetOverlappingActors(OverlappingActors);

	for (auto& OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor->ActorHasTag(TEXT("Climbable")))
		{
			return true;
		}
	}

	return false;
}

void AHandController_Agents::GripPressed()
{
	Super::GripPressed();

	if(AgentSpawnBox)
	{
		UE_LOG(LogTemp, Warning, TEXT(" AHandController_Agents::GripPressed()"));

		AgentSpawnBox->SpawnAgent();
	}

	if (!bCanPickupAgent) return;

}

void AHandController_Agents::GripReleased()
{
	Super::GripReleased();


	if(Agent)
	{
		Agent->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	}

	

}

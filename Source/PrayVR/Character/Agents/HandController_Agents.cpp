// Created by Cookie Core


#include "HandController_Agents.h"

#include "PrayVR/AgentModel/AgentBase.h"
#include "PrayVR/AgentModel/AgentSpawnBox.h"
#include "PrayVR/AgentModel/AgentTable.h"

AHandController_Agents::AHandController_Agents()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);

}

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


	if (!Agent)
	{
		Agent = Cast<AAgentBase>(OtherActor);
		if(Agent)
		{
			Agent->SetBeginMaterial();
		}
	}
	if (!AgentSpawnBox)
	{
		AgentSpawnBox = Cast<AAgentSpawnBox>(OtherActor);
	}
	if (!AgentTable)
	{
		AgentTable = Cast<AAgentTable>(OtherActor);

		if(Agent&& AgentTable && bGripPressed)
		{
			Agent->SetClickedMaterial();

		}

	}
	bCanPickupAgent = bNewCanPickupAgent;
}

void AHandController_Agents::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	bCanPickupAgent = CanPickUp();

	if (Agent&&!bGripPressed)
	{
		Agent->SetBasicMaterial();
		Agent = nullptr;
	}
	if (AgentSpawnBox)
	{
		AgentSpawnBox = nullptr;
	}
	if (AgentTable)
	{
		AgentTable = nullptr;
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


	if (Agent)
	{
		UE_LOG(LogTemp, Warning, TEXT(" I see agent"));
		Agent->AttachToComponent(StaticMeshComponent, FAttachmentTransformRules::KeepWorldTransform, NAME_None);
	}



	if(AgentSpawnBox)
	{
		UE_LOG(LogTemp, Warning, TEXT(" AHandController_Agents::GripPressed()"));

		AgentSpawnBox->SpawnAgent();
	}

	if (!bCanPickupAgent) return;

	bGripPressed = true;
}

void AHandController_Agents::GripReleased()
{
	Super::GripReleased();

	if(AgentTable && Agent)
	{
		Agent->SetBasicMaterial();
		AgentTable->SetUpAgent(Agent);
		Agent = nullptr;
	}

	if(Agent)
	{
		Agent->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Agent->OnDestroy();
	}

	
	bGripPressed = false;
}

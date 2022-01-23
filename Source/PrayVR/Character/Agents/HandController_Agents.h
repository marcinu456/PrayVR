// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "PrayVR/Character/HandController.h"
#include "HandController_Agents.generated.h"

/**
 * 
 */
UCLASS()
class PRAYVR_API AHandController_Agents : public AHandController
{
	GENERATED_BODY()



		virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

		virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

	bool bCanPickupAgent;

	class AAgentSpawnBox* AgentSpawnBox;
	class AAgentTable* AgentTable;

public:

	void GripPressed() override;
	void GripReleased() override;

	class AAgentBase* Agent;

	bool CanPickUp();


};

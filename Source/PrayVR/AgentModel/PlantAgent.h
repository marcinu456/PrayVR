// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "AgentBase.h"
#include "PlantAgent.generated.h"

/**
 * 
 */
UCLASS()
class PRAYVR_API APlantAgent : public AAgentBase
{
	GENERATED_BODY()
public:
	APlantAgent();

	virtual void Tick(float DeltaTime) override;
};

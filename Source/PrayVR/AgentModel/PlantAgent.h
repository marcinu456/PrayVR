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

private:
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

};

// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "AgentBase.h"
#include "RabbitAgent.generated.h"

/**
 * 
 */
UCLASS()
class PRAYVR_API ARabbitAgent : public AAgentBase
{
	GENERATED_BODY()
public:
	ARabbitAgent();
protected:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void Move() override;

	const size_t RABBIT_COUNT = 8;
	const size_t RABBIT_MAX_HP = 300;
	const size_t RABBIT_MAX_HUNGRY_HP_LEVEL = 150;
	const double RABBIT_VELOCITY = 2.5;
	const double RABBIT_REPRODUCE_COUNT = 2;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Actor to spawn"))
		TSubclassOf<ARabbitAgent> RabbitActor;

	class APlantAgent* atractorPlant;
	ARabbitAgent* atractorRabbit;
	
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};

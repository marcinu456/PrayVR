// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "PrayVR/Test/TestPawn.h"
#include "AgentSpawner.generated.h"

class AWolfAgent;
class ARabbitAgent;
class APlantAgent;
UCLASS()
class PRAYVR_API AAgentSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAgentSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:

	/** Class for cell. */
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		TSubclassOf<APlantAgent> PlantActor;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		TSubclassOf<ARabbitAgent> RabbitActor;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Grid Setup"))
		TSubclassOf<AWolfAgent> WolfActor;

	const size_t PLANT_COUNT = 8;
	const size_t PLANT_MAX_HP = 240;
	const size_t PLANT_REPRODUCE_TIME = 30;
	const size_t PLANT_REPRODUCE_COUNT = 8;

	const size_t RABBIT_COUNT = 2;
	const size_t RABBIT_MAX_HP = 300;
	const size_t RABBIT_MAX_HUNGRY_HP_LEVEL = 150;
	const double RABBIT_VELOCITY = 2.5;

	const size_t WOLF_COUNT = 4;
	const size_t WOLF_MAX_HP = 500;
	const size_t WOLF_MAX_HUNGRY_HP_LEVEL = 150;
	const double WOLF_VELOCITY = 2;

	size_t iter = 0;


	UFUNCTION()
	void RespondToOnPlayerJump(float location);

	TArray<class AAgentBase*> AgentBases;

public:

	void AddAgent(AAgentBase* _Agent);

	void DeleteAgent(AAgentBase* _Agent);
};

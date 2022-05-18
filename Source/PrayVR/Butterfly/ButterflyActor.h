// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ButterflyActor.generated.h"

UCLASS()
class PRAYVR_API AButterflyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AButterflyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Setup"))
		int32 ButterflyChange = 1;
};

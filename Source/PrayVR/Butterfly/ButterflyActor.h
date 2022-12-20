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

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		TArray<UStaticMeshComponent*> StaticMeshComponents;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Setup"))
		float ButterflyChange = 0.002;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Setup"))
		float sigma = 10;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Setup"))
		float rho = 28;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Setup"))
		float beta = 8 / 3;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true", Category = "Setup"))
		bool bIsCPPTick = false;

	UFUNCTION(BlueprintCallable)
		FVector UpdatePosition(FVector Position);
};

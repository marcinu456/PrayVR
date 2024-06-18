// Created by Cookie Core

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pendulum.generated.h"

UCLASS()
class PRAYVR_API APendulum : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APendulum();

	void SetParameters(double _theta0, double _length0, double _mass0, double _theta1, double _length1, double _mass1);
	void ResetParameters();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void computeAnglesEuler(float dt);
	void computeAnglesRunge(float dt);
	void computePosition();

	void air();

	//StartParameter
	float start_px = 0;
	float start_py = 0;

	float start_x0 = 0;
	float start_y0 = 0;
	float start_theta0prim = 0;
	float start_theta0bis = 0;
	float start_theta0 = 0;
	float start_length0 = 0;
	float start_mass0 = 0;

	float start_x1 = 0;
	float start_y1 = 0;
	float start_theta1prim = 0.0;
	float start_theta1bis = 0;
	float start_theta1 = 0;
	float start_length1 = 0;
	float start_mass1 = 0;



	//Current Parameter
	float px = 0;
	float py = 0;

	float x0 = 0;
	float y0 = 0;
	float theta0prim = 0;
	float theta0bis = 0;
	float theta0 = 0;
	float length0 = 0;
	float mass0 = 0;

	float x1 = 0;
	float y1 = 0;
	float theta1prim = 0.0;
	float theta1bis = 0;
	float theta1 = 0;
	float length1 = 0;
	float mass1 = 0;


	float g = -9.81;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		TArray<class USplineMeshComponent*> PendulumSplinePathMeshPool;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USplineComponent* PendulumSpline;

	UPROPERTY(EditDefaultsOnly)
		class UStaticMesh* FirstColumnArchMesh;

	UPROPERTY(EditDefaultsOnly)
		class UMaterialInterface* FirstColumnArchMaterial;

};

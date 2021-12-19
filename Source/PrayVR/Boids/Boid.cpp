// Created by Cookie Core


#include "Boid.h"
#include "BoidManager.h"
#include "BoidTarget.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
//#include "PrayVR/Character/HandController_Boids.h"

ABoid::ABoid() {
	PrimaryActorTick.bCanEverTick = false;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>(FName("SceneComponent"));
	BoxCollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxCollisionComponent->SetBoxExtent(FVector(16.f));
	SetRootComponent(BoxCollisionComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mesh"));
	Mesh->SetCollisionProfileName(FName("Boid"));
	Mesh->SetCollisionProfileName(FName("Boid"));
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh->SetupAttachment(BoxCollisionComponent);

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(FName("ArrowComponent"));
	ArrowComponent->SetupAttachment(BoxCollisionComponent);
}

void ABoid::BeginPlay() {
	Super::BeginPlay();

	Manager = Cast<ABoidManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoidManager::StaticClass()));
	if (Manager) {
		Manager->AddManagedBoid(this);
		UE_LOG(LogTemp, Warning, TEXT("Finded BoidManager in scene"));

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Failed to find BoidManager in scene"));
	}
	
	BoidTarget = Cast<ABoidTarget>(UGameplayStatics::GetActorOfClass(GetWorld(), ABoidTarget::StaticClass()));
	if (!BoidTarget) {
		UE_LOG(LogTemp, Error, TEXT("Failed to find BoidTarget in scene"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Finded BoidTarget in scene"));
	}
}

void ABoid::BeginDestroy() {
	if (Manager) {
		Manager->RemoveManagedBoid(this);
	}
	Super::BeginDestroy();
}

void ABoid::CalculateBoidRotation() {

	TArray<ABoid*> CloseBoids = CalculateClosestBoids(AmountOfBoidsToObserve);

	FVector InterpolatedForwardVector = FVector::ZeroVector;

	FVector AlignmentVector = FVector::ZeroVector;
	FVector CohesionVector = FVector::ZeroVector;
	FVector SeparationVector = FVector::ZeroVector;
	FVector TargetVector = FVector::ZeroVector;

	if (CloseBoids.Num() != 0) {
		for (int index = 0; index < CloseBoids.Num(); index++) {
			ABoid* Boid = CloseBoids[index];
			CalculateAlignment(AlignmentVector, Boid);
			CalculateCohesion(CohesionVector, Boid);
			CalculateSeparation(SeparationVector, Boid);
		}
		AlignmentVector /= CloseBoids.Num();
		CohesionVector /= CloseBoids.Num();
		SeparationVector /= CloseBoids.Num();

		AlignmentVector.Normalize();
		CohesionVector.Normalize();
		SeparationVector.Normalize();
	}

	if (Manager->IsBoidsFollowTarget()) {
		TargetVector = CalculateTarget();

		//UE_LOG(LogTemp, Error, TEXT("Follow To Targer"));

	}
	//UE_LOG(LogTemp, Error, TEXT("Obbliczanie"));

	InterpolatedForwardVector += AlignmentVector * Manager->GetAlignmentWeight();
	InterpolatedForwardVector += CohesionVector * Manager->GetCohesionWeight();
	InterpolatedForwardVector += SeparationVector * Manager->GetSeparationWeight();
	InterpolatedForwardVector += TargetVector * Manager->GetTargetWeight();

	InterpolatedForwardVector *= TurnSpeed;

	InterpolatedForwardVector.Normalize();

	NextBoidRotation = UKismetMathLibrary::MakeRotFromX(InterpolatedForwardVector);
}

void ABoid::UpdateBoidRotation(float DeltaTime) {
	SetActorRotation(FMath::RInterpTo(GetActorRotation(), NextBoidRotation, DeltaTime, 1.f));
}

void ABoid::CalculateBoidPosition(float DeltaTime) {
	FVector SimpleForwardMovement = GetActorForwardVector();
	NextBoidWorldOffset = ForwardSpeed * DeltaTime * (SimpleForwardMovement);
}

void ABoid::UpdateBoidPosition() {
	AddActorWorldOffset(NextBoidWorldOffset);
}

void ABoid::CalculateSeparation(FVector& Separation, ABoid* Boid) {
	FVector Sub = GetActorLocation() - Boid->GetActorLocation();
	Separation += Sub * Sub.GetSafeNormal().Size();
}

void ABoid::CalculateAlignment(FVector& Alignment, ABoid* Boid) {
	Alignment += Boid->GetActorForwardVector();
}

void ABoid::CalculateCohesion(FVector& Cohesion, ABoid* Boid) {
	Cohesion += Boid->GetActorLocation();
}

FVector ABoid::CalculateTarget() {
	FVector Target = FVector::ZeroVector;
	if (BoidTarget) {
		Target = BoidTarget->GetActorLocation() - GetActorLocation();
		Target.Normalize();
	}
	return Target;
}

TArray<ABoid*> ABoid::CalculateClosestBoids(int32 Amount) {
	TArray<ABoid*> rc;

	if (Manager) {
		TArray<FOtherBoidInfo> OtherBoidInfos;
		for (ABoid* Other : Manager->GetManagedBoids()) {
			if (!Other || this == Other) {
				continue;
			}
			float OtherDistance = (Other->GetActorLocation() - GetActorLocation()).Size();
			if (OtherDistance < CloseBoidDistanceCutOff) {
				FOtherBoidInfo OtherInfo(Other, OtherDistance);
				OtherBoidInfos.Add(OtherInfo);
			}
		}
		// Sort by distance
		OtherBoidInfos.Sort([this](const FOtherBoidInfo& O1, const FOtherBoidInfo& O2) {
			return O1.Distance < O2.Distance;
			});

		for (int32 i = 0; i < Amount && i < OtherBoidInfos.Num(); i++) {
			rc.Add(OtherBoidInfos[i].Other);
		}
	}

	return rc;
}

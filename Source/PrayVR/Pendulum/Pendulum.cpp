// Created by Cookie Core


#include "Pendulum.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

// Sets default values
APendulum::APendulum()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstColumn = CreateDefaultSubobject<USplineComponent>(TEXT("FirstColumn"));
	FirstColumn->SetupAttachment(GetRootComponent());


}

// Called when the game starts or when spawned
void APendulum::BeginPlay()
{
	Super::BeginPlay();
	double M_PI = 3.1415926535897932384626433832795;
	auto Frector = GetActorLocation();
	px = Frector.Y;
	py = Frector.Z;
	theta0 = M_PI / 2.0 + 0.15;
	length0 = 150;
	mass0 = 1;
	theta1 = M_PI / 2.0 + 0.15 + 0.0001;
	length1 = 150;
	mass1 = 1;
}

// Called every frame
void APendulum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	computeAnglesEuler(DeltaTime);
	computePosition();
}

void APendulum::computeAnglesEuler(float dt)
{
	//source http://www.team.kdm.p.lodz.pl/master/Jankowski.pdf
	double u = 1 + mass0 + mass1;
	theta0bis =
		(g * (sin(theta1) * cos(theta0 - theta1) - u * sin(theta0))
			- (length1 * pow(theta1prim, 2) + length0 * pow(theta0prim, 2) * cos(theta0 - theta1)) * sin(theta0 - theta1))
		/ (length0 * (u - pow(cos(theta0 - theta1), 2)));
	theta1bis =
		(g * u * (sin(theta0) * cos(theta0 - theta1) - sin(theta1)) + (u * length0 * pow(theta0prim, 2)
			+ length1 * pow(theta1prim, 2) * cos(theta0 - theta1)) * sin(theta0 - theta1))
		/ (length1 * (u - pow(cos(theta0 - theta1), 2)));


	theta0prim = theta0prim + theta0bis * dt;
	theta1prim = theta1prim + theta1bis * dt;

	theta0 = theta0 + theta0prim * dt;
	theta1 = theta1 + theta1prim * dt;
}

void APendulum::computeAnglesRunge(float dt)
{
	//source https://www.myphysicslab.com/pendulum/double-pendulum-en.html
	theta0bis = -g * (2 * mass0 + mass1) * sin(theta0) - mass1 * g * sin(theta0 - (2 * theta1)) - 2 * (sin(theta0 - theta1)) * mass0 * ((theta1prim * theta1prim) * length1 + (theta0prim * theta0prim) * length0 * cos(theta0 - theta1));

	theta0bis /= length0 * (2 * mass0 + mass1 - mass1 * cos(2 * theta0 - 2 * theta0));

	theta1bis = 2 * sin(theta0 - theta1) * ((theta0prim * theta0prim) * length0 * (mass0 + mass1) + g * (mass0 + mass1) * cos(theta0) + (theta1prim * theta1prim) * length1 * mass1 * cos(theta0 - theta1));

	theta1bis /= length1 * (2 * mass0 + mass1 - mass1 * cos(2 * theta0 - 2 * theta1));

	theta0prim = theta0prim + theta0bis * dt;
	theta1prim = theta1prim + theta1bis * dt;

	theta0 = theta0 + theta0prim * dt;
	theta1 = theta1 + theta1prim * dt;
}

void APendulum::computePosition()
{
	x0 = px + length0 * FMath::Sin(theta0);
	y0 = py + length0 * FMath::Cos(theta0);

	x1 = x0 + length1 * FMath::Sin(theta1);
	y1 = y0 + length1 * FMath::Cos(theta1);
	auto Frector = GetActorLocation();
	FVector StarPos1 = { Frector.X, px,py, };
	FVector EndPos1 = { Frector.X, x0, y0, };

	//FVector StarPos2 = { x0, y0,Frector.Z+150 };
	FVector EndPos2 = { Frector.X,x1, y1, };

	TArray<FVector> Path;
	Path.Add(StarPos1);
	Path.Add(EndPos1);
	Path.Add(EndPos2);

	FirstColumn->ClearSplinePoints(false);
	int32 index = 0;
	for (auto& Point : Path)
	{
		FVector LocalPosition = FirstColumn->GetComponentTransform().InverseTransformPosition(Point);
		FirstColumn->AddPoint(FSplinePoint(index, LocalPosition, ESplinePointType::Constant), false);
		index++;
	}

	FirstColumn->UpdateSpline();

	int32 SegmentNum = Path.Num() - 1;
	for (int32 i = 0; i < SegmentNum; ++i)
	{
		if (ColumnsPathMeshPool.Num() <= i)
		{
			USplineMeshComponent* SplineMesh = NewObject<USplineMeshComponent>(this);
			SplineMesh->SetMobility(EComponentMobility::Movable);
			SplineMesh->AttachToComponent(FirstColumn, FAttachmentTransformRules::KeepRelativeTransform);
			SplineMesh->SetStaticMesh(FirstColumnArchMesh);
			SplineMesh->SetMaterial(0, FirstColumnArchMaterial);
			SplineMesh->RegisterComponent();

			ColumnsPathMeshPool.Add(SplineMesh);
		}

		USplineMeshComponent* SplineMesh = ColumnsPathMeshPool[i];
		SplineMesh->SetVisibility(true);

		FVector StarPos, StartTangent, EndPos, EndTangent;
		FVector Tangent = { 0,0,0 };
		FirstColumn->GetLocalLocationAndTangentAtSplinePoint(i, StarPos, StartTangent);
		FirstColumn->GetLocalLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent);
		SplineMesh->SetStartAndEnd(StarPos, Tangent, EndPos, Tangent);

	}



	USplineMeshComponent* SplineMesh = ColumnsPathMeshPool[1];
	auto ss1 = SplineMesh->GetStartPosition();
	auto ss2 = SplineMesh->GetEndPosition();
	//UE_LOG(LogTemp, Warning, TEXT("Text, %f, %f, end %f, %f"), ss1.X, ss1.Y, ss2.X, ss2.Y);


}


void APendulum::air()
{
	theta0prim *= 0.993;
	theta1prim *= 0.993;
}



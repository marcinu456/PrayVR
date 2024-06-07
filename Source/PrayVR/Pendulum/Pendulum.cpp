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
	FirstColumn->CastShadow = false;

}

void APendulum::SetParameters(double _theta0, double _length0, double _mass0, double _theta1,
	double _length1, double _mass1)
{

	auto Frector = GetActorLocation();
	start_px = Frector.Y;
	start_py = Frector.Z;
	start_theta0 = _theta0;
	start_length0 = _length0;
	start_mass0 = _mass0;
	start_theta1 = _theta1;
	start_length1 = _length1;
	start_mass1 = _mass1;

	px = start_px;
	py = start_py;
	theta0 = start_theta0;
	length0 = start_length0;
	mass0 = start_mass0;
	theta1 = start_theta1;
	length1 = start_length1;
	mass1 = start_mass1;

	computePosition();
}

void APendulum::ResetParameters()
{
	px = start_px;
	py = start_py;
	theta0 = start_theta0;
	length0 = start_length0;
	mass0 = start_mass0;
	theta1 = start_theta1;
	length1 = start_length1;
	mass1 = start_mass1;

	x0 = 0;
	y0 = 0;
	theta0prim = 0;
	theta0bis = 0;

	x1 = 0;
	y1 = 0;
	theta1prim = 0.0;
	theta1bis = 0;


	computePosition();
}

// Called when the game starts or when spawned
void APendulum::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APendulum::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	computeAnglesEuler(DeltaTime*5);
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

	for (int32 i = 0; i < Path.Num() - 1; ++i)
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

			UE_LOG(LogTemp, Warning, TEXT("Some warning ColumnsPathMeshPool"));
		}

		USplineMeshComponent* SplineMesh = ColumnsPathMeshPool[i];
		SplineMesh->SetVisibility(true);

		FVector StarPos, StartTangent, EndPos, EndTangent;
		FVector Tangent = { 0,0,0 };
		FirstColumn->GetLocalLocationAndTangentAtSplinePoint(i, StarPos, StartTangent);
		FirstColumn->GetLocalLocationAndTangentAtSplinePoint(i + 1, EndPos, EndTangent);
		SplineMesh->SetStartAndEnd(StarPos, Tangent, EndPos, Tangent);

	}
	//TODO fix the bug with non visible spline mesh
}


void APendulum::air()
{
	theta0prim *= 0.993;
	theta1prim *= 0.993;
}



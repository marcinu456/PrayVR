// Created by Cookie Core


#include "GridActor.h"

#include "GameOfLifeControll.h"

//TODO Create base grid actor and child class to 2d and 3d
AGridActor::AGridActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	ControlBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("ControlBar"));
	ControlBar->SetupAttachment(GetRootComponent());

	AdvanceTime = .5f;
	maxTimer = 8.f;
	minTimer = 0.1f;

}

void AGridActor::BeginPlay()
{
	Super::BeginPlay();

	auto PaintingActionBar = Cast<UGameOfLifeControll>(ControlBar->GetUserWidgetObject());
	if (PaintingActionBar)
	{
		PaintingActionBar->SetParentPicker(this);
	}

	CreateGrid();
}

void AGridActor::CreateGrid()
{
	TArray<UStaticMeshComponent*> Components;
	CellActor.GetDefaultObject()->GetComponents<UStaticMeshComponent>(Components);
	const FVector BoxExtent = Components[0]->GetStaticMesh()->GetBounds().BoxExtent;
	const FVector Scale = Components[0]->GetRelativeTransform().GetScale3D();

	ensure(Components.Num() > 0);

	const float EffectiveBoxExtentY = BoxExtent.Y * Scale.Y + Offset;
	const float EffectiveBoxExtentZ = BoxExtent.Z * Scale.Z + Offset;
	const float YStep = EffectiveBoxExtentY * 2;
	const float ZStep = EffectiveBoxExtentZ * 2;
	const float BoardWidth = EffectiveBoxExtentY * 2 * Width;
	const float BoardHeight = EffectiveBoxExtentZ * 2 * Height;

	const FVector Origin = GetActorLocation();
	const FVector TopLeft(Origin.X, Origin.Y - BoardWidth / 2 + EffectiveBoxExtentY, Origin.Z + BoardHeight / 2 - EffectiveBoxExtentZ);

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const FVector Loc(Origin.X, TopLeft.Y + j * YStep, TopLeft.Z - i * ZStep);
			ACellActor* const SpawnedActorRef = GetWorld()->SpawnActor<ACellActor>(CellActor, Loc, GetActorRotation()); //const pointer to non-const CellActor
			CellActors.Add(SpawnedActorRef);
		}
	}
}

int AGridActor::CountAliveNeighbors(const int i, const int j) 
{
	int NumAliveNeighbors = 0;
	for (int k = -1; k <= 1; k++) {
		for (int l = -1; l <= 1; l++) {
			if (!(l == 0 && k == 0)) {
				const int effective_i = i + k;
				const int effective_j = j + l;
				if ((effective_i >= 0 && effective_i < Height) && (effective_j >= 0 && effective_j < Width)) {
					if (CellActors[effective_j + effective_i * Width]->GetAlive()) {
						NumAliveNeighbors++;
					}
				}
			}
		}
	}
	return NumAliveNeighbors;
}

void AGridActor::UpdateAliveNext(const int Index, const int NumAliveNeighbors) 
{
	const bool IsAlive = CellActors[Index]->GetAlive();
	if (IsAlive && (NumAliveNeighbors < 2))
	{
		CellActors[Index]->SetAliveNext(false);
	}
	else if (IsAlive && ((NumAliveNeighbors == 2) || (NumAliveNeighbors == 3)))
	{
		CellActors[Index]->SetAliveNext(true);
	}
	else if (IsAlive && (NumAliveNeighbors > 3))
	{
		CellActors[Index]->SetAliveNext(false);
	}
	else if (!IsAlive && (NumAliveNeighbors == 3))
	{
		CellActors[Index]->SetAliveNext(true);
	}
	else {
		CellActors[Index]->SetAliveNext(CellActors[Index]->GetAlive());
	}
}

void AGridActor::GenerateNext()
{
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const int NumAliveNeighbors = CountAliveNeighbors(i, j);
			UpdateAliveNext(j + i * Width, NumAliveNeighbors);
		}
	}
}

void AGridActor::UpdateNext() 
{
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const int Index = j + i * Width;
			CellActors[Index]->Update();
		}
	}
}

void AGridActor::Advance() 
{
	UE_LOG(LogTemp, Warning, TEXT("advancing"));
	GenerateNext();
	UpdateNext();
}


void AGridActor::ToEditMode()
{
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const int Index = j + i * Width;
			CellActors[Index]->SetActorHiddenInGame(false);
		}
	}
	ClearTimer();

}

void AGridActor::ToPlayMode() 
{
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			int Index = j + i * Width;
			//const bool IsAlive = CellActors[Index]->GetAlive();
			/*if (IsAlive) {
				CellActors[Index]->SetActorHiddenInGame(false);
			}
			else {
				CellActors[Index]->SetActorHiddenInGame(true);
			}*/
		}
	}
	StartTimer();
}

void AGridActor::StartTimer() 
{
	UE_LOG(LogTemp, Warning, TEXT("StartTimer"));

	GetWorld()->GetTimerManager().SetTimer(GridTimer, this, &AGridActor::Advance, AdvanceTime, true);
}

void AGridActor::ClearTimer() {
	GetWorld()->GetTimerManager().ClearTimer(GridTimer);
}

void AGridActor::Reset() 
{
	ClearTimer();
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const int Index = j + i * Width;
			CellActors[Index]->Reset();
		}
	}
}

void AGridActor::RandomGrid()
{
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			const int Index = j + i * Width;
			if (FMath::RandRange(0.0f, 1.0f) < 0.2f)
			{
				CellActors[Index]->SetAlive(true);
				CellActors[Index]->Random();
			}
		}
	}
}

float AGridActor::AddTime()
{
	if (AdvanceTime >= minTimer && AdvanceTime < maxTimer) {
		AdvanceTime += 0.1f;
	}
	return AdvanceTime;
}

float AGridActor::DeleteTime()
{
	if (AdvanceTime > minTimer && AdvanceTime <= maxTimer) {
		AdvanceTime -= 0.1f;
	}
	return AdvanceTime;

}



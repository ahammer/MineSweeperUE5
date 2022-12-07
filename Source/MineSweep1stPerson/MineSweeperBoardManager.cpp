// Fill out your copyright notice in the Description page of Project Settings.


#include "MineSweeperBoardManager.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>
#include <Runtime/Engine/Classes/Components/TextRenderComponent.h>

// Sets default values
AMineSweeperBoardManager::AMineSweeperBoardManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMineSweeperBoardManager::BeginPlay()
{
	Super::BeginPlay();

	UStaticMeshComponent* area = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Area")));
	FBox box = area->Bounds.GetBox();

	FVector center = box.GetCenter();
	FVector extents = box.GetExtent();
	float minx = center.X - extents.X;
	float maxx = center.X + extents.X;
	float miny = center.Y - extents.Y;
	float maxy = center.Y + extents.Y;
	float z = center.Z;
	float stepx = (maxx - minx) / width;
	float stepy = (maxy - miny) / height;

	

	
	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {			
			
			ALandMine* actor = Cast<ALandMine>(GetWorld()->SpawnActor(TileType1));			
			actor->SetActorLocation(FVector(minx+x*stepx, miny+y*stepy, z));
			actor->SetActorScale3D(FVector(5,5,5));
			actors.push_back(actor);
		}
	}
	// Assign Mines
	int minesAssigned = 0;
	while (minesAssigned < mines) {
		ALandMine* random = getMine(rand() % width, rand() % height);
		if (!random->isBomb) {
			random->isBomb = true;
			minesAssigned++;
		}
	}

	// Count Neighbours
	for (int y = 0; y < width; y++) {
		for (int x = 0; x < height; x++) {
			getMine(x, y)->neighbours = neighbours(x, y);
		}
	}



}

// Called every frame
void AMineSweeperBoardManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	clearPositions();
	handleTarget();
}

void AMineSweeperBoardManager::handleTarget() {
	APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	double min_distance = 1000000000;
	ALandMine* shortest = NULL;
	selectedMine = NULL;

	for (int i = 0; i < width * height; i++) {
		ALandMine* curr = actors[i];
		curr->target = false;
		if (curr->revealed && !curr->locked) {
			continue;
		}

		double curr_dist = FVector::Dist(curr->GetActorLocation(), pawn->GetActorLocation());
		if (curr_dist < min_distance) {
			min_distance = curr_dist;
			shortest = curr;
		}
	
	}

	if (shortest != NULL) {
		shortest->target = true;
		selectedMine = shortest;
	}
}

ALandMine* AMineSweeperBoardManager::getMine(int x, int y)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return nullptr;

	return actors[y*width + x];
}

int AMineSweeperBoardManager::neighbours(int x, int y)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return 0;

	int sum = 0;
	for (int ax = -1; ax <= 1; ax++) {
		for (int ay = -1; ay <= 1; ay++) {
			if (!(ax == 0 && ay == 0)) {
				ALandMine* neighbour = getMine(x + ax, y + ay);
				if (neighbour != nullptr) {
					if (neighbour->isBomb) {
						sum++;
					}
				}
			}
		}
	}
	return sum;
}

bool AMineSweeperBoardManager::hasZeroExposedNeighbour(int x, int y)
{
	if (y < 0 || y >= height || x < 0 || x >= width)
		return 0;

	int sum = 0;
	ALandMine* a = getMine(x - 1, y);
	ALandMine* b = getMine(x + 1, y);
	ALandMine* c = getMine(x, y + 1);
	ALandMine* d = getMine(x, y - 1);
	ALandMine* e = getMine(x - 1, y + 1);
	ALandMine* f = getMine(x - 1, y - 1);
	ALandMine* g = getMine(x + 1, y + 1);
	ALandMine* h = getMine(x + 1, y - 1);

	if (a != nullptr && a->revealed && a->neighbours == 0) {
		return true;
	}
	if (b != nullptr && b->revealed && b->neighbours == 0) {
		return true;
	}
	if (c != nullptr && c->revealed && c->neighbours == 0) {
		return true;
	}
	if (d != nullptr && d->revealed && d->neighbours == 0) {
		return true;
	}
	if (e != nullptr && e->revealed && e->neighbours == 0) {
		return true;
	}
	if (f != nullptr && f->revealed && f->neighbours == 0) {
		return true;
	}
	if (g != nullptr && g->revealed && g->neighbours == 0) {
		return true;
	}
	if (h != nullptr && h->revealed && h->neighbours == 0) {
		return true;
	}


	return false;	
}


void AMineSweeperBoardManager::clearPositions()
{
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			ALandMine* mine = getMine(x, y);
			if (!mine->isBomb && !mine->revealed && hasZeroExposedNeighbour(x,y)) {
				mine->Touch();
			}
		}
	}
}

void AMineSweeperBoardManager::ToggleLock_Implementation() 
{
	if (selectedMine != NULL) {
		if (selectedMine->locked) {
			locks--;
		}
		else {
			if (locks >= mines) {
				return;
			}
			locks++;
		}
		selectedMine->ToggleLock();
	}

}
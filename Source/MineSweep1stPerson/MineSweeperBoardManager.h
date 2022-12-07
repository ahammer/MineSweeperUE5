// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <MineSweep1stPerson/LandMine.h>
#include "MineSweeperBoardManager.generated.h"


UCLASS()
class MINESWEEP1STPERSON_API AMineSweeperBoardManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMineSweeperBoardManager();
	
	UPROPERTY(EditAnywhere, Category = "Board Size")
	int width = 10;
	
	UPROPERTY(EditAnywhere, Category = "Board Size")
	int height = 10;

	UPROPERTY(EditAnywhere, Category = "Spacing")
	float spacing = 10.0;

	UPROPERTY(EditAnywhere, Category = "LandMineActor")
	TSubclassOf<ALandMine> TileType1;

	UPROPERTY(BlueprintReadOnly, Category = "Mine Count")
	int mines = 20;

	UPROPERTY(BlueprintReadOnly, Category = "Lock Count")
	int locks = 0;


	

	UFUNCTION(BlueprintNativeEvent)
	void ToggleLock();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	ALandMine* getMine(int x, int y);
	ALandMine* selectedMine = NULL;
	int neighbours(int x, int y);
	std::vector<ALandMine*> actors;
	void clearPositions();
	void handleTarget();
	bool hasZeroExposedNeighbour(int x, int y);


};

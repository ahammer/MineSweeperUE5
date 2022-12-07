// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LandMine.generated.h"

UCLASS()
class MINESWEEP1STPERSON_API ALandMine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALandMine();

	UPROPERTY(EditAnywhere, Category = "Material")
	class UMaterial* LandMineMaterial;
	float distance = 1.0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool isBomb = false;
	bool revealed = false;
	bool showCount = false;

	UPROPERTY(BlueprintReadOnly, Category = "Neighbours")
	int neighbours = 0;

	UPROPERTY(BlueprintReadOnly, Category = "Target")
	bool target = false;
	bool locked = false;


	
	UFUNCTION(BlueprintCallable)
	void Touch();

	UFUNCTION(BlueprintNativeEvent)
		void Explode();

	UFUNCTION(BlueprintNativeEvent)
		void Fizzle();

	UFUNCTION(BlueprintNativeEvent)
		void ToggleLock();

	UFUNCTION(BlueprintNativeEvent)
		void Lock();

	UFUNCTION(BlueprintNativeEvent)
		void Unlock();



private:
	void updateTextState();
	void updateColor();

	FVector4 targetColor();

	//Vector4 neutral_color;
	//FInt32Vector4 bomb_color;
	//FInt32Vector4 neutral_color;
	FVector4 currentColor = FVector4(0, 0, 0, 1);

	const FVector4 enabledColor = FVector4(0.8, 0.8, 0.9, 1);
	const FVector4 selectedColor = FVector4(0.0, 0.0, 0.9, 1);
	const FVector4 disabledColor = FVector4(0, 0, 0, 1);
	const FVector4 bombColor = FVector4(1, 0, 0, 1);

	const float randomOffset = (rand() % 1000) / 1000.0;	
};

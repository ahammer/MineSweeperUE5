// Fill out your copyright notice in the Description page of Project Settings.


#include "LandMine.h"
#include <Runtime/Engine/Classes/Components/TextRenderComponent.h>
#include <string>

// Sets default values
ALandMine::ALandMine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALandMine::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALandMine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector4 tc = targetColor();
	currentColor.X = (currentColor.X * 9 + tc.X) / 10;
	currentColor.Y = (currentColor.Y * 9 + tc.Y) / 10;
	currentColor.Z = (currentColor.Z * 9 + tc.Z) / 10;
	updateColor();
	
	
	/*
	TArray<AActor*> FoundActors;
	APawn* pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	FVector playerLocation = pawn->GetActorLocation();
	FVector mineLocation = GetActorLocation();
		
	
	float cdistance = FVector::Dist(playerLocation, mineLocation);
	cdistance = cdistance / 1500.0;
	if (cdistance > 1) {
		cdistance = 1;
	}

	distance = cdistance;

	if (revealed) {
		UTextRenderComponent* text = FindComponentByClass<UTextRenderComponent>();
		if (isBomb) {
			text->SetText(FText::FromString("Bomb"));
			text->SetVisibility(true);
		}
		else {
			if (neighbours != 0) {
				text->SetText(FText::FromString(std::to_string(neighbours).c_str()));
				
			}
			else {
				text->SetText(FText::FromString("."));
			}
			text->SetVisibility(true);
		}
		
		
	}

	if (distance < 0.10 && !revealed) {

		
	}
	*/
}

void ALandMine::Touch()
{
	updateTextState();
	if (revealed) {
		return;
	}

	revealed = true;

	if (isBomb) {
		Explode();
	}
	else {
		Fizzle();
	}


}

void ALandMine::updateTextState()
{
	UTextRenderComponent* text = FindComponentByClass<UTextRenderComponent>(); 
	if (isBomb) {
		text->SetText(FText::FromString("Bomb"));
		text->SetVisibility(true);
	}
	else {
		if (neighbours != 0) {
			text->SetText(FText::FromString(std::to_string(neighbours).c_str()));

		}
		else {
			text->SetText(FText::FromString("."));
		}
		text->SetVisibility(true);
	}
}

void ALandMine::updateColor()
{
	UStaticMeshComponent* light = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Light")));
	UMaterialInstanceDynamic* mat = Cast<UMaterialInstanceDynamic>(light->GetMaterial(0));
	float multiplier_f = (cosf(GetWorld()->TimeSeconds * 3 + randomOffset*5) + 1) / 2.0 + 0.5;
	multiplier_f *= multiplier_f;

	FVector4 multiplier_vec = FVector4(multiplier_f, multiplier_f, multiplier_f , 1.0);
	FVector4 combined = multiplier_vec * currentColor;
	mat->SetVectorParameterValue("color", combined);
}

FVector4 ALandMine::targetColor()
{
	if (target && !(revealed && isBomb)) {
		return selectedColor;
	} else if (revealed) {
		if (isBomb) {
			return bombColor;
		}
		else {
			return disabledColor;
		}
	}
	else {
		return enabledColor;
	}
	return disabledColor;
}



void ALandMine::Explode_Implementation()
{
}


void ALandMine::Fizzle_Implementation()
{

}


void ALandMine::ToggleLock_Implementation()
{

	locked = !locked;
	if (locked) {
		Lock();
	}
	else {
		Unlock();
	}
}



void ALandMine::Unlock_Implementation()
{

	
}



void ALandMine::Lock_Implementation()
{

	
}



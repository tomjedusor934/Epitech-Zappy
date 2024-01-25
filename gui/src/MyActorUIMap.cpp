// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorUIMap.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

AMyActorUIMap::AMyActorUIMap()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyActorUIMap::BeginPlay()
{
	Super::BeginPlay();
}

void AMyActorUIMap::UpdateText(const FString& NewText)
{
}

void AMyActorUIMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

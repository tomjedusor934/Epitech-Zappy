// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorUIMap.generated.h"

class UUserWidget;

UCLASS()
class ZAPPY_3_API AMyActorUIMap : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyActorUIMap();

	// Function to update the text
	void UpdateText(const FString& NewText);

	UPROPERTY(EditAnywhere, Category = "UI")
		TSubclassOf<UUserWidget> WidgetClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyDeraumere.generated.h"

UCLASS()
class ZAPPY_3_API AMyDeraumere : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMyDeraumere();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

};
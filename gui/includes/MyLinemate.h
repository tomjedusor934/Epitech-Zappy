// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyLinemate.generated.h"

UCLASS()
class ZAPPY_3_API AMyLinemate : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyLinemate();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

private:
    UPROPERTY(VisibleAnywhere)
        UStaticMeshComponent* VisualMesh;
};

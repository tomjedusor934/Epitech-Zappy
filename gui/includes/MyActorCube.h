// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActorCube.generated.h"

UCLASS()
class ZAPPY_3_API AMyActorCube : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActorCube();

	void SetHighlight(bool bHighlight);

	bool IsHighlighted() const;

	UFUNCTION()
		void OnBeginMouseOver(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
		void OnEndMouseOver(UPrimitiveComponent* TouchedComponent);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Highlight")
		bool bIsHighlighted;
	FVector InitialLocation;

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisualMesh;

};

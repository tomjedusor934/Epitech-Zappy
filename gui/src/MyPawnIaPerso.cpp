// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnIaPerso.h"

// Sets default values
AMyPawnIaPerso::AMyPawnIaPerso()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyPawnIaPerso::BeginPlay()
{
	Super::BeginPlay();

    VisualMesh->SetMobility(EComponentMobility::Movable);
	
}

// Called every frame
void AMyPawnIaPerso::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPawnIaPerso::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


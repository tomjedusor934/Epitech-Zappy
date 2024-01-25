// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDeraumere.h"

// Sets default values
AMyDeraumere::AMyDeraumere()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = VisualMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/MyAssets/stone_smallB.stone_smallB"));
    if (SphereVisualAsset.Succeeded()) {
        VisualMesh->SetStaticMesh(SphereVisualAsset.Object);
        VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
    }
}

// Called when the game starts or when spawned
void AMyDeraumere::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyDeraumere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


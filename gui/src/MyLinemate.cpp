// Fill out your copyright notice in the Description page of Project Settings.


#include "MyLinemate.h"

// Sets default values
AMyLinemate::AMyLinemate()
{
	PrimaryActorTick.bCanEverTick = true;

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = VisualMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/MyAssets/stone_smallA.stone_smallA"));
    if (SphereVisualAsset.Succeeded()) {
        VisualMesh->SetStaticMesh(SphereVisualAsset.Object);
        VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
    }
}

// Called when the game starts or when spawned
void AMyLinemate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyLinemate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


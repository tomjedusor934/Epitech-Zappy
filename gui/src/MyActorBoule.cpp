// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorBoule.h"

// Sets default values
AMyActorBoule::AMyActorBoule()
{
    PrimaryActorTick.bCanEverTick = true;

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = VisualMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere1.Shape_Sphere1"));
    if (SphereVisualAsset.Succeeded()) {
        VisualMesh->SetStaticMesh(SphereVisualAsset.Object);
        VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
    }
}

void AMyActorBoule::BeginPlay()
{
    Super::BeginPlay();
}

void AMyActorBoule::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
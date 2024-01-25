// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPhiras.h"

// Sets default values
AMyPhiras::AMyPhiras()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = VisualMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/MyAssets/stone_smallE.stone_smallE"));
    if (SphereVisualAsset.Succeeded()) {
        VisualMesh->SetStaticMesh(SphereVisualAsset.Object);
        VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
    }
}

// Called when the game starts or when spawned
void AMyPhiras::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPhiras::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorTree.h"

// Sets default values
AMyActorTree::AMyActorTree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    this->VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    this->VisualMesh->SetupAttachment(RootComponent);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/MyAssets/tree_blocks_fall.tree_blocks_fall"));

    if (CubeVisualAsset.Succeeded()) {
        this->VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
        this->VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        SetActorScale3D(FVector(50.0f, 50.0f, 50.0f));
    }

}

// Called when the game starts or when spawned
void AMyActorTree::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorTree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


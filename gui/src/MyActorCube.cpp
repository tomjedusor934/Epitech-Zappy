// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorCube.h"

// Sets default values
AMyActorCube::AMyActorCube()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    this->VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    this->VisualMesh->SetupAttachment(RootComponent);
    this->VisualMesh->SetNotifyRigidBodyCollision(true);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/MyAssets/stone_largeC.stone_largeC"));

    if (CubeVisualAsset.Succeeded()) {
        this->VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
        this->VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
        SetActorScale3D(FVector(1.0f, 1.0f, 1.0f));
    }

    VisualMesh->OnBeginCursorOver.AddDynamic(this, &AMyActorCube::OnBeginMouseOver);
    VisualMesh->OnEndCursorOver.AddDynamic(this, &AMyActorCube::OnEndMouseOver);
}

void AMyActorCube::SetHighlight(bool bHighlight)
{
    bIsHighlighted = bHighlight;

    // Activer ou désactiver la surbrillance
    VisualMesh->SetRenderCustomDepth(bHighlight);
}



bool AMyActorCube::IsHighlighted() const
{
    return bIsHighlighted;
}


void AMyActorCube::OnBeginMouseOver(UPrimitiveComponent* TouchedComponent)
{
    // Sauvegarder la position initiale du cube
    InitialLocation = GetActorLocation();

    // Déplacer le cube vers le haut
    FVector NewLocation = InitialLocation + FVector(0.0f, 0.0f, 20.0f);
    SetActorLocation(NewLocation);

    // Activer la surbrillance
    SetHighlight(true);
}

void AMyActorCube::OnEndMouseOver(UPrimitiveComponent* TouchedComponent)
{
    // Replacer le cube à sa position initiale
    SetActorLocation(InitialLocation);

    // Désactiver la surbrillance
    SetHighlight(false);
}

// Called when the game starts or when spawned
void AMyActorCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActorCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


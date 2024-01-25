// Fill out your copyright notice in the Description page of Project Settings.

#include "MySetNuclear.h"

// Sets default values
AMySetNuclear::AMySetNuclear()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = VisualMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
    if (SphereVisualAsset.Succeeded()) {

        RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

        ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
        ParticleSystemComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

        VisualMesh->SetStaticMesh(SphereVisualAsset.Object);
        VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -100.0f));
        SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));
    }
}

// Called when the game starts or when spawned
void AMySetNuclear::BeginPlay()
{
	Super::BeginPlay();

    SpawnParticles();
	
}

// Called every frame
void AMySetNuclear::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMySetNuclear::SpawnParticles()
{
    UParticleSystem* ParticleSystem = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/FXVarietyPack/Particles/P_ky_explosion.P_ky_explosion"));

    if (ParticleSystem)
    {
        ParticleSystemComponent->SetTemplate(ParticleSystem);
        ParticleSystemComponent->ActivateSystem();
    }
}

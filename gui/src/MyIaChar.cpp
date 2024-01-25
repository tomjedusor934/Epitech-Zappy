// Fill out your copyright notice in the Description page of Project Settings.


#include "MyIaChar.h"

// Sets default values
AMyIaChar::AMyIaChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = VisualMesh;
	VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Sci_Fi_Character_08/Mesh/Character/SK_Sci_Fi_Character_08_Full_01.SK_Sci_Fi_Character_08_Full_01"));
	if (MeshAsset.Succeeded())
	{
		VisualMesh->SetSkeletalMesh(MeshAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	// Charger l'animation par défaut
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationAsset(TEXT("/Game/Sci_Fi_Character_08/Demo/Animations/ThirdPersonIdle.ThirdPersonIdle"));
	if (AnimationAsset.Succeeded())
	{
		anim = AnimationAsset.Object;
	}

}

// Called when the game starts or when spawned
void AMyIaChar::BeginPlay()
{
	Super::BeginPlay();

	if (anim)
	{
		VisualMesh->PlayAnimation(anim, true);
	}
	
	VisualMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

// Called every frame
void AMyIaChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyIaChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Fill out your copyright notice in the Description page of Project Settings.



#include "MyActorPersoIaPrinc.h"
#include "Animation/AnimationAsset.h"
#include "Animation/AnimSequence.h"

// Sets default values
AMyActorPersoIaPrinc::AMyActorPersoIaPrinc()
{
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = VisualMesh;
	VisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	arrayAnim.Empty();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/MyAssets/perso/Vanguard_By_T__Choonyung.Vanguard_By_T__Choonyung"));
	if (MeshAsset.Succeeded())
	{
		VisualMesh->SetSkeletalMesh(MeshAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
	}

	// Charger l'animation par défaut
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationIdle(TEXT("/Game/MyAssets/perso/Happy_Idle_Anim.Happy_Idle_Anim"));
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationAsset(TEXT("/Game/MyAssets/perso/Dancing_Twerk_Anim.Dancing_Twerk_Anim"));
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationJump(TEXT("/Game/MyAssets/perso/Mutant_Jumping_Anim.Mutant_Jumping_Anim"));
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationDie(TEXT("/Game/MyAssets/perso/Sword_And_Shield_Death_Anim.Sword_And_Shield_Death_Anim"));
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationKick(TEXT("/Game/MyAssets/perso/Mma_Kick_Anim.Mma_Kick_Anim"));
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationPickup(L"/Game/MyAssets/perso/Unarmed_Grab_Torch_From_Floor_Anim.Unarmed_Grab_Torch_From_Floor_Anim");
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationBroadCast(L"/Game/MyAssets/perso/Yelling_Out_Anim.Yelling_Out_Anim");
	static ConstructorHelpers::FObjectFinder<UAnimSequence> AnimationDance(L"/Game/MyAssets/perso/Macarena_Dance_Anim.Macarena_Dance_Anim");


	//light

	AttachedLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("AttachedLight"));
	AttachedLight->SetupAttachment(RootComponent);


	if (AnimationAsset.Succeeded() && AnimationJump.Succeeded())
	{
		arrayAnim.Add("idle", AnimationIdle.Object);
		arrayAnim.Add("Jump", AnimationJump.Object);
		arrayAnim.Add("Twerk", AnimationAsset.Object);
		arrayAnim.Add("Die", AnimationDie.Object);
		arrayAnim.Add("Pickup", AnimationPickup.Object);
		arrayAnim.Add("Kick", AnimationKick.Object);
		arrayAnim.Add("Broad", AnimationBroadCast.Object);
		arrayAnim.Add("dance", AnimationDance.Object);

		anim = AnimationIdle.Object;
	}
}

bool AMyActorPersoIaPrinc::checkIsPlaying()
{
	if (this->VisualMesh->IsPlaying())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void AMyActorPersoIaPrinc::BeginPlay()
{
	Super::BeginPlay();

	if (anim)
	{
		VisualMesh->PlayAnimation(anim, true);
	}

	if (AttachedLight != nullptr)
	{
		AttachedLight->SetLightColor(FLinearColor::Red);
	}
}

void AMyActorPersoIaPrinc::SetTeamColor(const FLinearColor& TeamColor)
{
	if (AttachedLight != nullptr)
	{
		AttachedLight->SetLightColor(TeamColor);
		AttachedLight->SetIntensity(5000.0f);
	}
}

void AMyActorPersoIaPrinc::PlayAnimation(FString name)
{
	if (arrayAnim.Contains(name))
	{
		UAnimSequence* AnimationSequence = arrayAnim[name];
		if (AnimationSequence != nullptr)
		{
			bool bLooping = true;

			if (name == "Jump" || name == "Die" || name == "Pickup" || name == "Kick" || name == "Broad")
			{
				bLooping = false;
			}

			if (VisualMesh != nullptr)
			{
				VisualMesh->PlayAnimation(AnimationSequence, bLooping);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("VisualMesh is nullptr"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Animation sequence for %s is nullptr"), *name);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Animation %s not found in arrayAnim"), *name);
	}
}
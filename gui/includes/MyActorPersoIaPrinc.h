// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "Components/LightComponent.h"
#include "MyActorPersoIaPrinc.generated.h"

UCLASS()
class ZAPPY_3_API AMyActorPersoIaPrinc : public AActor
{
    GENERATED_BODY()

public:
    AMyActorPersoIaPrinc();
    void PlayAnimation(FString name);

    UFUNCTION(BlueprintCallable, Category = "Team")
        void SetTeamColor(const FLinearColor& TeamColor);

    bool checkIsPlaying();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Light")
        class UPointLightComponent* AttachedLight;

    void SetLightIntensity(float Intensity)
    {
        if (AttachedLight != nullptr)
        {
            AttachedLight->SetIntensity(Intensity);
        }
    }


protected:
    virtual void BeginPlay() override;


private:
    UPROPERTY(VisibleAnywhere)
        USkeletalMeshComponent* VisualMesh;

    TMap<FString, UAnimSequence*> arrayAnim;

    class UAnimSequence* anim;

    UParticleSystemComponent* ParticleSystemComponent;

};

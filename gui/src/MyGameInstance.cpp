// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "MyServerConnection.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "MyServerConnection.h"
#include "MyActorCube.h"

void UMyGameInstance::Init()
{
    Super::Init();

    UE_LOG(LogTemp, Warning, TEXT("Coucou ma gueule"));

    UWorld* World = GetWorld();

    FVector location(0.0f, 0.0f, 0.0f);
    FRotator rota(0.0f, 0.0f, 0.0f);

    if (World) {
        serverconnection = World->SpawnActor<AMyServerConnection>(AMyServerConnection::StaticClass(), location, rota);
    }
}
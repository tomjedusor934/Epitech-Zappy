// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyServerConnection.h"	
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ZAPPY_3_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	void Init();

	UPROPERTY(BlueprintReadWrite, Category = "GameInstance")
		AMyServerConnection* serverconnection;
};

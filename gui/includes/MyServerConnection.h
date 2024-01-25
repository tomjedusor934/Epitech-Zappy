#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Components/PanelWidget.h"
#include "MyActorPersoIaPrinc.h"
#include "MyLinemate.h"
#include "MyBurger.h"
#include "MyDeraumere.h"
#include "MySibur.h"
#include "MyMendiane.h"
#include "MyPhiras.h"
#include "MyThystame.h"

#include "Blueprint/UserWidget.h"

#include "MyEgg.h"

#include "MyServerConnection.generated.h"


USTRUCT(BlueprintType)
struct FPosIa
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "PosIa")
		int32 nbIa;

	UPROPERTY(BlueprintReadWrite, Category = "PosIa")
		int32 X;

	UPROPERTY(BlueprintReadWrite, Category = "PosIa")
		int32 Y;

	UPROPERTY(BlueprintReadWrite, Category = "PosIa")
		int32 Orien;

	UPROPERTY(BlueprintReadWrite, Category = "PosIa")
		int32 Level;

	UPROPERTY(BlueprintReadWrite, Category = "PosIa")
		FString TeamName;

	UPROPERTY(BlueprintReadWrite, Category = "PosIa")
		AMyActorPersoIaPrinc* ActorIa;

	// Constructeur par défaut pour initialiser les membres
	FPosIa()
		: nbIa(0)
		, X(-1)
		, Y(-1)
		, Orien(0)
		, Level(0)
		, TeamName("")
		, ActorIa(nullptr)
	{
	}
};

USTRUCT(BlueprintType)
struct FMapCell
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "MapCell")
		int32 Food;

	UPROPERTY(BlueprintReadWrite, Category = "MapCell")
		int32 linemate;

	UPROPERTY(BlueprintReadWrite, Category = "MapCell")
		int32 deraumere;

	UPROPERTY(BlueprintReadWrite, Category = "MapCell")
		int32 sibur;

	UPROPERTY(BlueprintReadWrite, Category = "MapCell")
		int32 mendiane;

	UPROPERTY(BlueprintReadWrite, Category = "MapCell")
		int32 phiras;

	UPROPERTY(BlueprintReadWrite, Category = "MapCell")
		int32 thystame;

	UPROPERTY(BlueprintReadWrite, Category = "MapCell")
		int32 Egg;

	UPROPERTY(BlueprintReadWrite, Category = "MapCellActor")
		AMyBurger* FoodActor;

	UPROPERTY(BlueprintReadWrite, Category = "MapCellActor")
		AMyLinemate* linemateActor;

	UPROPERTY(BlueprintReadWrite, Category = "MapCellActor")
		AMyDeraumere* deraumereActor;

	UPROPERTY(BlueprintReadWrite, Category = "MapCellActor")
		AMySibur* siburActor;

	UPROPERTY(BlueprintReadWrite, Category = "MapCellActor")
		AMyMendiane* mendianeActor;

	UPROPERTY(BlueprintReadWrite, Category = "MapCellActor")
		AMyPhiras* phirasActor;

	UPROPERTY(BlueprintReadWrite, Category = "MapCellActor")
		AMyThystame* thystameActor;

	UPROPERTY(BlueprintReadWrite, Category = "MapCellActor")
		AMyEgg* EggActor;

	// Constructeur par défaut pour initialiser les membres
	FMapCell()
		: Food(-1)
		, linemate(-1)
		, deraumere(-1)
		, sibur(-1)
		, mendiane(-1)
		, phiras(-1)
		, thystame(-1)
		, Egg(-1)
		, FoodActor(nullptr)
		, linemateActor(nullptr)
		, deraumereActor(nullptr)
		, siburActor(nullptr)
		, mendianeActor(nullptr)
		, phirasActor(nullptr)
		, thystameActor(nullptr)
		, EggActor(nullptr)
	{
	}
};

UCLASS()
class ZAPPY_3_API AMyServerConnection : public AActor, public FRunnable
{
	GENERATED_BODY()

public:

	//fonction gestion connection server

	AMyServerConnection();

	UFUNCTION(BlueprintCallable, category = "Connexion")
		void ConnectToServer(const FString& ServerIP, int32 ServerPort);

	void ReceiveData();
	void SendData(const FString& DataToSend);

	//generation de la map
	void GenerateMap();

	void updateMap();

	void updateMapMovable();


	UPROPERTY(BlueprintReadWrite, Category = "PosIa")
		TArray<FPosIa> PosIaArray;

	// Tableau à une dimension pour stocker les cellules de la carte
	UPROPERTY(BlueprintReadWrite, Category = "Map")
		TArray<FMapCell> MapData;

	// Dimensions de la carte
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
		int32 SizeXmapArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map")
		int32 SizeYmapArray;

	int32 Index = 0;

	// Fonction de conversion d'indices 2D à 1D
	int32 GetIndex(int32 X, int32 Y) const
	{
		return Y * sizeX + X;
	}

	UFUNCTION()
		void OnMouseClicked(AActor* ClickedActor, FKey ButtonClicked, APlayerController *PlayerController);

	UFUNCTION()
		void OnMouseClickedOnIa(AActor* ClickedActor, FKey ButtonClicked, APlayerController* PlayerController);


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
		TSubclassOf<UUserWidget> WidgetTemplate;

	UPROPERTY()
		UUserWidget* WidgetInstance;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
		TSubclassOf<UUserWidget> WidgetTemplateVictoire;

	UPROPERTY()
		UUserWidget* WidgetInstanceVictoire;


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
		UCameraComponent* CameraComponent;

	AMyActorPersoIaPrinc* BallActor;

private:

	int32 TickInterval = 0; // Appel de Tick toutes les 1 seconde

	FSocket* Socket;

	ISocketSubsystem* ISocket;

	FRunnableThread* ReceiveThread;
	TArray<uint8> ReceivedData;
	FCriticalSection DataMutex;

	int32 sizeX;
	int32 sizeY;

	int32 sizeloadx;
	int32 sizeloady;

	bool bIsConnected;
	bool IsStopping;

	bool arrayisFull;

	bool arrayIaisFull;

	bool bMapDataFilled;

	int32 DataCount = 0;
	bool bAllDataReceived = false;

	bool load = false;

	bool bShowText = true;

	bool bShowDetailCase = false;

	bool WaitingFirstIa = false;

	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	bool move_perso_ppo = false;

	bool gen_map = false;

	bool loadMap = false;

	FString nameFirstTeam = "";
	FString nameScdTeam = "";
	FString nameThrstTeam = "";
	FString nameFrthTeam = "";
	FString nameFvthTeam = "";

	int32 nbTeam1 = 0;
	int32 nbTeam2 = 0;
	int32 nbTeam3 = 0;
	int32 nbTeam4 = 0;
	int32 nbTeam5= 0;

	bool IsConstruct;
};

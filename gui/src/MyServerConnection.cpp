// Fill out your copyright notice in the Description page of Project Settings.

//include de la class:
#include "MyServerConnection.h"

//include pour la connection au server:
#include "Sockets.h"
#include "SocketSubsystem.h"

//include pour la génération 
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

//include de mes mesh:
#include "MyActorCube.h"
#include "MyActorTree.h"
#include "MyActorBoule.h"

//#include "MyActorPersoIaPrinc.h"
#include "MyIaChar.h"

//include math pour le rand:
#include "Math/RandomStream.h"

//include pour la gestion des event
#include "Components/InputComponent.h"

//include camera
#include "Camera/CameraComponent.h"

//include PlayerStart
#include "GameFramework/PlayerStart.h"
#include <Runtime/Engine/Classes/Kismet/GameplayStatics.h>

#include "DrawDebugHelpers.h"

#include "MySetNuclear.h"

#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

#include "Components/TextBlock.h"



AMyServerConnection::AMyServerConnection()
{
    PrimaryActorTick.bCanEverTick = true;

    this->arrayisFull = false;
    this->bMapDataFilled = false;

    this->sizeX = 0;
    this->sizeY = 0;
    this->Index = 0;

    this->IsConstruct = false;

    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/UI/UI_Case_Map"));

    if (WidgetClassFinder.Succeeded())
    {
        WidgetTemplate = WidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinderVictoire(TEXT("/Game/UI/victoire"));

    if (WidgetClassFinderVictoire.Succeeded())
    {
        WidgetTemplateVictoire = WidgetClassFinderVictoire.Class;
    }
}

void AMyServerConnection::OnMouseClicked(AActor* ClickedActor, FKey ButtonClicked, APlayerController *PlayerController)
{
    if (ClickedActor)
    {
        // Vérifiez si l'acteur cliqué est une pierre (AMyActorCube)
        AMyActorCube* CubeActor = Cast<AMyActorCube>(ClickedActor);
        if (CubeActor)
        {
            FString ActorName = CubeActor->GetName();

            // Découper la chaîne de nom de l'acteur en utilisant "_" comme délimiteur
            TArray<FString> NameParts;
            ActorName.ParseIntoArray(NameParts, TEXT("_"), true);


            if (NameParts.Num() >= 1)
            {
                FString NumString = NameParts[1];

                // Convertir la chaîne de caractères en un entier
                int32 Num = FCString::Atoi(*NameParts[1]);


                // Utiliser la variable Num pour accéder au contenu de la case correspondante dans MapData

                if (Num >= 0 && Num < MapData.Num() && Num >= 0)
                {
                    FMapCell& MapCell = MapData[Num];

                    FString TextToDisplay = FString::Printf(TEXT("case number: %d\nfood: %d\nLinemate: %d\nDeraumere: %d\nMendiane: %d\nPhiras: %d\nSibur: %d\nThystame: %d\nEgg: %d"),
                        Num + 1, MapData[Num].Food, MapData[Num].linemate, MapData[Num].deraumere, MapData[Num].mendiane, MapData[Num].phiras, MapData[Num].sibur, MapData[Num].thystame, MapData[Num].Egg + 1);
                    FVector2D TextPosition2D(-2500.0f, 0.0f);

                    FVector TextPosition(TextPosition2D.X, TextPosition2D.Y, 0.0f);
                    FColor TextColor = FColor::White;

                    // Augmenter la taille du texte en définissant une échelle (Scale) plus grande
                    float TextScale = 2.0f;

                    if (WidgetInstance == nullptr)
                    {
                        APlayerController* PlayerControllerUI = UGameplayStatics::GetPlayerController(GetWorld(), 0);

                        if (PlayerControllerUI)
                        {
                            WidgetInstance = CreateWidget<UUserWidget>(PlayerControllerUI, WidgetTemplate);

                            if (WidgetInstance)
                            {
                                WidgetInstance->AddToViewport();
                                int32 CaseNumber = Num + 1;
                                int32 FoodCount = MapCell.Food;
                                int32 LinemateCount = MapCell.linemate;
                                int32 DeraumereCount = MapCell.deraumere;
                                int32 MendianeCount = MapCell.mendiane;
                                int32 PhirasCount = MapCell.phiras;
                                int32 SiburCount = MapCell.sibur;
                                int32 ThystameCount = MapCell.thystame;
                                int32 EggCount = MapCell.Egg + 1;

                                UTextBlock* MyTextBoxCase = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName(TEXT("TextBlock_8")));
                                if (MyTextBoxCase)
                                {
                                    FText NumberCaseText = FText::FromString(FString::Printf(TEXT("%d"), CaseNumber));
                                    MyTextBoxCase->SetText(NumberCaseText);
                                }

                                UTextBlock* MyTextBoxFood = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName(TEXT("TextBlock_9")));
                                if (MyTextBoxFood)
                                {
                                    FText NumberCaseText = FText::FromString(FString::Printf(TEXT("%d"), FoodCount));
                                    MyTextBoxFood->SetText(NumberCaseText);
                                }

                                UTextBlock* MyTextBoxLinemate = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName(TEXT("TextBlock_10")));
                                if (MyTextBoxLinemate)
                                {
                                    FText NumberCaseText = FText::FromString(FString::Printf(TEXT("%d"), LinemateCount));
                                    MyTextBoxLinemate->SetText(NumberCaseText);
                                }

                                UTextBlock* MyTextBoxDeraumere = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName(TEXT("TextBlock_11")));
                                if (MyTextBoxDeraumere)
                                {
                                    FText NumberCaseText = FText::FromString(FString::Printf(TEXT("%d"), DeraumereCount));
                                    MyTextBoxDeraumere->SetText(NumberCaseText);
                                }

                                UTextBlock* MyTextBoxMendiane = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName(TEXT("TextBlock_12")));
                                if (MyTextBoxMendiane)
                                {
                                    FText NumberCaseText = FText::FromString(FString::Printf(TEXT("%d"), MendianeCount));
                                    MyTextBoxMendiane->SetText(NumberCaseText);
                                }

                                UTextBlock* MyTextBoxPhiras = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName(TEXT("TextBlock_13")));
                                if (MyTextBoxPhiras)
                                {
                                    FText NumberCaseText = FText::FromString(FString::Printf(TEXT("%d"), PhirasCount));
                                    MyTextBoxPhiras->SetText(NumberCaseText);
                                }

                                UTextBlock* MyTextBoxSibur = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName(TEXT("TextBlock_14")));
                                if (MyTextBoxSibur)
                                {
                                    FText NumberCaseText = FText::FromString(FString::Printf(TEXT("%d"), SiburCount));
                                    MyTextBoxSibur->SetText(NumberCaseText);
                                }

                                UTextBlock* MyTextBoxThystame = Cast<UTextBlock>(WidgetInstance->GetWidgetFromName(TEXT("TextBlock_15")));
                                if (MyTextBoxThystame)
                                {
                                    FText NumberCaseText = FText::FromString(FString::Printf(TEXT("%d"), ThystameCount));
                                    MyTextBoxThystame->SetText(NumberCaseText);
                                }
                            }

                        }
                    }


                }
            }
        }
    }
}

void AMyServerConnection::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bIsConnected)
    {
        ReceiveData();
        if (WaitingFirstIa)
        {

            if (PosIaArray.Num() > 0 && TickInterval > 100)
            {
                int index_update_pos_ia = 0;

                for (const FPosIa& PosIa : PosIaArray)
                {
                    if (PosIaArray[index_update_pos_ia].nbIa > 0)
                    {
                        FString SendPpo = FString::Printf(TEXT("ppo %d\n"), PosIaArray[index_update_pos_ia].nbIa);

                        SendData(SendPpo);
                    }

                    index_update_pos_ia++;
                }

                TickInterval = 0;
            }
        }

        if (bAllDataReceived)
        {
            GenerateMap();

            bAllDataReceived = false;
            load = true;

            if (this->bShowText && load == true)
            {
                FString TextToDisplay = TEXT("CHARGEMENT...");
                FVector2D TextPosition2D(1000.0f, 1000.0f);

                FVector TextPosition(TextPosition2D.X, TextPosition2D.Y, 0.0f);
                FColor TextColor = FColor::Yellow;

                // Définir la durée en fonction de la taille de PosIaArray
                float MinDuration = 0.5f;
                float MaxDuration = 5.0f;
                float ArraySize = PosIaArray.Num();
                float Duration = FMath::Lerp(MinDuration, MaxDuration, ArraySize / 900.0f);

                // Augmenter la taille du texte en définissant une échelle (Scale) plus grande
                float TextScale = 2.0f;

                DrawDebugString(GetWorld(), TextPosition, TextToDisplay, nullptr, TextColor, Duration, false, TextScale);

                this->bShowText = false;
            }

            bAllDataReceived = false;
        }

        if (arrayIaisFull)
        {
            updateMap();
            arrayIaisFull = false;
        }

        if (move_perso_ppo)
        {
            updateMapMovable();
        }


        //click sur une case
        APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
        if (PlayerController)
        {
            FHitResult HitResult;
            PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

            if (HitResult.GetActor())
            {
                AMyActorCube* CubeActor = Cast<AMyActorCube>(HitResult.GetActor());
                if (CubeActor)
                {
                    CubeActor->SetHighlight(true);

                    // Vérifiez si le bouton gauche de la souris est enfoncé
                    if (PlayerController->WasInputKeyJustReleased(EKeys::LeftMouseButton))
                    {
                        if (bShowDetailCase)
                        {
                            WidgetInstance->RemoveFromViewport();
                            WidgetInstance = nullptr;
                        }

                        OnMouseClicked(CubeActor, EKeys::LeftMouseButton, PlayerController);
                        bShowDetailCase = true;
                    }

                    if (PlayerController->WasInputKeyJustReleased(EKeys::P))
                    {
                        if (WidgetInstance)
                        {
                            WidgetInstance->RemoveFromViewport();
                            WidgetInstance = nullptr;
                        }
                        bShowDetailCase = false;
                    }

                }
            }
        }
    }
}

void AMyServerConnection::OnMouseClickedOnIa(AActor* ClickedActor, FKey ButtonClicked, APlayerController* PlayerController)
{
}

void AMyServerConnection::ConnectToServer(const FString& ServerIP, int32 ServerPort)
{
    this->ISocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    this->Socket = this->ISocket->CreateSocket(NAME_Stream, TEXT("default"), false);
    TSharedRef<FInternetAddr> ServerAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
    bool bIsValid;
    ServerAddress->SetIp(*ServerIP, bIsValid);
    ServerAddress->SetPort(ServerPort);
    bool bConnected = Socket->Connect(*ServerAddress);

    if (bConnected)
    {
        UE_LOG(LogTemp, Warning, TEXT("Connexion réussie au serveur."));
        Socket->SetNonBlocking(true);
        if (loadMap == false) {
            SendData("GRAPHIC\n");
            loadMap = true;
        }
        bIsConnected = true;
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Échec de la connexion au serveur."));
        bIsConnected = false;
    }
}

uint32 AMyServerConnection::Run()
{
    while (bIsConnected == true)
    {
        if (bIsConnected)
        {
            ReceiveData();
        }
    }
    return 0;
}

void AMyServerConnection::Stop()
{
    if (Socket && Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected && this->bIsConnected)
    {
        Socket->Close();
        ISocket->DestroySocket(Socket);
        FPlatformProcess::Sleep(1.0f);
    }
}

void AMyServerConnection::Exit()
{
    bIsConnected = false;
    Stop();
}

void AMyServerConnection::SendData(const FString& DataToSend)
{
    if (Socket != nullptr && Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected && !DataToSend.IsEmpty())
    {
        TArray<uint8> SerializedData;
        FTCHARToUTF8 UTF8Converter(*DataToSend);
        SerializedData.Append((const uint8*)UTF8Converter.Get(), UTF8Converter.Length());

        int32 BytesSent = 0;
        int32 DataSize = SerializedData.Num();

        Socket->Send(SerializedData.GetData(), DataSize, BytesSent)
    }
}

void AMyServerConnection::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = true;
        PlayerController->bEnableClickEvents = true;
        PlayerController->bEnableMouseOverEvents = true;

        FInputModeGameAndUI InputMode;
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        InputMode.SetHideCursorDuringCapture(false);
        PlayerController->SetInputMode(InputMode);
    }
}

void AMyServerConnection::updateMapMovable()
{
    UWorld* World = GetWorld();

    if (World)
    {
        float DeltaTime = World->GetDeltaSeconds();
        float InterpSpeed = 5.0f;

        for (const FPosIa& PosIa : PosIaArray)
        {
            int32 x = PosIa.X;
            int32 y = PosIa.Y;

            if (x >= 0 && x <= sizeX && y >= 0 && y <= sizeY)
            {
                FVector TargetLocation(x * 350.0f, y * 350.0f, -50.0f);
                FRotator TargetRotation(0.0f, 0.0f, 0.0f);

                if (PosIa.Orien == 1)
                    TargetRotation.Yaw = 180.0f;
                else if (PosIa.Orien == 2)
                    TargetRotation.Yaw = 260.0f;
                else if (PosIa.Orien == 3)
                    TargetRotation.Yaw = 0.0f;
                else if (PosIa.Orien == 4)
                    TargetRotation.Yaw = 90.0f;

                if (PosIa.ActorIa)
                {
                    FVector CurrentLocation = PosIa.ActorIa->GetActorLocation();
                    FRotator CurrentRotation = PosIa.ActorIa->GetActorRotation();


                    FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, InterpSpeed);
                    FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, InterpSpeed);

                    PosIa.ActorIa->SetActorLocation(NewLocation);
                    PosIa.ActorIa->SetActorRotation(NewRotation);

                    WaitingFirstIa = true;
                }
            }
        }
    }
}


void AMyServerConnection::updateMap()
{
    UWorld* World = GetWorld();

    if (World)
    {
        for (const FPosIa& PosIa : PosIaArray)
        {
            int32 x = PosIa.X;
            int32 y = PosIa.Y;

            FVector Location(x * 350.0f, y * 350.0f, 0.0f);

            if (x >= 0 && x <= sizeX && y >= 0 && y <= sizeY)
            {
                float orientation = 0.0f;

                if (PosIa.Orien == 1)
                    orientation = 180.0f;
                else if (PosIa.Orien == 2)
                    orientation = 260.0f;
                else if (PosIa.Orien == 3)
                    orientation = 0.0f;
                else if (PosIa.Orien == 4)
                    orientation = 90.0f;


                FRotator Rotation(0.0f, orientation, 0.0f);

                FVector LocationBoule(x * 350.0f, y * 350.0f, 20.0f);
                FVector BallLocation = LocationBoule; // Ajouter un décalage vertical pour chaque boule

                // Vérifier si un acteur existe déjà à cette position
                TArray<AActor*> OverlappingActors;
                UGameplayStatics::GetAllActorsOfClass(World, AMyActorPersoIaPrinc::StaticClass(), OverlappingActors);

                bool bActorExists = false;
                for (AActor* Actor : OverlappingActors)
                {
                    if (Actor->GetActorLocation() == BallLocation)
                    {
                        bActorExists = true;
                        break;
                    }
                }

                if (!bActorExists)
                {
                    WaitingFirstIa = true;
                }
            }
        }
    }
}

void AMyServerConnection::GenerateMap()
{
    UWorld* World = GetWorld();
    FRandomStream RandomStream;

    UE_LOG(LogTemp, Warning, TEXT("test"));

    if (World)
    {
        for (int32 y = 0; y < sizeY; y++) {
            for (int32 x = 0; x < sizeX; x++) {
                FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                FVector Location(x * 350.0f, y * 350.0f, -100.0f);

                TArray<AActor*> OverlappingActors;
                UGameplayStatics::GetAllActorsOfClass(World, AMyActorPersoIaPrinc::StaticClass(), OverlappingActors);

                bool bActorExists = false;
                for (AActor* Actor : OverlappingActors)
                {
                    if (Actor->GetActorLocation() == Location)
                    {
                        bActorExists = true;
                        break;
                    }
                }

                if (bActorExists == false && IsConstruct == false)
                {
                    AMyActorCube* SpawnerCube = World->SpawnActor<AMyActorCube>(AMyActorCube::StaticClass(), Location, Rotation);

                    // Définir l'échelle souhaitée
                    FVector Scale(30.0f, 30.0f, 10.0f);
                    SpawnerCube->SetActorScale3D(Scale);
                }


                this->sizeloadx = sizeX;
                this->sizeloady = sizeY;

                this->Index = GetIndex(x, y);
                if (Index >= 0 && Index < MapData.Num())
                {
                    FMapCell& MapCell = MapData[Index];

                    for (int32 i = 0; i < MapCell.Food; i++)
                    {
                        FVector LocationBoule(x * 350.0f, y * 350.0f, -75.0f);
                        FVector BallLocation = LocationBoule; // Ajouter un décalage vertical pour chaque boule

                        MapData[Index].FoodActor = World->SpawnActor<AMyBurger>(AMyBurger::StaticClass(), BallLocation, Rotation);
                        FVector ScaleBoule(1.0f, 1.0f, 1.0f);
                        MapData[Index].FoodActor->SetActorScale3D(ScaleBoule);
                    }

                    for (int32 i = 0; i < MapCell.linemate; i++)
                    {
                        FVector LocationBoule(x * 340.0f, y * 340.0f, -50.0f);
                        FVector BallLocation = LocationBoule; // Ajouter un décalage vertical pour chaque boule

                        MapData[Index].linemateActor = World->SpawnActor<AMyLinemate>(AMyLinemate::StaticClass(), BallLocation, Rotation);
                        FVector ScaleBoule(15.0f, 15.0f, 15.0f);
                        MapData[Index].linemateActor->SetActorScale3D(ScaleBoule);
                    }

                    for (int32 i = 0; i < MapCell.deraumere; i++)
                    {
                        FVector LocationBoule(x * 350.0f, y * 358.0f, -50.0f);
                        FVector BallLocation = LocationBoule; // Ajouter un décalage vertical pour chaque boule

                        MapData[Index].deraumereActor = World->SpawnActor<AMyDeraumere>(AMyDeraumere::StaticClass(), BallLocation, Rotation);
                        FVector ScaleBoule(10.0f, 10.0f, 10.0f);
                        MapData[Index].deraumereActor->SetActorScale3D(ScaleBoule);
                    }

                    for (int32 i = 0; i < MapCell.sibur; i++)
                    {
                        FVector LocationBoule(x * 345.0f, y * 355.0f, -50.0f);
                        FVector BallLocation = LocationBoule; // Ajouter un décalage vertical pour chaque boule

                        MapData[Index].siburActor = World->SpawnActor<AMySibur>(AMySibur::StaticClass(), BallLocation, Rotation);
                        FVector ScaleBoule(13.0f, 13.0f, 13.0f);
                        MapData[Index].siburActor->SetActorScale3D(ScaleBoule);
                    }

                    for (int32 i = 0; i < MapCell.mendiane; i++)
                    {
                        FVector LocationBoule(x * 350.0f, y * 340.0f, -50.0f);
                        FVector BallLocation = LocationBoule; // Ajouter un décalage vertical pour chaque boule

                        MapData[Index].mendianeActor = World->SpawnActor<AMyMendiane>(AMyMendiane::StaticClass(), BallLocation, Rotation);
                        FVector ScaleBoule(20.0f, 16.0f, 16.0f);
                        MapData[Index].mendianeActor->SetActorScale3D(ScaleBoule);
                    }

                    for (int32 i = 0; i < MapCell.phiras; i++)
                    {
                        FVector LocationBoule(x * 360.0f, y * 345.0f, -50.0f);
                        FVector BallLocation = LocationBoule; // Ajouter un décalage vertical pour chaque boule

                        MapData[Index].phirasActor = World->SpawnActor<AMyPhiras>(AMyPhiras::StaticClass(), BallLocation, Rotation);
                        FVector ScaleBoule(12.0f, 12.0f, 12.0f);
                        MapData[Index].phirasActor->SetActorScale3D(ScaleBoule);
                    }

                    for (int32 i = 0; i < MapCell.thystame; i++)
                    {
                        FVector LocationBoule(x * 355.0f, y * 340.0f, -50.0f);
                        FVector BallLocation = LocationBoule; // Ajouter un décalage vertical pour chaque boule

                        MapData[Index].thystameActor = World->SpawnActor<AMyThystame>(AMyThystame::StaticClass(), BallLocation, Rotation);
                        FVector ScaleBoule(12.0f, 12.0f, 12.0f);
                        MapData[Index].thystameActor->SetActorScale3D(ScaleBoule);
                    }
                }
            }
        }

    }
    gen_map = true;
    IsConstruct = true;
    this->bMapDataFilled = true;
}

void AMyServerConnection::ReceiveData()
{
    if (Socket != nullptr && Socket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
    {
        uint32 BufferSize = 4096;
        TArray<uint8> TempReceivedData;
        TempReceivedData.SetNumUninitialized(BufferSize);
        int32 BytesRead = 0;

        if (Socket->Recv(TempReceivedData.GetData(), TempReceivedData.Num(), BytesRead))
        {
            this->DataCount = 0;
            this->bAllDataReceived = false;
            if (BytesRead > 0)
            {
                ReceivedData.Append(TempReceivedData.GetData(), BytesRead);

                FString ReceivedString = FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));
                int32 LineIndex = 0;

                bool bIsMszLine = false;
                FString MszValue1;
                FString MszValue2;
                bool bAllLinesProcessed = false;

                ReceivedData.Empty();

                while (LineIndex != INDEX_NONE)
                {
                    FString Line;
                    LineIndex = ReceivedString.Find(TEXT("\n"), ESearchCase::CaseSensitive, ESearchDir::FromStart, LineIndex);
                    if (LineIndex != INDEX_NONE)
                    {
                        Line = ReceivedString.Left(LineIndex);
                        ReceivedString.RemoveAt(0, LineIndex + 1);
                        LineIndex = 0;
                    }
                    else
                    {
                        Line = ReceivedString;
                        ReceivedString.Empty();
                    }

                    if (!Line.IsEmpty())
                    {
                        Line = Line.Replace(TEXT("\r"), TEXT("")); // Supprime les caractères de retour chariot "\r" s'ils sont présents
                    }

                    if (Line.StartsWith("msz"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true); // Divise la ligne en utilisant l'espace comme délimiteur

                        if (Values.Num() >= 3 && Values[1].IsNumeric() && Values[2].IsNumeric())
                        {
                            MszValue1 = Values[1];
                            MszValue2 = Values[2];
                            this->sizeX = FCString::Atoi(*MszValue1);
                            this->sizeY = FCString::Atoi(*MszValue2);

                            if (this->sizeX >= 10 && this->sizeY >= 10) {
                                MapData.Empty();
                                PosIaArray.Empty();
                                MapData.SetNum(sizeX * sizeY); // Réinitialise le tableau MapData avec la nouvelle taille
                            }
                        }
                    }

                    if (Line.StartsWith("bct"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true); // Divise la ligne en utilisant l'espace comme délimiteur

                        if (Values.Num() >= 10 && Values[0] == "bct")
                        {
                            int32 X = FCString::Atoi(*Values[1]);
                            int32 Y = FCString::Atoi(*Values[2]);
                            int32 Food = FCString::Atoi(*Values[3]);
                            int32 Linemate = FCString::Atoi(*Values[4]);
                            int32 Deraumere = FCString::Atoi(*Values[5]);
                            int32 Sibur = FCString::Atoi(*Values[6]);
                            int32 Mendiane = FCString::Atoi(*Values[7]);
                            int32 Phiras = FCString::Atoi(*Values[8]);
                            int32 Thystame = FCString::Atoi(*Values[9]);

                            this->Index = GetIndex(X, Y);

                            if (Index >= 0 && Index < MapData.Num())
                            {
                                FMapCell& MapCell = MapData[Index];
                                MapCell.Food = Food;
                                MapCell.linemate = Linemate;
                                MapCell.deraumere = Deraumere;
                                MapCell.sibur = Sibur;
                                MapCell.mendiane = Mendiane;
                                MapCell.phiras = Phiras;
                                MapCell.thystame = Thystame;

                                this->arrayisFull = true;
                            }

                            DataCount++;

                            if (DataCount < sizeX * sizeY)
                            {
                                bAllDataReceived = true;
                            }
                        }
                    }

                    if (Line.StartsWith("pnw"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true); // Divise la ligne en utilisant l'espace comme délimiteur

                        if (Values.Num() >= 7 && Values[0] == "pnw")
                        {
                            int32 nbIa = FCString::Atoi(*Values[1]);
                            int32 X = FCString::Atoi(*Values[2]);
                            int32 Y = FCString::Atoi(*Values[3]);
                            int32 Orien = FCString::Atoi(*Values[4]);
                            int32 Level = FCString::Atoi(*Values[5]);
                            FString TeamName = *Values[6];

                            // Créer un nouvel élément FPosIa
                            FPosIa NewPosIa;
                            NewPosIa.nbIa = nbIa;
                            NewPosIa.X = X;
                            NewPosIa.Y = Y;
                            NewPosIa.Orien = Orien;
                            NewPosIa.Level = Level;
                            NewPosIa.TeamName = TeamName;

                            // Ajouter le nouvel élément au TArray
                            PosIaArray.Add(NewPosIa);

                            int32 IndexTmp = PosIaArray.Num() - 1; // Index de la nouvelle case

                            FRotator Rotation(0.0f, 0.0f, 0.0f);
                            FVector LocationBoule(0.0f, 0.0f, -500.0f);
                            FVector BallLocation = LocationBoule; // Ajouter un décalage vertical pour chaque boule

                            PosIaArray[IndexTmp].ActorIa = GetWorld()->SpawnActor<AMyActorPersoIaPrinc>(AMyActorPersoIaPrinc::StaticClass(), BallLocation, Rotation);

                            FLinearColor TeamColor;


                            // Déterminez la couleur de l'équipe en fonction du nom de l'équipe
                            if (TeamName == nameFirstTeam)
                            {
                                TeamColor = FLinearColor::Red;
                            }
                            else if (TeamName == nameScdTeam)
                            {
                                TeamColor = FLinearColor::Blue;
                            }
                            else if (TeamName == nameThrstTeam)
                            {
                                TeamColor = FLinearColor::Green;
                            }
                            else if (TeamName == nameFrthTeam)
                            {
                                TeamColor = FLinearColor::Yellow;
                            }
                            else
                            {
                                TeamColor = FLinearColor::White;
                            }

                            PosIaArray[IndexTmp].ActorIa->SetTeamColor(TeamColor);

                            this->arrayIaisFull = true;
                        }
                    }


                    if (Line.StartsWith("ppo"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true); // Divise la ligne en utilisant l'espace comme délimiteur

                        int32 nbIaPpo = FCString::Atoi(*Values[1]);
                        int32 X = FCString::Atoi(*Values[2]);
                        int32 Y = FCString::Atoi(*Values[3]);
                        int32 Orien = FCString::Atoi(*Values[4]);

                        int32 index_update_ppo = 0;

                        for (const FPosIa& PosIa : PosIaArray)
                        {

                            if (PosIaArray[index_update_ppo].nbIa == nbIaPpo)
                            {
                                if (PosIaArray[index_update_ppo].X != X || PosIaArray[index_update_ppo].Y != Y)
                                {
                                    //PosIa.ActorIa->PlayAnimation("Jump");
                                }
                                else {
                                    if (PosIa.ActorIa->checkIsPlaying() == false) {
                                        PosIa.ActorIa->PlayAnimation("idle");
                                    }
                                }

                                PosIaArray[index_update_ppo].X = X;
                                PosIaArray[index_update_ppo].Y = Y;
                                PosIaArray[index_update_ppo].Orien = Orien;
                            }

                            index_update_ppo++;
                        }
                        move_perso_ppo = true;
                    }

                    if (Line.StartsWith("pdi"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true); // Divise la ligne en utilisant l'espace comme délimiteur

                        int32 nbIaPdi = FCString::Atoi(*Values[1]);

                        int32 index_mort_pdi = 0;

                        for (const FPosIa& PosIa : PosIaArray)
                        {
                            if (PosIaArray[index_mort_pdi].nbIa == nbIaPdi)
                            {
                                int32 menos = -2;

                                PosIaArray[index_mort_pdi].X = menos;
                                PosIaArray[index_mort_pdi].Y = menos;
                                PosIaArray[index_mort_pdi].Orien = menos;

                                PosIaArray[index_mort_pdi].ActorIa->PlayAnimation("Die");
                                PosIaArray[index_mort_pdi].ActorIa->SetLightIntensity(0.0f);

                                PosIa.ActorIa->Destroy();


                            }

                            index_mort_pdi++;
                        }
                        move_perso_ppo = true;
                    }

                    if (Line.StartsWith("tna"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true); // Divise la ligne en utilisant l'espace comme délimiteur

                        FString teamName = *Values[1];

                        if (nameFirstTeam == "")
                        {
                            nameFirstTeam = teamName;
                        }
                        else if (nameScdTeam == "")
                        {
                            nameScdTeam = teamName;
                        }
                        else if (nameThrstTeam == "")
                        {
                            nameThrstTeam = teamName;
                        }
                        else if (nameFrthTeam == "")
                        {
                            nameFrthTeam = teamName;
                        }
                        else if (nameFvthTeam == "")
                        {
                            nameFvthTeam = teamName;
                        }
                    }


                    if (Line.StartsWith("pfk"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true); // Divise la ligne en utilisant l'espace comme délimiteur

                        int32 nbIaPdi = FCString::Atoi(*Values[1]);

                        int32 index_pfk = 0;

                        for (const FPosIa& PosIa : PosIaArray)
                        {
                            if (PosIaArray[index_pfk].nbIa == nbIaPdi)
                            {
                                PosIa.ActorIa->PlayAnimation("Twerk");
                            }

                            index_pfk++;
                        }
                        move_perso_ppo = true;
                    }

                    if (Line.StartsWith("ebo"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true); // Divise la ligne en utilisant l'espace comme délimiteur

                        int32 eggNumber = FCString::Atoi(*Values[1]);

                        int32 index_ebo = 0;
                        move_perso_ppo = true;
                    }

                    if (Line.StartsWith("enw"))
                    {
                        UWorld* World = GetWorld();
                        FRandomStream RandomStream;

                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true);

                        int32 nboeuf = FCString::Atoi(*Values[1]);
                        int32 nbIaPdi = FCString::Atoi(*Values[2]);
                        int32 X = FCString::Atoi(*Values[3]);
                        int32 Y = FCString::Atoi(*Values[4]);

                        int32 index_ewn = 0;

                        for (const FPosIa& PosIa : PosIaArray)
                        {
                            if (PosIaArray[index_ewn].nbIa == nbIaPdi)
                            {
                                PosIa.ActorIa->PlayAnimation("idle");
                            }

                            index_ewn++;
                        }

                        int32 index_ewn_sec = 0;

                        move_perso_ppo = true;
                    }



                    if (Line.StartsWith("pgt"))
                    {
                        UWorld* World = GetWorld();
                        FRandomStream RandomStream;

                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true); // Divise la ligne en utilisant l'espace comme délimiteur

                        int32 nbIaPdi = FCString::Atoi(*Values[1]);
                        int32 ressource = FCString::Atoi(*Values[2]);

                        int32 x = 0;
                        int32 y = 0;

                        int32 index_pgt_first = 0;

                        for (const FPosIa& PosIa : PosIaArray)
                        {
                            if (PosIaArray[index_pgt_first].nbIa == nbIaPdi)
                            {
                                PosIa.ActorIa->PlayAnimation("Pickup");
                                x = PosIa.X;
                                y = PosIa.Y;
                            }
                            index_pgt_first++;
                        }

                        int32 index_pgt_sec = 0;

                        for (const FMapCell& MapCell : MapData)
                        {
                            int32 getindex = GetIndex(x, y);

                            if ((index_pgt_sec == getindex) && ressource == 0)
                            {
                                if (MapData[index_pgt_sec].Food > 0)
                                {
                                    MapData[index_pgt_sec].Food -= 1;

                                    if (MapData[index_pgt_sec].Food == 0) {
                                        FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                        FVector LocationBoule(x * RandomStream.FRandRange(340.0f, 360.0f), y * RandomStream.FRandRange(340.0f, 360.0f), -500.0f);
                                        FVector BallLocation = LocationBoule;
                                        MapData[index_pgt_sec].FoodActor->Destroy();
                                    }
                                }
                            }

                            if ((index_pgt_sec == getindex) && ressource == 1)
                            {
                                if (MapData[index_pgt_sec].linemate > 0)
                                {
                                    MapData[index_pgt_sec].linemate -= 1;


                                    if (MapData[index_pgt_sec].linemate == 0) {
                                        FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                         FVector LocationBoule(x* RandomStream.FRandRange(340.0f, 360.0f), y* RandomStream.FRandRange(340.0f, 360.0f), -500.0f);
                                         FVector BallLocation = LocationBoule;
                                         MapData[index_pgt_sec].linemateActor->Destroy();
                                    }
                                }
                            }

                            if ((index_pgt_sec == getindex) && ressource == 2)
                            {

                                if (MapData[index_pgt_sec].deraumere > 0)
                                {
                                    MapData[index_pgt_sec].deraumere -= 1;
                                    
                                    if (MapData[index_pgt_sec].deraumere == 0) {
                                        FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                        FVector LocationBoule(x * RandomStream.FRandRange(340.0f, 360.0f), y * RandomStream.FRandRange(340.0f, 360.0f), -500.0f);
                                        FVector BallLocation = LocationBoule;
                                        MapData[index_pgt_sec].deraumereActor->Destroy();
                                    }
                                }
                            }

                            if ((index_pgt_sec == getindex) && ressource == 3)
                            {
                                if (MapData[index_pgt_sec].sibur > 0)
                                {
                                    MapData[index_pgt_sec].sibur -= 1;

                                    if (MapData[index_pgt_sec].sibur == 0) {
                                        FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                        FVector LocationBoule(x * RandomStream.FRandRange(340.0f, 360.0f), y * RandomStream.FRandRange(340.0f, 360.0f), -500.0f);
                                        FVector BallLocation = LocationBoule;
                                        MapData[index_pgt_sec].siburActor->Destroy();
                                    }
                                };
                            }

                            if ((index_pgt_sec == getindex) && ressource == 4)
                            {

                                if (MapData[index_pgt_sec].mendiane > 0)
                                {
                                    MapData[index_pgt_sec].mendiane -= 1;
                                    
                                    if (MapData[index_pgt_sec].mendiane == 0) {
                                        FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                        FVector LocationBoule(x * RandomStream.FRandRange(340.0f, 360.0f), y * RandomStream.FRandRange(340.0f, 360.0f), -500.0f);
                                        FVector BallLocation = LocationBoule;
                                        MapData[index_pgt_sec].mendianeActor->Destroy();
                                    }
                                }

                            }

                            if ((index_pgt_sec == getindex) && ressource == 5)
                            {
                                if (MapData[index_pgt_sec].phiras > 0)
                                {
                                    MapData[index_pgt_sec].phiras -= 1;

                                    if (MapData[index_pgt_sec].phiras == 0) {
                                         FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                         FVector LocationBoule(x* RandomStream.FRandRange(340.0f, 360.0f), y* RandomStream.FRandRange(340.0f, 360.0f), -500.0f);
                                         FVector BallLocation = LocationBoule;
                                         MapData[index_pgt_sec].phirasActor->Destroy();
                                    }
                                }

                            }

                            if ((index_pgt_sec == getindex) && ressource == 6)
                            {
                                if (MapData[index_pgt_sec].phiras > 0)
                                {
                                    MapData[index_pgt_sec].thystame -= 1;
                                    
                                    if (MapData[index_pgt_sec].thystame == 0) {
                                        FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                        FVector LocationBoule(x* RandomStream.FRandRange(340.0f, 360.0f), y* RandomStream.FRandRange(340.0f, 360.0f), -500.0f);
                                        FVector BallLocation = LocationBoule;
                                        MapData[index_pgt_sec].thystameActor->Destroy();
                                    }
                                }

                            }
                            index_pgt_sec++;
                        }

                        move_perso_ppo = true;
                    }

                    if (Line.StartsWith("pdr"))
                    {
                        UWorld* World = GetWorld();
                        FRandomStream RandomStream;

                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true); // Divise la ligne en utilisant l'espace comme délimiteur

                        int32 nbIaPdi = FCString::Atoi(*Values[1]);
                        int32 ressource = FCString::Atoi(*Values[2]);

                        int32 x = 0;
                        int32 y = 0;

                        int32 index_pdr_first = 0;

                        for (const FPosIa& PosIa : PosIaArray)
                        {
                            if (PosIaArray[index_pdr_first].nbIa == nbIaPdi)
                            {
                                x = PosIa.X;
                                y = PosIa.Y;
                            }
                            index_pdr_first++;
                        }

                        int32 index_pdr_sec = 0;

                        for (const FMapCell& MapCell : MapData)
                        {
                            int32 getindex = GetIndex(x, y);

                            if ((index_pdr_sec == getindex) && ressource == 0)
                            {
                                MapData[index_pdr_sec].Food += 1;

                                if (MapData[index_pdr_sec].Food == 1) {
                                    FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                    FVector LocationBoule(x * RandomStream.FRandRange(340.0f, 360.0f), y * RandomStream.FRandRange(340.0f, 360.0f), 0.0f);
                                    FVector BallLocation = LocationBoule;

                                    MapData[index_pdr_sec].FoodActor = World->SpawnActor<AMyBurger>(AMyBurger::StaticClass(), BallLocation, Rotation);
                                    FVector ScaleBoule(1.0f, 1.0f, 1.0f);
                                    MapData[index_pdr_sec].FoodActor->SetActorScale3D(ScaleBoule);
                                }
                            }

                            if ((index_pdr_sec == getindex) && ressource == 1)
                            {
                                MapData[index_pdr_sec].linemate += 1;

                                if (MapData[index_pdr_sec].linemate == 1) {
                                    FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                    FVector LocationBoule(x * RandomStream.FRandRange(340.0f, 360.0f), y * RandomStream.FRandRange(340.0f, 360.0f), 0.0f);
                                    FVector BallLocation = LocationBoule;

                                    MapData[index_pdr_sec].linemateActor = World->SpawnActor<AMyLinemate>(AMyLinemate::StaticClass(), BallLocation, Rotation);
                                    FVector ScaleBoule(1.0f, 1.0f, 1.0f);
                                    MapData[index_pdr_sec].linemateActor->SetActorScale3D(ScaleBoule);
                                }
                            }

                            if ((index_pdr_sec == getindex) && ressource == 2)
                            {
                                MapData[index_pdr_sec].deraumere += 1;

                                if (MapData[index_pdr_sec].deraumere == 1) {
                                    FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                    FVector LocationBoule(x * RandomStream.FRandRange(340.0f, 360.0f), y * RandomStream.FRandRange(340.0f, 360.0f), 0.0f);
                                    FVector BallLocation = LocationBoule;

                                    MapData[index_pdr_sec].deraumereActor = World->SpawnActor<AMyDeraumere>(AMyDeraumere::StaticClass(), BallLocation, Rotation);
                                    FVector ScaleBoule(1.0f, 1.0f, 1.0f);
                                    MapData[index_pdr_sec].deraumereActor->SetActorScale3D(ScaleBoule);
                                }
                            }

                            if ((index_pdr_sec == getindex) && ressource == 3)
                            {
                                MapData[index_pdr_sec].sibur += 1;

                                if (MapData[index_pdr_sec].sibur == 1) {
                                    FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                    FVector LocationBoule(x * RandomStream.FRandRange(340.0f, 360.0f), y * RandomStream.FRandRange(340.0f, 360.0f), 0.0f);
                                    FVector BallLocation = LocationBoule;

                                    MapData[index_pdr_sec].siburActor = World->SpawnActor<AMySibur>(AMySibur::StaticClass(), BallLocation, Rotation);
                                    FVector ScaleBoule(1.0f, 1.0f, 1.0f);
                                    MapData[index_pdr_sec].siburActor->SetActorScale3D(ScaleBoule);
                                }
                            }

                            if ((index_pdr_sec == getindex) && ressource == 4)
                            {
                                MapData[index_pdr_sec].mendiane += 1;

                                if (MapData[index_pdr_sec].mendiane == 1) {
                                    FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                    FVector LocationBoule(x * RandomStream.FRandRange(340.0f, 360.0f), y * RandomStream.FRandRange(340.0f, 360.0f), 0.0f);
                                    FVector BallLocation = LocationBoule;

                                    MapData[index_pdr_sec].mendianeActor = World->SpawnActor<AMyMendiane>(AMyMendiane::StaticClass(), BallLocation, Rotation);
                                    FVector ScaleBoule(1.0f, 1.0f, 1.0f);
                                    MapData[index_pdr_sec].mendianeActor->SetActorScale3D(ScaleBoule);
                                }
                            }

                            if ((index_pdr_sec == getindex) && ressource == 5)
                            {
                                MapData[index_pdr_sec].phiras += 1;

                                if (MapData[index_pdr_sec].phiras == 1) {
                                     FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                     FVector LocationBoule(x * RandomStream.FRandRange(340.0f, 360.0f), y * RandomStream.FRandRange(340.0f, 360.0f), 0.0f);
                                     FVector BallLocation = LocationBoule;

                                     MapData[index_pdr_sec].phirasActor = World->SpawnActor<AMyPhiras>(AMyPhiras::StaticClass(), BallLocation, Rotation);
                                     FVector ScaleBoule(1.0f, 1.0f, 1.0f);
                                     MapData[index_pdr_sec].phirasActor->SetActorScale3D(ScaleBoule);
                                }
                            }

                            if ((index_pdr_sec == getindex) && ressource == 6)
                            {
                                MapData[index_pdr_sec].thystame += 1;

                                if (MapData[index_pdr_sec].thystame == 1) {
                                    FRotator Rotation(0.0f, RandomStream.FRandRange(0.0f, 360.0f), 0.0f);
                                    FVector LocationBoule(x * RandomStream.FRandRange(340.0f, 360.0f), y * RandomStream.FRandRange(340.0f, 360.0f), 0.0f);
                                    FVector BallLocation = LocationBoule;

                                    MapData[index_pdr_sec].thystameActor = World->SpawnActor<AMyThystame>(AMyThystame::StaticClass(), BallLocation, Rotation);
                                    FVector ScaleBoule(1.0f, 1.0f, 1.0f);
                                    MapData[index_pdr_sec].thystameActor->SetActorScale3D(ScaleBoule);
                                }
                            }

                            index_pdr_sec++;
                        }

                        move_perso_ppo = true;
                    }

                    if (Line.StartsWith("smg"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true);

                        FString msg = *Values[1];

                        if (msg == "NUCLEAR")
                        {
                            FRotator Rotation(0.0f, 0.0f, 0.0f);


                            int32 nukeX = ((sizeloadx) * 350) / 2;
                            int32 nukeY = ((sizeloady) * 350) / 2;

                            FVector LocationBoule(nukeX, nukeY, -100.0f);

                            FVector BallLocation = LocationBoule;

                            AMySetNuclear* nuke = GetWorld()->SpawnActor<AMySetNuclear>(AMySetNuclear::StaticClass(), BallLocation, Rotation);

                            FVector ScaleBoule(10.0f, 10.0f, 10.0f);
                            nuke->SetActorScale3D(ScaleBoule);
                        }
                       
                        move_perso_ppo = true;
                    }

                    if (Line.StartsWith("pex"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true);

                        int32 nbIaPdi = FCString::Atoi(*Values[1]);

                        int32 index_pex = 0;

                        for (const FPosIa& PosIa : PosIaArray)
                        {
                            if (PosIaArray[index_pex].nbIa == nbIaPdi)
                            {
                                PosIa.ActorIa->PlayAnimation("Kick");

                                if (PosIa.ActorIa->checkIsPlaying() == false) {
                                    PosIa.ActorIa->PlayAnimation("idle");
                                }
                            }

                            index_pex++;
                        }
                        move_perso_ppo = true;
                    }

                    if (Line.StartsWith("pic"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true);

                        int32 X = FCString::Atoi(*Values[1]);
                        int32 Y = FCString::Atoi(*Values[2]);
                        int32 Level = FCString::Atoi(*Values[3]);
                        TArray<int32> NValues;

                        for (int32 IndexForInc = 4; IndexForInc < Values.Num(); IndexForInc++)
                        {
                            int32 N = FCString::Atoi(*Values[IndexForInc]);
                            NValues.Add(N);
                        }

                        int32 index_pic = 0;

                        for (int32 N : NValues)
                        {
                            for (const FPosIa& PosIa : PosIaArray)
                            {
                                if (PosIaArray[index_pic].nbIa == N)
                                {
                                    PosIa.ActorIa->PlayAnimation("dance");

                                    if (PosIa.ActorIa->checkIsPlaying() == false) {
                                        PosIa.ActorIa->PlayAnimation("idle");
                                    }
                                }

                                index_pic++;
                            }
                        }

                        move_perso_ppo = true;
                    }

                    if (Line.StartsWith("pie"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true);

                        int32 X = FCString::Atoi(*Values[1]);
                        int32 Y = FCString::Atoi(*Values[2]);
                        FString res = *Values[3];

                        int32 index_pie = 0;

                        for (const FPosIa& PosIa : PosIaArray)
                        {
                            if (PosIaArray[index_pie].X == X && PosIaArray[index_pie].Y == Y)
                            {
                                PosIa.ActorIa->PlayAnimation("idle");
                            }
                            index_pie++;
                        }


                        move_perso_ppo = true;
                    }


                    if (Line.StartsWith("pbc"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true);

                        int32 nbIaPdi = FCString::Atoi(*Values[1]);
                        FString msg = Line.Mid(Values[0].Len() + Values[1].Len() + 2);

                        int32 index_pbc = 0;

                        for (const FPosIa& PosIa : PosIaArray)
                        {
                            if (PosIaArray[index_pbc].nbIa == nbIaPdi)
                            {
                                PosIa.ActorIa->PlayAnimation("Broad");

                                UAudioComponent* BroadcastSound = NewObject<UAudioComponent>(PosIa.ActorIa);
                                BroadcastSound->AttachToComponent(PosIa.ActorIa->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

                                USoundBase* SoundToPlay = LoadObject<USoundBase>(nullptr, TEXT("/Game/UI/son.son"));
                                if (SoundToPlay)
                                {
                                    BroadcastSound->SetSound(SoundToPlay);
                                    BroadcastSound->Play();
                                    BroadcastSound->SetVolumeMultiplier(0.8f);
                                }

                                FString TextToDisplay = FString::Printf(TEXT("%s"), *msg);
                                FVector2D TextPosition2D(-2500.0f, 0.0f);

                                FVector TextPosition = PosIa.ActorIa->GetActorLocation();
                                FColor TextColor = FColor::Yellow;

                                // Augmenter la taille du texte en définissant une échelle (Scale) plus grande
                                float TextScale = 1.5f;

                                DrawDebugString(GetWorld(), TextPosition, TextToDisplay, nullptr, TextColor, 3.0f, false, TextScale);

                                if (PosIa.ActorIa->checkIsPlaying() == false) {
                                    PosIa.ActorIa->PlayAnimation("idle");
                                }
                            }

                            index_pbc++;
                        }
                        move_perso_ppo = true;
                    }

                    if (Line.StartsWith("seg"))
                    {
                        TArray<FString> Values;
                        Line.ParseIntoArray(Values, TEXT(" "), true);

                        FString teamName = Values[1];

                        FString TextToDisplay = FString::Printf(TEXT("VICTOIRE DE LA %s"), *teamName);
                        FVector2D TextPosition2D(0.0f, 0.0f);

                        FVector TextPosition = FVector::ZeroVector;
                        FColor TextColor = FColor::White;

                        float TextScale = 3.0f;

                        if (WidgetInstanceVictoire == nullptr)
                        {
                            APlayerController* PlayerControllerUI = UGameplayStatics::GetPlayerController(GetWorld(), 0);

                            if (PlayerControllerUI)
                            {
                                WidgetInstanceVictoire = CreateWidget<UUserWidget>(PlayerControllerUI, WidgetTemplateVictoire);

                                if (WidgetInstanceVictoire)
                                {
                                    WidgetInstanceVictoire->AddToViewport();

                                    UTextBlock* MyTextBoxCase = Cast<UTextBlock>(WidgetInstanceVictoire->GetWidgetFromName(TEXT("TextBlock_1")));
                                    if (MyTextBoxCase)
                                    {
                                        FText NumberCaseText = FText::FromString(FString::Printf(TEXT("%s"), *teamName));
                                        MyTextBoxCase->SetText(NumberCaseText);
                                    }
                                }
                            }
                        }
                    }

                    if (ReceivedString.IsEmpty())
                    {
                        bAllLinesProcessed = true;
                    }
                }
                ReceivedData.Empty();
            }
        }
    }
}

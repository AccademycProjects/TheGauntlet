// Fill out your copyright notice in the Description page of Project Settings.


#include "_TheGauntlet/Core/GauntletGameMode.h"
#include "_TheGauntlet/Core/GauntletGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AGauntletGameMode::BeginPlay()
{
    Super::BeginPlay();

    // Detect if we're in main menu or gameplay based on map name
    const FString MapName = GetWorld()->GetMapName();
    
    if (UGauntletGameInstance* GI = GetGameInstance<UGauntletGameInstance>())
    {
        if (MapName.Contains(TEXT("MainMenu")))
        {
            GI->SetGameState(EGauntletGameState::InMainMenu);
        }
        else
        {
            GI->SetGameState(EGauntletGameState::InPlay);
        }
    }
}

void AGauntletGameMode::CompleteLevel()
{
    // Broadcast event so UI, GameInstance, etc. can react
    OnLevelCompleted.Broadcast();

    // Here you can add logic for win, like disabling input, starting a timer, etc.
}

void AGauntletGameMode::FailLevel()
{
    // Logic for lose, e.g., restart level, show lose UI, etc.
}

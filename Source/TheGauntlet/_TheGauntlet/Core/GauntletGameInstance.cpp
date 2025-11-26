// Fill out your copyright notice in the Description page of Project Settings.


#include "_TheGauntlet/Core/GauntletGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#pragma region Level Management

void UGauntletGameInstance::LoadMainMenu()
{
    SetGameState(EGauntletGameState::InLoading);
    UGameplayStatics::OpenLevel(this, FName("MainMenu"));
}

void UGauntletGameInstance::LoadLevel(FName LevelName)
{
    SetGameState(EGauntletGameState::InLoading);
    UGameplayStatics::OpenLevel(this, LevelName);
}

void UGauntletGameInstance::QuitGame()
{
    UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}

#pragma endregion

#pragma region Game State

void UGauntletGameInstance::SetGameState(EGauntletGameState NewState)
{
    if (CurrentGameState != NewState)
    {
        CurrentGameState = NewState;
        OnGameStateChanged.Broadcast(NewState);
    }
}

#pragma endregion

#pragma region Input Device

void UGauntletGameInstance::SetInputDevice(EGauntletInputDevice NewDevice)
{
    if (CurrentInputDevice != NewDevice)
    {
        CurrentInputDevice = NewDevice;
        OnInputDeviceChanged.Broadcast(NewDevice);
    }
}

#pragma endregion


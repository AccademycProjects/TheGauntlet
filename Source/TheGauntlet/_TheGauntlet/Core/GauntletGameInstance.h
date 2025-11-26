// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GauntletGameInstance.generated.h"

/** Enum representing the current game state */
UENUM(BlueprintType)
enum class EGauntletGameState : uint8
{
    InMainMenu,
    InPlay,
    InPause,
    InLoading,
    InSaving
};

/** Enum representing the current input device */
UENUM(BlueprintType)
enum class EGauntletInputDevice : uint8
{
    MouseKeyboard,
    Gamepad
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, EGauntletGameState, NewState);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputDeviceChanged, EGauntletInputDevice, NewDevice);

/**
 * Main GameInstance class. Stores persistent data and the current game state.
 */
UCLASS()
class THEGAUNTLET_API UGauntletGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    // Loads the Main Menu level
    UFUNCTION(BlueprintCallable)
    void LoadMainMenu();

    // Loads a specific level by name
    UFUNCTION(BlueprintCallable)
    void LoadLevel(FName LevelName);

    // Quits the game application
    UFUNCTION(BlueprintCallable)
    void QuitGame();

    // Returns current game state
    UFUNCTION(BlueprintCallable, Category = "Game State")
    EGauntletGameState GetGameState() const { return CurrentGameState; }

    // Sets the current game state and broadcasts the change
    UFUNCTION(BlueprintCallable, Category = "Game State")
    void SetGameState(EGauntletGameState NewState);

    // Delegate broadcast when game state changes
    UPROPERTY(BlueprintAssignable, Category = "Game State")
    FOnGameStateChanged OnGameStateChanged;

    // Returns current input device
    UFUNCTION(BlueprintCallable, Category = "Input")
    EGauntletInputDevice GetInputDevice() const { return CurrentInputDevice; }

    // Sets the current input device and broadcasts the change
    UFUNCTION(BlueprintCallable, Category = "Input")
    void SetInputDevice(EGauntletInputDevice NewDevice);

    // Delegate broadcast when input device changes
    UPROPERTY(BlueprintAssignable, Category = "Input")
    FOnInputDeviceChanged OnInputDeviceChanged;

protected:
    UPROPERTY(BlueprintReadOnly, Category = "Game State")
    EGauntletGameState CurrentGameState = EGauntletGameState::InMainMenu;

    UPROPERTY(BlueprintReadOnly, Category = "Input")
    EGauntletInputDevice CurrentInputDevice = EGauntletInputDevice::MouseKeyboard;
};

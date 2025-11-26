// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GauntletGameInstance.h"
#include "GauntletPlayerController.generated.h"

/**
 * Unified PlayerController for both MainMenu and Gameplay.
 * Handles cursor visibility and input mode based on game state.
 */
UCLASS()
class THEGAUNTLET_API AGauntletPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:
	/** Called when game state changes (menu, play, pause, etc.) */
	UFUNCTION()
	void OnGameStateChanged(EGauntletGameState NewState);

	/** Called when input device changes (mouse/keyboard or gamepad) */
	UFUNCTION()
	void OnInputDeviceChanged(EGauntletInputDevice NewDevice);

	/** Updates cursor visibility and input mode based on current state and device */
	void UpdateCursorState();
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/Core/GauntletPlayerController.h"

void AGauntletPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UGauntletGameInstance* GI = GetGameInstance<UGauntletGameInstance>())
	{
		// Bind to game state and input device changes
		GI->OnGameStateChanged.AddDynamic(this, &AGauntletPlayerController::OnGameStateChanged);
		GI->OnInputDeviceChanged.AddDynamic(this, &AGauntletPlayerController::OnInputDeviceChanged);
		
		// Apply current state immediately
		UpdateCursorState();
	}
}

void AGauntletPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UGauntletGameInstance* GI = GetGameInstance<UGauntletGameInstance>())
	{
		GI->OnGameStateChanged.RemoveDynamic(this, &AGauntletPlayerController::OnGameStateChanged);
		GI->OnInputDeviceChanged.RemoveDynamic(this, &AGauntletPlayerController::OnInputDeviceChanged);
	}

	Super::EndPlay(EndPlayReason);
}

void AGauntletPlayerController::OnGameStateChanged(EGauntletGameState NewState)
{
	UpdateCursorState();
}

void AGauntletPlayerController::OnInputDeviceChanged(EGauntletInputDevice NewDevice)
{
	UpdateCursorState();
}

void AGauntletPlayerController::UpdateCursorState()
{
	UGauntletGameInstance* GI = GetGameInstance<UGauntletGameInstance>();
	if (!GI) return;

	const EGauntletGameState State = GI->GetGameState();
	const bool bUsingMouseKeyboard = (GI->GetInputDevice() == EGauntletInputDevice::MouseKeyboard);

	switch (State)
	{
	case EGauntletGameState::InMainMenu:
	case EGauntletGameState::InPause:
		// Show cursor only if using mouse & keyboard
		bShowMouseCursor = bUsingMouseKeyboard;
		SetInputMode(FInputModeUIOnly());
		break;

	case EGauntletGameState::InPlay:
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		break;

	case EGauntletGameState::InLoading:
	case EGauntletGameState::InSaving:
		// Keep current state during loading/saving
		break;
	}
}


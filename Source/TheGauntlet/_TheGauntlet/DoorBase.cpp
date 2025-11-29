// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/DoorBase.h"
#include "_TheGauntlet/Core/GauntletCharacter.h"
#include "Components/SceneComponent.h"

ADoorBase::ADoorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
}

void ADoorBase::BeginPlay()
{
	Super::BeginPlay();
}

void ADoorBase::Interact_Implementation(AGauntletCharacter* Interactor)
{
	if (!Interactor) return;

	// Check if interaction is allowed (base class handles requirement checking)
	if (!IInteractable::Execute_CanInteract(this, Interactor))
	{
		return;
	}

	ToggleDoor();
}

void ADoorBase::OpenDoor()
{
	if (bIsOpen) return;

	bIsOpen = true;
	OnDoorOpened();
}

void ADoorBase::CloseDoor()
{
	if (!bIsOpen) return;

	bIsOpen = false;
	OnDoorClosed();
}

void ADoorBase::ToggleDoor()
{
	if (bIsOpen)
	{
		CloseDoor();
	}
	else
	{
		OpenDoor();
	}
}

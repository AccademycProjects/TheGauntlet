// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/Obstacles/GauntletDoor.h"
#include "_TheGauntlet/Core/GauntletCharacter.h"
#include "Components/StaticMeshComponent.h"

AGauntletDoor::AGauntletDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
}

void AGauntletDoor::BeginPlay()
{
	Super::BeginPlay();
}

void AGauntletDoor::Interact_Implementation(AGauntletCharacter* Interactor)
{
	if (!Interactor) return;

	// Check if key is required and player has it
	if (RequiredKeyID != NAME_None && !Interactor->HasKey(RequiredKeyID))
	{
		// Player doesn't have the key - could play a "locked" sound/effect here
		return;
	}

	// Toggle door state
	bIsOpen = !bIsOpen;

	// Call Blueprint event for animation
	if (bIsOpen)
	{
		OnDoorOpen();
	}
	else
	{
		OnDoorClose();
	}
}

bool AGauntletDoor::CanInteract_Implementation(AGauntletCharacter* Interactor) const
{
	if (!Interactor) return false;

	// Can interact if: no key required OR player has the required key
	if (RequiredKeyID == NAME_None)
	{
		return true;
	}

	return Interactor->HasKey(RequiredKeyID);
}


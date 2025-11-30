// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/DoorReq_Key.h"
#include "_TheGauntlet/Core/GauntletCharacter.h"

UDoorReq_Key::UDoorReq_Key()
{
}

bool UDoorReq_Key::CheckRequirement_Implementation(AGauntletCharacter* Interactor)
{
	if (!Interactor) return false;

	// If no key required, always pass
	if (RequiredKeyID == NAME_None)
	{
		return true;
	}

	// Check if player has the required key
	return Interactor->HasKey(RequiredKeyID);
}


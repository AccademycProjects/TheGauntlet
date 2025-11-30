// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/ToggleComponent.h"
#include "_TheGauntlet/InteractableActor.h"
#include "_TheGauntlet/Interfaces/Interactable.h"
#include "_TheGauntlet/Core/GauntletCharacter.h"

UToggleComponent::UToggleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UToggleComponent::PerformActivation_Implementation(AGauntletCharacter* Interactor)
{
	if (!Interactor) return;

	// Toggle state
	bIsOn = !bIsOn;

	// Call appropriate event
	if (bIsOn)
	{
		OnToggleOn();
		OnToggleOnDelegate.Broadcast(this);
	}
	else
	{
		OnToggleOff();
		OnToggleOffDelegate.Broadcast(this);
	}

	// Call SystemInteract on target actor
	if (TargetActor && TargetActor->Implements<UInteractable>())
	{
		IInteractable::Execute_SystemInteract(TargetActor, Interactor);
	}
}

void UToggleComponent::OnToggleOn_Implementation()
{
    // Stub
}

void UToggleComponent::OnToggleOff_Implementation()
{
    // Stub
}

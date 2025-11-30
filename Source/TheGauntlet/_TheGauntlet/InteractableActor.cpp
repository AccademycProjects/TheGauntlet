// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/InteractableActor.h"
#include "_TheGauntlet/Core/GauntletCharacter.h"
#include "_TheGauntlet/RequirementComponent.h"

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();

	// Find all requirement components
	GetComponents<URequirementComponent>(RequirementComponents);
}

void AInteractableActor::Interact_Implementation(AGauntletCharacter* Interactor)
{
	// Base implementation does nothing
	// Override in derived classes
}

bool AInteractableActor::CanInteract_Implementation(AGauntletCharacter* Interactor) const
{
	if (!Interactor) return false;

	// Check all requirement components
	for (URequirementComponent* Requirement : RequirementComponents)
	{
		if (!IsValid(Requirement))
			continue;

		if (!Requirement->CheckRequirement(Interactor))
			return false;
	}

	return true;
}

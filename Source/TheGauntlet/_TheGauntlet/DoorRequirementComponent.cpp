// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/DoorRequirementComponent.h"
#include "_TheGauntlet/Core/GauntletCharacter.h"

UDoorRequirementComponent::UDoorRequirementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDoorRequirementComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UDoorRequirementComponent::CheckRequirement_Implementation(AGauntletCharacter* Interactor) const
{
	// Base implementation always returns true
	// Override in derived classes to implement custom logic
	return true;
}


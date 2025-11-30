// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/RequirementComponent.h"
#include "_TheGauntlet/Core/GauntletCharacter.h"

URequirementComponent::URequirementComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URequirementComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool URequirementComponent::CheckRequirement_Implementation(AGauntletCharacter* Interactor)
{
	// Base implementation always returns true
	// Override in derived classes to implement custom logic
	return true;
}

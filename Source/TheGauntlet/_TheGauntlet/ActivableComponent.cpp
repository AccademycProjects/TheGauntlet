// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/ActivableComponent.h"

UActivableComponent::UActivableComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UActivableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UActivableComponent::PerformActivation_Implementation(AGauntletCharacter* Interactor)
{
	// Base implementation does nothing
	// Override in derived classes to implement custom logic
}


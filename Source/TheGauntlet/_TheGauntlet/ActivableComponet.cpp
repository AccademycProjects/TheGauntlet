// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/ActivableComponet.h"

UActivableComponet::UActivableComponet()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UActivableComponet::BeginPlay()
{
	Super::BeginPlay();
}

void UActivableComponet::PerformActivation_Implementation()
{
	// Base implementation does nothing
	// Override in derived classes to implement custom logic
}


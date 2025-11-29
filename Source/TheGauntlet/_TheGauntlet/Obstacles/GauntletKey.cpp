// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/Obstacles/GauntletKey.h"
#include "_TheGauntlet/Core/GauntletCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/WidgetComponent.h"

AGauntletKey::AGauntletKey()
{
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
}

void AGauntletKey::BeginPlay()
{
	Super::BeginPlay();
}

void AGauntletKey::Interact_Implementation(AGauntletCharacter* Interactor)
{
	if (!Interactor) return;

	// Check if character has AddKey method (it should, but safety check)
	Interactor->AddKey(KeyID);

	// Destroy the key
	Destroy();
}

bool AGauntletKey::CanInteract_Implementation(AGauntletCharacter* Interactor) const
{
	// Keys can always be picked up
	return Interactor != nullptr;
}


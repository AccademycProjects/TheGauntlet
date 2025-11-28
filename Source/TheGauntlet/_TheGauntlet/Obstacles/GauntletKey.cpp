// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/Obstacles/GauntletKey.h"
#include "_TheGauntlet/Core/GauntletCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

AGauntletKey::AGauntletKey()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	InteractionWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractionWidget"));
	InteractionWidget->SetupAttachment(RootComponent);
	InteractionWidget->SetWidgetSpace(EWidgetSpace::World);
	InteractionWidget->SetDrawSize(FVector2D(100.f, 50.f));
	InteractionWidget->SetVisibility(false);
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


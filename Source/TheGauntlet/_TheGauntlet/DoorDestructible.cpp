// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/DoorDestructible.h"
#include "_TheGauntlet/Components/GauntletHealthComponent.h"

ADoorDestructible::ADoorDestructible()
{
	HealthComponent = CreateDefaultSubobject<UGauntletHealthComponent>(TEXT("HealthComponent"));
}

void ADoorDestructible::BeginPlay()
{
	Super::BeginPlay();

	// Bind to health component death event
	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &ADoorDestructible::OnHealthComponentDeath);
	}
}

void ADoorDestructible::OnHealthComponentDeath(UGauntletHealthComponent* HealthComp, AActor* DamageInstigator)
{
	DestroyDoor();
}

void ADoorDestructible::DestroyDoor()
{
	Destroy();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "_TheGauntlet/Interfaces/Interactable.h"
#include "InteractableActor.generated.h"

class AGauntletCharacter;
class URequirementComponent;
class UActivableComponent;

/**
 * Base class for all interactable actors.
 * Handles requirement component checking and IInteractable interface.
 */
UCLASS()
class THEGAUNTLET_API AInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	AInteractableActor();

protected:
	virtual void BeginPlay() override;

	/** Requirement components that must be satisfied to interact */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<TObjectPtr<URequirementComponent>> RequirementComponents;

	/** Activable components activate after interaction */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TArray<TObjectPtr<UActivableComponent>> ActivableComponents;

	/** If true, the player cannot interact with this object directly */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interactable")
	bool bIsLockedForPlayerInteraction = false;

	/** Event called when the actor is interacted with */
	UFUNCTION(BlueprintNativeEvent, Category="Interactable")
	void OnInteracted(AGauntletCharacter* Interactor);

public:
	// IInteractable interface
	virtual void Interact_Implementation(AGauntletCharacter* Interactor) override;
	virtual void SystemInteract_Implementation(AGauntletCharacter* Interactor) override;
	virtual bool CanInteract_Implementation(AGauntletCharacter* Interactor) const override;
};

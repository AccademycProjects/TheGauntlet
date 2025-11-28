// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "_TheGauntlet/Interfaces/Interactable.h"
#include "GauntletDoor.generated.h"

class UStaticMeshComponent;
class AGauntletCharacter;

UCLASS()
class THEGAUNTLET_API AGauntletDoor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	AGauntletDoor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> DoorMesh;

	/** Key ID required to open this door (empty = no key required) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	FName RequiredKeyID = NAME_None;

	/** Is the door currently open? */
	UPROPERTY(BlueprintReadOnly, Category = "Door")
	bool bIsOpen = false;

public:
	// IInteractable interface
	virtual void Interact_Implementation(AGauntletCharacter* Interactor) override;
	virtual bool CanInteract_Implementation(AGauntletCharacter* Interactor) const override;

	/** Event called when door should open - Implement animation in Blueprint */
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OnDoorOpen();

	/** Event called when door should close - Implement animation in Blueprint */
	UFUNCTION(BlueprintImplementableEvent, Category = "Door")
	void OnDoorClose();
};


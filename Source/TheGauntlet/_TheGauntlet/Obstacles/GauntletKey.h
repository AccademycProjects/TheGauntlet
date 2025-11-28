// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "_TheGauntlet/Interfaces/Interactable.h"
#include "GauntletKey.generated.h"

class UStaticMeshComponent;
class UWidgetComponent;
class AGauntletCharacter;

UCLASS()
class THEGAUNTLET_API AGauntletKey : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:
	AGauntletKey();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> InteractionWidget;

	/** Unique ID for this key */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	FName KeyID = NAME_None;

	/** Show interaction prompt widget */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	bool bShowInteractionPrompt = true;

public:
	// IInteractable interface
	virtual void Interact_Implementation(AGauntletCharacter* Interactor) override;
	virtual bool CanInteract_Implementation(AGauntletCharacter* Interactor) const override;

};

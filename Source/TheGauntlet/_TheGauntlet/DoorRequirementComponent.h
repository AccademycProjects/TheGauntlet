// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorRequirementComponent.generated.h"

class AGauntletCharacter;

/**
 * Base component for door requirements.
 * Inherit from this to create custom requirement checks (key, levers, etc.)
 */
UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_API UDoorRequirementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDoorRequirementComponent();

	/**
	 * Checks if the requirement is satisfied.
	 * Override this in derived components to implement custom logic.
	 * @param Interactor The character trying to interact with the door
	 * @return true if requirement is satisfied, false otherwise
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Door Requirement")
	bool CheckRequirement(AGauntletCharacter* Interactor) const;

protected:
	virtual void BeginPlay() override;
};

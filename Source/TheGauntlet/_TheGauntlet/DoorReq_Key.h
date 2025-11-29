// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_TheGauntlet/DoorRequirementComponent.h"
#include "DoorReq_Key.generated.h"

/**
 * Requirement component that checks if the player has a specific key
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_API UDoorReq_Key : public UDoorRequirementComponent
{
	GENERATED_BODY()

public:
	UDoorReq_Key();

	/** Key ID required to open the door */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key Requirement")
	FName RequiredKeyID = NAME_None;

protected:
	virtual bool CheckRequirement_Implementation(class AGauntletCharacter* Interactor) const override;
};

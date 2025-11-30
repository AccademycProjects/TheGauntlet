// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_TheGauntlet/ActivableComponent.h"
#include "Controller_Timed.generated.h"

class AInteractableActor;
class AGauntletCharacter;

/**
 * Component that activates an InteractableActor for a specified duration
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THEGAUNTLET_API UController_Timed : public UActivableComponent
{
	GENERATED_BODY()

public:
	UController_Timed();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Interactable actor to control */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timed Controller")
	TObjectPtr<AInteractableActor> TargetActor;

	/** Character to use for interaction (if null, will try to find player) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timed Controller")
	TObjectPtr<AGauntletCharacter> InteractorCharacter;

	/** Duration in seconds before deactivating */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Timed Controller", meta = (ClampMin = "0.1"))
	float Duration = 5.f;

	FTimerHandle DeactivateTimerHandle;

	/** Deactivates the target actor after timer expires */
	void Deactivate();

public:
	virtual void PerformActivation_Implementation() override;

	/** Manually deactivate the target */
	UFUNCTION(BlueprintCallable, Category = "Timed Controller")
	void DeactivateNow();
};


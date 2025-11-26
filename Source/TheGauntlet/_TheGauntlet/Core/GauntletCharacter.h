// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GauntletCharacter.generated.h"

class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class THEGAUNTLET_API AGauntletCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGauntletCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;

#pragma endregion

#pragma region Input

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> PauseAction;

	void Move(const struct FInputActionValue& Value);
	void Look(const struct FInputActionValue& Value);
	void StartSprint();
	void StopSprint();
	void Interact();
	void TogglePause();

#pragma endregion

#pragma region Gameplay

public:
	// Movement
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay|Movement")
	float WalkSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay|Movement")
	float SprintSpeed = 800.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay|Movement")
	float JumpZVelocity = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay|Movement")
	float AirControl = 0.35f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay|Movement")
	float GravityScale = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay|Movement")
	float GroundFriction = 8.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay|Movement")
	float BrakingDecelerationWalking = 2048.f;

	// Health system
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Gameplay|Health")
	float MaxHealth = 100.f;

	UPROPERTY(BlueprintReadOnly, Category = "Gameplay|Health")
	float CurrentHealth;

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Health")
	void TakeDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Health")
	bool IsAlive() const { return CurrentHealth > 0.f; }

	// Key inventory
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gameplay|Inventory")
	TArray<FName> CollectedKeys;

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Inventory")
	void AddKey(FName KeyID);

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Inventory")
	bool HasKey(FName KeyID) const;

#pragma endregion
};

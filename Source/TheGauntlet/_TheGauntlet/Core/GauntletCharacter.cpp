// Fill out your copyright notice in the Description page of Project Settings.

#include "_TheGauntlet/Core/GauntletCharacter.h"
#include "_TheGauntlet/Core/GauntletGameInstance.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGauntletCharacter::AGauntletCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bUsePawnControlRotation = true;

	// Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	// Character rotation settings
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->JumpZVelocity = JumpZVelocity;
	GetCharacterMovement()->AirControl = AirControl;
	GetCharacterMovement()->GravityScale = GravityScale;
	GetCharacterMovement()->GroundFriction = GroundFriction;
	GetCharacterMovement()->BrakingDecelerationWalking = BrakingDecelerationWalking;

	// Initialize health
	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void AGauntletCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	APlayerController* PC = Cast<APlayerController>(GetController());
	if (!PC)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AGauntletCharacter: NO PlayerController in BeginPlay"));
		return;
	}

	ULocalPlayer* LP = PC->GetLocalPlayer();
	if (!LP)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AGauntletCharacter: NO LocalPlayer"));
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LP);
	if (!Subsystem)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AGauntletCharacter: NO EnhancedInput Subsystem"));
		return;
	}

	if (!InputMappingContext)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AGauntletCharacter: InputMappingContext is NULL"));
		return;
	}

	Subsystem->AddMappingContext(InputMappingContext, 0);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("AGauntletCharacter: MappingContext ADDED"));

}

void AGauntletCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGauntletCharacter::Move);

			if (!MoveAction && GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("MoveAction is NULL"));
		}
		if (LookAction)
		{
			EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGauntletCharacter::Look);

			if (!LookAction && GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("LookAction is NULL"));
		}
		if (JumpAction)
		{
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

			if (!JumpAction && GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("JumpAction is NULL"));
		}
		if (SprintAction)
		{
			EnhancedInput->BindAction(SprintAction, ETriggerEvent::Started, this, &AGauntletCharacter::StartSprint);
			EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &AGauntletCharacter::StopSprint);

			if (!SprintAction && GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SprintAction is NULL"));
		}
		if (InteractAction)
		{
			EnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &AGauntletCharacter::Interact);

			if (!InteractAction && GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("InteractAction is NULL"));
		}
		if (PauseAction)
		{
			EnhancedInput->BindAction(PauseAction, ETriggerEvent::Started, this, &AGauntletCharacter::TogglePause);

			if (!PauseAction && GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PauseAction is NULL"));
		}
	}
}

#pragma region Input Functions

void AGauntletCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MoveInput = Value.Get<FVector2D>();

	if (Controller && !MoveInput.IsNearlyZero())
	{
		// Get forward and right vectors based on controller rotation
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDir, MoveInput.Y);
		AddMovementInput(RightDir, MoveInput.X);

		if (GEngine)
		{
			const FString Msg = FString::Printf(
				TEXT("MoveInput: X = %f, Y = %f"),
				MoveInput.X,
				MoveInput.Y
			);

			GEngine->AddOnScreenDebugMessage(
				1,
				5.f,
				FColor::Green,
				Msg
			);
		}
	}
}

void AGauntletCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookInput.X);
		AddControllerPitchInput(LookInput.Y);
	}

	if (GEngine)
	{
		const FString Msg = FString::Printf(
			TEXT("LookInput: X = %f, Y = %f"),
			LookInput.X,
			LookInput.Y
		);

		GEngine->AddOnScreenDebugMessage(
			1,
			5.f,
			FColor::Green,
			Msg
		);
	}
}

void AGauntletCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
}

void AGauntletCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void AGauntletCharacter::Interact()
{
	// TODO: Implement interaction with IInteractable interface
	// Line trace forward, check for IInteractable, call Interact()
}

void AGauntletCharacter::TogglePause()
{
	if (UGauntletGameInstance* GI = GetGameInstance<UGauntletGameInstance>())
	{
		const EGauntletGameState CurrentState = GI->GetGameState();
		
		if (CurrentState == EGauntletGameState::InPlay)
		{
			GI->SetGameState(EGauntletGameState::InPause);
		}
		else if (CurrentState == EGauntletGameState::InPause)
		{
			GI->SetGameState(EGauntletGameState::InPlay);
		}
	}
}

#pragma endregion

#pragma region Gameplay

void AGauntletCharacter::TakeDamage(float Damage)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);

	if (!IsAlive())
	{
		// TODO: Notify GameMode of player death
	}
}

void AGauntletCharacter::AddKey(FName KeyID)
{
	if (!CollectedKeys.Contains(KeyID))
	{
		CollectedKeys.Add(KeyID);
	}
}

bool AGauntletCharacter::HasKey(FName KeyID) const
{
	return CollectedKeys.Contains(KeyID);
}

#pragma endregion

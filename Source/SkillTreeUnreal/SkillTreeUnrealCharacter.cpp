// Copyright Epic Games, Inc. All Rights Reserved.

#include "SkillTreeUnrealCharacter.h"
#include "SkillTreeUnrealProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ASkillTreeUnrealCharacter

ASkillTreeUnrealCharacter::ASkillTreeUnrealCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void ASkillTreeUnrealCharacter::RemoveSkillsPoints(int32 Cost)
{
	SkillPoints -= Cost;
	OnSkillUnlocked.ExecuteIfBound();
}

void ASkillTreeUnrealCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (SkillTreeWidgetClass)
	{
		SkillTreeWidget = CreateWidget(GetWorld(), SkillTreeWidgetClass);
		SkillTreeWidget->AddToViewport();
		SkillTreeWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	SkillPoints = 100;
}

//////////////////////////////////////////////////////////////////////////// Input

void ASkillTreeUnrealCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASkillTreeUnrealCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASkillTreeUnrealCharacter::Look);

		EnhancedInputComponent->BindAction(ToggleSkillTreeAction, ETriggerEvent::Started, this, &ASkillTreeUnrealCharacter::ToggleSkillTree);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void ASkillTreeUnrealCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ASkillTreeUnrealCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASkillTreeUnrealCharacter::ToggleSkillTree(const FInputActionValue& Value)
{
	if (!IsValid(PlayerController) || !IsValid(SkillTreeWidgetClass))
	{
		return;
	}
	
	if (bCanToggleSkillTree)
	{
		SkillTreeWidget->SetVisibility(ESlateVisibility::Visible);
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->SetShowMouseCursor(true);
		bCanToggleSkillTree = false;
	}
	else
	{
		SkillTreeWidget->SetVisibility(ESlateVisibility::Collapsed);
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->SetShowMouseCursor(false);
		bCanToggleSkillTree = true;
	}
}

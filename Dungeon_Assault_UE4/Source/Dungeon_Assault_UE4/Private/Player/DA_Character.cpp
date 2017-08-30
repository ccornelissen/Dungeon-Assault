// Fill out your copyright notice in the Description page of Project Settings.

#include "DA_Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "WeaponEquipComponent.h"
#include "ShieldEquipComponent.h"
#include "PaperFlipbookComponent.h"
#include "DAPlayerUI.h"

// Sets default values
ADA_Character::ADA_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	//Don't rotate the camera with the player
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	//Constrain character movement for top down camera view
	GetCharacterMovement()->bOrientRotationToMovement = true; //Rotate character to face moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f); //TODO: Should get rid of floating number
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//Creating the camera boom
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->bAbsoluteRotation = true;
	CameraArm->TargetArmLength = 800.0f; //TODO: Should get rid of floating number
	CameraArm->RelativeRotation = FRotator(-60.0f, 0.0f, 0.0f); //TODO: Should get rid of floating number
	CameraArm->bDoCollisionTest = false;

	//Creating the camera
	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
	TopDownCamera->bUsePawnControlRotation = false;

	//Create weapon slot
	CurWeapon = CreateDefaultSubobject<UWeaponEquipComponent>(TEXT("MainHandWeapon"));
	CurWeapon->SetupAttachment(RootComponent);
	CurWeapon->bGenerateOverlapEvents = false;

	CurShield = CreateDefaultSubobject<UShieldEquipComponent>(TEXT("ShieldSlot"));
	CurShield->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	CurShield->bGenerateOverlapEvents = false;

	ShieldIdlePoint = CreateDefaultSubobject<USceneComponent>(TEXT("ShieldIdlePoint"));
	ShieldIdlePoint->SetupAttachment(RootComponent);

	ShieldBlockPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ShieldBlockPoint"));
	ShieldBlockPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADA_Character::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerUI)
	{
		PlayerUI->fPlayerMaxHealth = fPlayerHealth;
	}
	
	
	if (CurWeapon && FirstWeapon)
	{
		if (FirstWeapon->IsChildOf(UWeaponEquipComponent::StaticClass()))
		{
			CurWeapon->WeaponInfo = FirstWeapon->GetDefaultObject<UWeaponEquipComponent>()->WeaponInfo;

			CurWeapon->SetWeapon();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CurWeapon or First Weapon returning null"));
	}

	if (CurShield && FirstOffhand)
	{
		if (FirstOffhand->IsChildOf(UShieldEquipComponent::StaticClass()))
		{
			CurShield->ShieldInfo = FirstOffhand->GetDefaultObject<UShieldEquipComponent>()->ShieldInfo;

			CurShield->SetShield();

			if (ShieldIdlePoint && ShieldBlockPoint)
			{
				CurShield->SetIdlePoint(*ShieldIdlePoint);
				CurShield->SetBlockingPoint(*ShieldBlockPoint);
			}

			CurShield->UnBlock();
		}
	}
}


// Called every frame
void ADA_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADA_Character::DATakeDamage(float DamageToTake)
{
	fPlayerHealth -= DamageToTake;

	if (PlayerUI)
	{
		PlayerUI->UpdateHealthBar(fPlayerHealth);
	}

	CheckIfDead();
}

void ADA_Character::CheckIfDead()
{
	if (fPlayerHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is dead now!"));
	}
}

void ADA_Character::SetPlayerUI(UDAPlayerUI & UIToSet)
{
	PlayerUI = &UIToSet;
}

// Called to bind functionality to input
void ADA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("WeaponAttack", IE_Pressed, this, &ADA_Character::UseWeapon);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &ADA_Character::SwitchWeapon);
	PlayerInputComponent->BindAction("AltAction", IE_Pressed, this, &ADA_Character::OffhandUsed);
	PlayerInputComponent->BindAction("AltAction", IE_Released, this, &ADA_Character::OffhandReleased);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADA_Character::MoveVertical);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADA_Character::MoveHorizontal);
}

void ADA_Character::MoveVertical(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ADA_Character::UseWeapon()
{
	if (CurWeapon)
	{
		CurWeapon->Attack();
	}
}

void ADA_Character::OffhandUsed()
{
	if (CurShield->ShieldInfo.IdleBook != nullptr)
	{
		CurShield->Block();
	}
}

void ADA_Character::OffhandReleased()
{
	if (CurShield->ShieldInfo.IdleBook != nullptr)
	{
		CurShield->UnBlock();
	}
}

void ADA_Character::SwitchWeapon()
{
	if (bFirstWeaponEquiped)
	{
		if (CurWeapon && SecondWeapon)
		{
			if (SecondWeapon->IsChildOf(UWeaponEquipComponent::StaticClass()))
			{
				CurWeapon->WeaponInfo = SecondWeapon->GetDefaultObject<UWeaponEquipComponent>()->WeaponInfo;

				CurWeapon->SetWeapon();
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CurWeapon or Second Weapon returning null"));
		}

		bFirstWeaponEquiped = false;
	}
	else
	{
		if (CurWeapon && FirstWeapon)
		{
			if (FirstWeapon->IsChildOf(UWeaponEquipComponent::StaticClass()))
			{
				CurWeapon->WeaponInfo = FirstWeapon->GetDefaultObject<UWeaponEquipComponent>()->WeaponInfo;

				CurWeapon->SetWeapon();
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CurWeapon or First Weapon returning null"));
		}

		bFirstWeaponEquiped = true;
	}

	if (bFirstOffhandEquiped)
	{
		if (CurShield && SecondOffhand)
		{
			if (SecondOffhand->IsChildOf(UShieldEquipComponent::StaticClass()))
			{
				CurShield->ShieldInfo = SecondOffhand->GetDefaultObject<UShieldEquipComponent>()->ShieldInfo;

				CurShield->SetShield();
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CurShield or Second Offhand returning null"));
		}

		bFirstOffhandEquiped = false;
	}
	else
	{
		if (CurShield && FirstOffhand)
		{
			if (FirstOffhand->IsChildOf(UShieldEquipComponent::StaticClass()))
			{
				CurShield->ShieldInfo = FirstOffhand->GetDefaultObject<UShieldEquipComponent>()->ShieldInfo;

				CurShield->SetShield();
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CurShield or First Offhand returning null"));
		}

		bFirstOffhandEquiped = true;
	}

}

void ADA_Character::MoveHorizontal(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}




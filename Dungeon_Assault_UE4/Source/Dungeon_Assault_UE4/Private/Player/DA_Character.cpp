// Fill out your copyright notice in the Description page of Project Settings.

#include "DA_Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "WeaponBase.h"
#include "ShieldBase.h"
#include "RangedBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "Dungeon_Assault_UE4.h"
#include "EquipmentBase.h"
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

	//Create the player body.
	BodyComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerBody"));
	BodyComp->SetupAttachment(RootComponent);

	//Create the player head.
	HeadComp = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerHead"));
	HeadComp->SetupAttachment(RootComponent);

	//Create weapon slot
	CurWeaponPos = CreateDefaultSubobject<USceneComponent>(FName(TEXT("CurrentWeapon")));
	CurWeaponPos->SetupAttachment(RootComponent);
	CurWeaponPos->SetRelativeLocation(FVector(30.0, 30.0, -70.0));
	CurWeaponPos->SetRelativeRotation(FRotator(-90, 0, 90));

	//Create Offhand 
	CurOffhandPos = CreateDefaultSubobject<USceneComponent>(FName(TEXT("CurrentOffhand")));
	CurOffhandPos->SetupAttachment(RootComponent);
	CurOffhandPos->SetRelativeLocation(FVector(-10.0, -40.0, -70.0));
	CurOffhandPos->SetRelativeRotation(FRotator(-90, 0, 90));

	//Create Shield points
	ShieldIdlePoint = CreateDefaultSubobject<USceneComponent>(TEXT("ShieldIdlePoint"));
	ShieldIdlePoint->SetupAttachment(RootComponent);
	ShieldIdlePoint->SetRelativeLocation(FVector(-10.0, -40.0, -70.0));
	ShieldIdlePoint->SetRelativeRotation(FRotator(-90, 0, 90));

	ShieldBlockPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ShieldBlockPoint"));
	ShieldBlockPoint->SetupAttachment(RootComponent);
	ShieldBlockPoint->SetRelativeLocation(FVector(67.0, -21.0, -70.0));
	ShieldBlockPoint->SetRelativeRotation(FRotator(-90, 0, 160));
}

// Called when the game starts or when spawned
void ADA_Character::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerUI)
	{
		PlayerUI->fPlayerMaxHealth = fPlayerHealth;
	}
	
	fCurrentHealth = fPlayerHealth;
	
	if (CurWeaponPos && FirstWeapon)
	{
		if (FirstWeapon->IsChildOf(AEquipmentBase::StaticClass()))
		{
			EquippedWeapon = GetWorld()->SpawnActor<AEquipmentBase>(FirstWeapon, CurWeaponPos->GetComponentLocation(), CurWeaponPos->GetComponentRotation());

			EquippedWeapon->AttachToComponent(CurWeaponPos, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			EquippedWeapon->SetPlayer(*this);

			EquippedWeapon->SetWeapon();
		}
	}
	else if (CurWeaponPos == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Weapon Position!"));
	}
	else if (FirstWeapon == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character missing a starting weapon!"));
	}

	if (CurOffhandPos && FirstOffhand)
	{
		if (FirstOffhand->IsChildOf(AEquipmentBase::StaticClass()))
		{
			UE_LOG(LogTemp, Warning, TEXT("Setting Offhand!"));

			EquippedOffhand = GetWorld()->SpawnActor<AEquipmentBase>(FirstOffhand, CurOffhandPos->GetComponentLocation(), CurOffhandPos->GetComponentRotation());

			EquippedOffhand->AttachToComponent(CurOffhandPos, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

			EquippedOffhand->SetPlayer(*this);

			EquippedOffhand->SetWeapon();

			if (EquippedOffhand->MyEquipType == EEquipmentType::ET_Shield)
			{
				UE_LOG(LogTemp, Warning, TEXT("Setting Shield!"));
				 
				AShieldBase* OffShield = Cast<AShieldBase>(EquippedOffhand);
				OffShield->SetIdlePoint(*ShieldIdlePoint);
				OffShield->SetBlockingPoint(*ShieldBlockPoint);

				OffShield->UnBlock();
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CurOffhand or FirstOffhand returning null"));
	}

	CalculateMovementSpeed();
}


// Called every frame
void ADA_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADA_Character::DATakeDamage(float DamageToTake)
{
	fCurrentHealth -= DamageToTake;

	UE_LOG(LogTemp, Warning, TEXT("Player health = %f"), fCurrentHealth);

	if (PlayerUI)
	{
		PlayerUI->UpdateHealthBar(fCurrentHealth);
	}

	CheckIfDead();
}

void ADA_Character::CheckIfDead()
{
	if (fCurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player is dead now!"));
	}
}

void ADA_Character::SetPlayerUI(UDAPlayerUI & UIToSet)
{
	PlayerUI = &UIToSet;
}

void ADA_Character::AddCoins(int32 ValueToAdd)
{
	SaveGameInstance = Cast<UDASaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));

	int32 NewValue = SaveGameInstance->MenuSaveData.iPlayerCoins + ValueToAdd;

	SaveGameInstance->MenuSaveData.iPlayerCoins = NewValue;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
}

void ADA_Character::SetSaveInstance(UDASaveGame & SaveGame)
{
	SaveGameInstance = &SaveGame;
}

void ADA_Character::Heal(float AmountToHeal)
{
	fCurrentHealth += AmountToHeal;

	if (fCurrentHealth > fPlayerHealth)
	{
		fCurrentHealth = fPlayerHealth;
	}

	if (PlayerUI)
	{
		PlayerUI->UpdateHealthBar(fCurrentHealth);
	}
}

// Called to bind functionality to input
void ADA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInput = PlayerInputComponent;

	PlayerInputComponent->BindAction("WeaponAttack", IE_Pressed, this, &ADA_Character::UseWeapon);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &ADA_Character::SwitchWeapon);
	PlayerInputComponent->BindAction("AltAction", IE_Pressed, this, &ADA_Character::OffhandUsed);
	PlayerInputComponent->BindAction("AltAction", IE_Released, this, &ADA_Character::OffhandReleased);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADA_Character::MoveVertical);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADA_Character::MoveVertical);
}

void ADA_Character::MoveVertical(float Value)
{
	TurnToFace();

	UpdateBodyComponents();

	Value = FMath::Abs(Value);

	AddMovementInput(GetActorForwardVector(), Value);
}

void ADA_Character::UseWeapon()
{
	if (EquippedWeapon)
	{
		if (EquippedWeapon->MyEquipType == EEquipmentType::ET_Melee)
		{
			AWeaponBase* MyWeapon = Cast<AWeaponBase>(EquippedWeapon);

			if (MyWeapon)
			{
				UE_LOG(LogTemp, Warning, TEXT("Melee Attack"));

				MyWeapon->Attack();
			}
		}
		else if (EquippedWeapon->MyEquipType == EEquipmentType::ET_Ranged)
		{
			ARangedBase* MyRanged = Cast<ARangedBase>(EquippedWeapon);

			if (MyRanged)
			{
				UE_LOG(LogTemp, Warning, TEXT("Ranged Attack"));
				MyRanged->Attack();
			}
		}
	}
}

void ADA_Character::OffhandUsed()
{
	if (EquippedOffhand)
	{
		if (EquippedOffhand->MyEquipType == EEquipmentType::ET_Shield)
		{
			AShieldBase* MyShield = Cast<AShieldBase>(EquippedOffhand);

			if (MyShield)
			{
				UE_LOG(LogTemp, Warning, TEXT("Blocking"));

				MyShield->Block();
			}
		}
		else if (EquippedOffhand->MyEquipType == EEquipmentType::ET_Ranged)
		{
			ARangedBase* MyRanged = Cast<ARangedBase>(EquippedOffhand);

			if (MyRanged)
			{
				UE_LOG(LogTemp, Warning, TEXT("Ranged Attack"));
				MyRanged->Attack();
			}
		}
	}
}

void ADA_Character::OffhandReleased()
{
	if (EquippedOffhand)
	{
		if (EquippedOffhand->MyEquipType == EEquipmentType::ET_Shield)
		{
			AShieldBase* MyShield = Cast<AShieldBase>(EquippedOffhand);

			if (MyShield)
			{
				MyShield->UnBlock();
			}
		}
	}
}

void ADA_Character::SwitchWeapon()
{
	if (bFirstWeaponEquiped)
	{
		if (EquippedWeapon && SecondWeapon)
		{
			if (SecondWeapon->IsChildOf(AEquipmentBase::StaticClass()))
			{
				EquippedWeapon->Destroy();

				EquippedWeapon = GetWorld()->SpawnActor<AEquipmentBase>(SecondWeapon, CurWeaponPos->GetComponentLocation(), CurWeaponPos->GetComponentRotation());

				EquippedWeapon->AttachToComponent(CurWeaponPos, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

				EquippedWeapon->SetPlayer(*this);

				EquippedWeapon->SetWeapon();
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
		if (EquippedWeapon && FirstWeapon)
		{
			if (FirstWeapon->IsChildOf(AEquipmentBase::StaticClass()))
			{
				EquippedWeapon->Destroy();

				EquippedWeapon = GetWorld()->SpawnActor<AEquipmentBase>(FirstWeapon, CurWeaponPos->GetComponentLocation(), CurWeaponPos->GetComponentRotation());

				EquippedWeapon->AttachToComponent(CurWeaponPos, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

				EquippedWeapon->SetPlayer(*this);

				EquippedWeapon->SetWeapon();
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
		if (EquippedOffhand && SecondOffhand)
		{
			if (SecondOffhand->IsChildOf(AEquipmentBase::StaticClass()))
			{
				EquippedOffhand->Destroy();

				EquippedOffhand = GetWorld()->SpawnActor<AEquipmentBase>(SecondOffhand, CurWeaponPos->GetComponentLocation(), CurWeaponPos->GetComponentRotation());

				EquippedOffhand->AttachToComponent(CurOffhandPos, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

				EquippedOffhand->SetPlayer(*this);

				EquippedOffhand->SetWeapon();

				if (EquippedOffhand->MyEquipType == EEquipmentType::ET_Shield)
				{
					UE_LOG(LogTemp, Warning, TEXT("Setting Shield!"));

					AShieldBase* OffShield = Cast<AShieldBase>(EquippedOffhand);
					OffShield->SetIdlePoint(*ShieldIdlePoint);
					OffShield->SetBlockingPoint(*ShieldBlockPoint);

					OffShield->UnBlock();
				}
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

		if (EquippedOffhand && FirstOffhand)
		{
			if (FirstOffhand->IsChildOf(AEquipmentBase::StaticClass()))
			{
				EquippedOffhand->Destroy();

				EquippedOffhand = GetWorld()->SpawnActor<AEquipmentBase>(FirstOffhand, CurWeaponPos->GetComponentLocation(), CurWeaponPos->GetComponentRotation());

				EquippedOffhand->AttachToComponent(CurOffhandPos, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

				EquippedOffhand->SetPlayer(*this);

				EquippedOffhand->SetWeapon();

				if (EquippedOffhand->MyEquipType == EEquipmentType::ET_Shield)
				{
					UE_LOG(LogTemp, Warning, TEXT("Setting Shield!"));

					AShieldBase* OffShield = Cast<AShieldBase>(EquippedOffhand);
					OffShield->SetIdlePoint(*ShieldIdlePoint);
					OffShield->SetBlockingPoint(*ShieldBlockPoint);

					OffShield->UnBlock();
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("CurShield or Second Offhand returning null"));
		}

		bFirstOffhandEquiped = true;
	}
}

void ADA_Character::TurnToFace()
{
	float fToRotate = 0.0f;

	if (PlayerInput)
	{
		float fForward = PlayerInput->GetAxisValue("MoveForward");
		float fRight = PlayerInput->GetAxisValue("MoveRight");

		fToRotate = atan2f(fRight, fForward);

		fToRotate = FMath::RadiansToDegrees(fToRotate);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player input returning null!"));
	}

	FRotator StartRot = GetActorRotation();

	FRotator NewRotation = FRotator(StartRot.Pitch, fToRotate, StartRot.Roll);

	SetActorRotation(NewRotation);
}

void ADA_Character::UpdateBodyComponents()
{
	FRotator CurPlayerRot = GetActorRotation();
	if (HeadBooks.Num() != 0)
	{
		if (CurPlayerRot.Yaw < -91.0f || CurPlayerRot.Yaw > 89.0f)
		{
			if (HeadComp && HeadBooks[0])
			{
				HeadComp->SetFlipbook(HeadBooks[0]);
			}
		}
		else if (CurPlayerRot.Yaw > -89.0f || CurPlayerRot.Yaw < 91.0f)
		{
			if (HeadComp && HeadBooks[1])
			{
				HeadComp->SetFlipbook(HeadBooks[1]);
			}
		}
	}
}

void ADA_Character::CalculateMovementSpeed()
{
	float fCalculatedSpeed = 0.0f;

	fCalculatedSpeed = fPlayerSpeed * fArmorSlowDown;

	GetCharacterMovement()->MaxWalkSpeed = fCalculatedSpeed;

}




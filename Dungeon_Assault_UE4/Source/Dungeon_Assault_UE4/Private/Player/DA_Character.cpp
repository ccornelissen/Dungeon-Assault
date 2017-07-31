// Fill out your copyright notice in the Description page of Project Settings.

#include "DA_Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "WeaponEquipComponent.h"

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

	//Adding weapon component
	WeaponComp = CreateDefaultSubobject<UWeaponEquipComponent>(TEXT("Weapon"));
	WeaponComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADA_Character::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ADA_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("WeaponAttack", IE_Pressed, this, &ADA_Character::UseWeapon);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADA_Character::MoveVertical);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADA_Character::MoveHorizontal);
}

void ADA_Character::MoveVertical(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ADA_Character::UseWeapon()
{
	WeaponComp->Attack();
}

void ADA_Character::MoveHorizontal(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}




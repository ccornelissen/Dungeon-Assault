// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DA_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPaperFlipbookComponent;
class UDAPlayerUI;
class UPaperFlipbook;
class UDASaveGame;
class AEquipmentBase;

UCLASS()
class DUNGEON_ASSAULT_UE4_API ADA_Character : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	ADA_Character();

	FORCEINLINE UCameraComponent* GetTopDownCameraComponent() const { return TopDownCamera; }
	FORCEINLINE USpringArmComponent* GetCameraSpringArm() const { return CameraArm; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void DATakeDamage(float DamageToTake);

	void CheckIfDead();

	void SetSaveInstance(UDASaveGame& SaveGame);

	void SetPlayerUI(UDAPlayerUI& UIToSet);

	void AddCoins(int32 ValueToAdd);

	void Heal(float AmountToHeal);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Player weapons
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TSubclassOf<AEquipmentBase> FirstWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TSubclassOf<AEquipmentBase> FirstOffhand = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TSubclassOf<AEquipmentBase> SecondWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
	TSubclassOf<AEquipmentBase> SecondOffhand = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveVertical(float Value);

	void UseWeapon();

	void OffhandUsed();

	void OffhandReleased();

	void SwitchWeapon();

	void TurnToFace();

	UPROPERTY(EditDefaultsOnly, Category = "Player Variables")
	float fPlayerSpeed = 600.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Player Variables")
	float fArmorSlowDown = 0.95f;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float fPlayerHealth = 100.0f;

	//PLAYER BODY COMPONENTS
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	TArray<UPaperFlipbook*> HeadBooks;

	void UpdateBodyComponents();

	void CalculateMovementSpeed();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCamera;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	USceneComponent* CurWeaponPos = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	USceneComponent* CurOffhandPos = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ShieldIdlePoint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ShieldBlockPoint = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* BodyComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
	UPaperFlipbookComponent* HeadComp = nullptr;

	AEquipmentBase* EquippedWeapon = nullptr;

	AEquipmentBase* EquippedOffhand = nullptr;

	UDASaveGame* SaveGameInstance;

	float fCurrentHealth;

	bool bFirstWeaponEquiped = true;
	bool bFirstOffhandEquiped = true;

	UInputComponent* PlayerInput;

	UDAPlayerUI* PlayerUI = nullptr;
};

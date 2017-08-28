// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DA_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UPaperFlipbookComponent;
class UWeaponEquipComponent;
class UShieldEquipComponent;
class UDAPlayerUI;

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

	void SetPlayerUI(UDAPlayerUI& UIToSet);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Player weapons
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<UPaperFlipbookComponent> FirstWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<UPaperFlipbookComponent> FirstOffhand = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<UPaperFlipbookComponent> SecondWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<UPaperFlipbookComponent> SecondOffhand = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveHorizontal(float Value);
	void MoveVertical(float Value);

	void UseWeapon();

	void SwitchWeapon();

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float fPlayerHealth = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	UWeaponEquipComponent* CurWeapon = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	UShieldEquipComponent* CurShield = nullptr;
	

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCamera;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;

	bool bFirstWeaponEquiped = true;
	bool bFirstOffhandEquiped = true;

	UDAPlayerUI* PlayerUI = nullptr;
};

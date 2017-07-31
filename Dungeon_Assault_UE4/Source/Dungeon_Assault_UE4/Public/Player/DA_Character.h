// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DA_Character.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UWeaponEquipComponent;

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

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveHorizontal(float Value);
	void MoveVertical(float Value);

	void UseWeapon();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCamera;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraArm;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	UWeaponEquipComponent* WeaponComp;
};

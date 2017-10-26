// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossBase.generated.h"

class UEnemyHealthBar;
class ABossLauncher;
class ABossMelee;
class AMinionSpawner;
class USceneComponent;
class APaperFlipbookActor;
class AArenaEndDoor;
class UDASaveGame;
class ADACoin;

UCLASS()
class DUNGEON_ASSAULT_UE4_API ABossBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossBase();

	virtual void Tick(float DeltaTime) override;

	void ApplyDamage(float Damage);

	void SetEndDoor(AArenaEndDoor& DoorRef);

	void SetSaveInstance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Boss Components")
	void SetComponents();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	UEnemyHealthBar* BaseHealthBar = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Player Coin")
	TSubclassOf<ADACoin> Coin = nullptr;

	//Boss Component Spawn Arrays//

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Boss Components")
	TArray<USceneComponent*> ComponentSpawns;

	TArray<TSubclassOf<APaperFlipbookActor>> BossSupport;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Components")
	TArray<TSubclassOf<APaperFlipbookActor>> BossComponentDif1;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Components")
	TArray<TSubclassOf<APaperFlipbookActor>> BossComponentDif2;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Components")
	TArray<TSubclassOf<APaperFlipbookActor>> BossComponentDif3;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Components")
	TArray<TSubclassOf<APaperFlipbookActor>> BossComponentDif4;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Components")
	TArray<TSubclassOf<APaperFlipbookActor>> BossComponentDif5;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float fBossHealth = 100.0f;

	int32 iNumberOfComponentsToSpawn = 0;

	void CalculateDifficulty();
	
	void DeathCheck();

	AArenaEndDoor* EndDoor = nullptr;

	TArray<AActor*> SpawnedActors;

	UDASaveGame* SaveGameInstance;

	void SpawnComponents();
};

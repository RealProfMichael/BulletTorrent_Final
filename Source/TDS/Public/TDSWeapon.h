// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDSWeapon.generated.h"

UCLASS()
class TDS_API ATDSWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float FiringRate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	bool IsAutoFire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float MaxLoadedAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float ShotCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings", meta = (AllowPrivateAccess = "true"))
	float ShotSpread;

public:
	// Sets default values for this actor's properties
	ATDSWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void Equip();
	void UnEquip();

	UFUNCTION(BlueprintImplementableEvent, Category = "Equipping")
	void OnEquip();

	UFUNCTION(BlueprintImplementableEvent, Category = "Equipping")
	void OnUnEquip();

};
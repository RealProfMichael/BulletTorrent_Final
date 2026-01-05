// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"
#include "TDS.generated.h"

UENUM(BlueprintType)
enum class EAbilityInputID : uint8
{
    None,
    Confirm,
    Cancel,
    PrimaryAbility,
    SecondaryAbility,
    MovementAbility,
    UtilityAbility,
    WeaponFire,
    WeaponAlt,
    WeaponReload
};

UENUM(BlueprintType)
enum class EUpgradeType : uint8
{
    None,
    HealthCommon,
    HealthRare,
    HealthEpic,
    DamageCommon,
    DamageRare,
    DamageEpic,
    FiringRateCommon,
    FiringRateRare,
    FiringRateEpic,
    MoveSpeedCommon,
    MoveSpeedRare,
    MoveSpeedZoomies,
    // More later
};

USTRUCT(BlueprintType)
struct FMissionInfo : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Map;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool IsRepeateable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FName> Prerequisites;
};

namespace TDSGameplayTags
{
    TDS_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_Spawned);
    TDS_API	UE_DECLARE_GAMEPLAY_TAG_EXTERN(InitState_GameplayReady);
};

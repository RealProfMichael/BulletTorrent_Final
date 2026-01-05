// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TDSBlueprintLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TDS_API UTDSBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static TArray<FVector> CalcDirectionsAroundAxis(FVector Axis, int Count);

};

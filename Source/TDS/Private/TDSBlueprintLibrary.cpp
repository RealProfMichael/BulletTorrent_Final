// Fill out your copyright notice in the Description page of Project Settings.


#include "TDSBlueprintLibrary.h"

TArray<FVector> UTDSBlueprintLibrary::CalcDirectionsAroundAxis(FVector Axis, int Count)
{
	TArray<FVector> Directions;

	FVector Vec(1.0f, 0.0f, 0.0f);
	float AngleDegrees = 360.0f / Count;

	for (int i = 0; i < Count; i++)
	{
		FVector Direction = Vec.RotateAngleAxis(i * AngleDegrees, Axis);
		Directions.Add(Direction);
	}

	return Directions;
}

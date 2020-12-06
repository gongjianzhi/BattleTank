// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void SetThrottle(float Throttle);

private:
	TArray<class ASprungWheel*> GetWheels() const;

	void DriveTrack(float CurrentThrottle);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	float TrackMaxDrivingForce = 4000000;	

};

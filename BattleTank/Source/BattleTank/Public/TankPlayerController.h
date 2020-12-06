// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRef);

	UFUNCTION()
	void OnPossessedTankDeath();
private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetPawn(APawn* InPawn) override;

	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landsacpe
	bool GetSightRayHitLocation(FVector& Out_HitLocation) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& Out_HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& Out_LookDirection) const;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.3333f;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;


};


// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (!GetPawn()) return;
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
	
	FoundAimingComponent(AimingComponent);

}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
	}
}

void ATankPlayerController::OnPossessedTankDeath()
{
	StartSpectatingOnly();
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetPawn()) { return; }
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;// OUT parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& Out_HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation,LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, Out_HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& Out_LookDirection) const
{
	FVector CameraWorldLocation;// ±»¶ªÆúÁË
	bool result = DeprojectScreenPositionToWorld(
		ScreenLocation.X, 
		ScreenLocation.Y, 
		CameraWorldLocation, 
		Out_LookDirection);

	//UE_LOG(LogTemp, Warning, TEXT("WorldLocation: %s"), *CameraWorldLocation.ToString());
	
	return result;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& Out_HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + LookDirection * LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(HitResult,StartLocation,EndLocation,ECollisionChannel::ECC_Camera))
	{
		Out_HitLocation = HitResult.Location;
		return true;
	}

	Out_HitLocation = FVector(0.f);
	return false;
}

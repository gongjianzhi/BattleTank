// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

    //Called by the engine when actor damage is dealt
    virtual float TakeDamage
    (
        float DamageAmount,
        struct FDamageEvent const& DamageEvent,
        AController* EventInstigator,
        AActor* DamageCauser
    ) override;

    //Return current health as a percentage of starting health, between 0 and 1
    UFUNCTION(BlueprintPure, Category = "Health")
    float GetHealthPercent() const;

    FTankDelegate OnDeath;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    int32 StartingHealth = 100;

    int32 CurrentHealth = StartingHealth;


};

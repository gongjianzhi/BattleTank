// Fill out your copyright notice in the Description page of Project Settings.


#include "SprungWheel.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassWheelCostraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelCostraint"));
	SetRootComponent(MassWheelCostraint);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassWheelCostraint);

	AxleWheelCostraint = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelCostraint"));
	AxleWheelCostraint->SetupAttachment(Axle);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();

	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupConstraint();
}

void ASprungWheel::SetupConstraint()
{
	if (!GetAttachParentActor()) return;
	UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyRoot) return;
	MassWheelCostraint->SetConstrainedComponents(BodyRoot, NAME_None, Axle, NAME_None);
	AxleWheelCostraint->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);

}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->TickGroup == TG_PostPhysics)
	{
		TotalForceMagnitude = 0.f;
	}

}

void ASprungWheel::AddDrivingForce(float ForceMagnitude)
{
	TotalForceMagnitude += ForceMagnitude;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyForce();
}

void ASprungWheel::ApplyForce()
{
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceMagnitude);
}

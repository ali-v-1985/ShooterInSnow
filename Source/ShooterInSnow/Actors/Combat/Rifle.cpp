// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Sound/SoundBase.h"

ARifle::ARifle()
{
}

void ARifle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ARifle::BeginPlay()
{
    Super::BeginPlay();
}

void ARifle::Fire()
{
    if (HasAmmo() && IsCocked())
    {
        Super::Fire();
        RifleFire();
    }
}

void ARifle::RifleFire()
{
    UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
    UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
    FHitResult Hit;
    FVector Start, End;
    FRotator Rotation;
    const auto Controller = Cast<APawn>(GetOwner())->GetController();
    if(Controller == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("No controller"));
        return;
    }
    Controller->GetPlayerViewPoint(Start, Rotation);
    End = Start + Rotation.Vector() * FireRange;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);
    Params.AddIgnoredActor(GetOwner());
    const auto bSuccessHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End,
        ECC_GameTraceChannel1, Params);
    if(bSuccessHit)
    {
        const auto ShotDirection = -Rotation.Vector();
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, Hit.Location, ShotDirection.Rotation());
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), HitSound, Hit.Location, ShotDirection.Rotation());
        auto HitActor = Hit.GetActor();
        if (HitActor != nullptr)
        {
            FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
            HitActor->TakeDamage(Damage, DamageEvent, Controller, this);
        }
    }
}

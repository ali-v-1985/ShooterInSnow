// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"

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
    Super::Fire();
    UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
    FHitResult Hit;
    FVector Start;
    FVector End;
    FRotator Rotation;
    const auto Controller = Cast<APawn>(GetOwner())->GetController();

    Controller->GetPlayerViewPoint(Start, Rotation);
    End = Start + Rotation.Vector() * FireRange;
    const auto bSuccessHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel1);
    if(bSuccessHit)
    {
        const auto ShotDirection = -Rotation.Vector();
        // UE_LOG(LogTemp, Warning, TEXT("End : (%f, %f, %f)"), End.X, End.Y, End.Z);
        // UE_LOG(LogTemp, Warning, TEXT("Hit to : %s"), *Hit.GetActor()->GetName());
        // DrawDebugPoint(GetWorld(), Hit.Location, Caliber, FColor::Red, true);
        // // DrawDebugLine(GetWorld(), Start, Hit.Location, FColor::Red, true);
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitFlash, Hit.Location, ShotDirection.Rotation());
        UGameplayStatics::SpawnDecalAtLocation(GetWorld(), HitFlash, Hit.Location, ShotDirection.Rotation());
    
    }
}

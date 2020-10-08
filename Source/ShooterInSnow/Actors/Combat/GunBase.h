// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

class UParticleSystem;

UCLASS()
class SHOOTERINSNOW_API AGunBase : public AActor
{
    GENERATED_BODY()

public:
    AGunBase();
    
    virtual void Fire();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
    USkeletalMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, Category="Combat|Effects")
    UParticleSystem* MuzzleFlash;

    UPROPERTY(EditAnywhere, Category="Combat|Effects")
    UParticleSystem* HitFlash;

    UPROPERTY(EditAnywhere, Category=Combat)
    int32 MagazineCapacity;

    UPROPERTY(EditAnywhere, Category=Combat)
    int32 FireRate;
    
    UPROPERTY(EditAnywhere, Category=Combat)
    int32 FireRange;    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
    int32 Caliber;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
    USceneComponent* Root;

    void DrawDebugCam() const;
};

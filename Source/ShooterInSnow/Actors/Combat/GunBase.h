// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunBase.generated.h"

class UParticleSystem;
class USoundBase;

UCLASS()
class SHOOTERINSNOW_API AGunBase : public AActor
{
    GENERATED_BODY()

public:
    AGunBase();

    virtual void Fire();

    int32 GetFireRate() const;

    bool HasAmmo() const;
    
    int32 GetMagazineCapacity() const;
    
    bool IsMagazineFull() const;
    
    void Reload(int32 BulletCount);
    
    int32 GetAmmoLeft() const;

protected:

    virtual void BeginPlay() override;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components)
    USkeletalMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, Category="Combat|Effects")
    UParticleSystem* MuzzleFlash;

    UPROPERTY(EditAnywhere, Category="Combat|Effects")
    USoundBase* MuzzleSound;

    UPROPERTY(EditAnywhere, Category="Combat|Effects")
    UParticleSystem* HitFlash;

    UPROPERTY(EditAnywhere, Category="Combat|Effects")
    USoundBase* HitSound;

    UPROPERTY(EditAnywhere, Category="Combat|Effects")
    USoundBase* ReloadSound;

    UPROPERTY(EditAnywhere, Category=Combat)
    int32 MagazineCapacity;

    UPROPERTY(EditAnywhere, Category=Combat)
    int32 FireRate;
    
    UPROPERTY(EditAnywhere, Category=Combat)
    float FireRange;    

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
    float Caliber;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat", meta=(AllowPrivateAccess="true"))
    float Damage = 30;

    bool IsCocked() const;
    
private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Components, meta=(AllowPrivateAccess="true"))
    USceneComponent* Root;

    float LastShot = 0;

    float TimeToCock = 0;

    int32 AmmoLeft;
    
    void DrawDebugCam() const;
};

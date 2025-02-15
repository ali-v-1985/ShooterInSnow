﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AGunBase;

UCLASS()
class SHOOTERINSNOW_API AShooterCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AShooterCharacter();

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    virtual float TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
                             AActor* DamageCauser) override;

    UFUNCTION(BlueprintPure, Category=Health)
    float GetHealthPercent() const;

    UFUNCTION(BlueprintPure, Category=Health)
    bool IsDead() const;

    UFUNCTION(BlueprintPure, Category=Combat)
    int32 GetCarryingAmmo() const;

    UFUNCTION(BlueprintPure, Category=Combat)
    int32 GetGunAmmo() const;

    void PullTrigger();

    void ReloadGun();

    FVector GetPatrolEndLocation() const;

    AGunBase* GetWeaponInUse() const;

protected:
    void HideDefaultWeapon() const;
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Camera, meta=(AllowPrivateAccess="true"))
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Camera, meta=(AllowPrivateAccess="true"))
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, Category= Movement)
    float RotationRate = 10;

    UPROPERTY(EditAnywhere, Category= Camera)
    float ChangeHandSpeed = 10;

    UPROPERTY(EditAnywhere, Category= Camera)
    float MaxHealth = 100;

    UPROPERTY(EditAnywhere, Category= Combat)
    int32 CarriedAmmoAmount = 200;

    UPROPERTY(EditDefaultsOnly, Category= Combat, meta=(AllowPrivateAccess="true"))
    TArray<TSubclassOf<AGunBase>> WeaponInventory;

    UPROPERTY(EditDefaultsOnly, Category= Combat, meta=(AllowPrivateAccess="true"))
    TSubclassOf<AGunBase> WeaponOfChoice;

    UPROPERTY(EditAnywhere, Category="Combat|Patrol", meta=(AllowPrivateAccess="true"))
    FVector PatrolEndLocation;
    // TArray<AGunBase*> Weapons;

    AGunBase* WeaponInUse;

    bool ShouldChangeHand = false;

    float TargetSocketOffsetY;
    float TargetRelativeLocationY;

    float Health;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void LookUp(float Value);
    void LookRight(float Value);
    void ChangeHandDelegate();
    void ChangeHand();
    void ChangeSpringArmRelativeLocationY() const;
    void ChangeSpringArmSocketOffsetY() const;
    void SpawnWeapons();
    void UseChoseWeapon(AGunBase* Weapon);
};

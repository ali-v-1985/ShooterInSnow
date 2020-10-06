// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"

#include "Kismet/GameplayStatics.h"

ARifle::ARifle()
{
}

void ARifle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ARifle::Fire()
{
    UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, MuzzleFirePoint, TEXT("MuzzleFlashSocket"));
}

void ARifle::BeginPlay()
{
    Super::BeginPlay();
}

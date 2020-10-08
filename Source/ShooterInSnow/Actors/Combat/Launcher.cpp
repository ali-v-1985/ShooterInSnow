// Fill out your copyright notice in the Description page of Project Settings.


#include "Launcher.h"

ALauncher::ALauncher()
{
}

void ALauncher::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ALauncher::BeginPlay()
{
    Super::BeginPlay();
}

void ALauncher::Fire()
{
    Super::Fire();
    UE_LOG(LogTemp, Warning, TEXT("Fire by Launcher"));
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GunBase.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

// Sets default values

AGunBase::AGunBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGunBase::Fire()
{
	// DrawDebugCam();
}

int32 AGunBase::GetFireRate() const
{
	return FireRate;
}

void AGunBase::DrawDebugCam() const
{
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	const auto Controller = Cast<APawn>(GetOwner())->GetController();

	Controller->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	DrawDebugCamera(GetWorld(),
	                  ViewPointLocation, ViewPointRotation,
	                  90, 2, FColor::Red, true);
}

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

void AGunBase::BeginPlay()
{
	Super::BeginPlay();
	if (FireRate > 0)
	{
		TimeToCock = 60 / FireRate;
	}

	AmmoLeft = MagazineCapacity;
}

void AGunBase::Fire()
{
	LastShot = GetWorld()->GetTimeSeconds();
	if (AmmoLeft > 0)
	{
		AmmoLeft--;
	}
	// DrawDebugCam();
}

int32 AGunBase::GetFireRate() const
{
	return FireRate;
}

bool AGunBase::IsCocked() const
{
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	bool bIsCocked = true;
	if (LastShot != 0)
	{
		bIsCocked = CurrentTime - LastShot >= TimeToCock;
	}
	return bIsCocked;
}

bool AGunBase::HasAmmo() const
{
	return AmmoLeft > 0;
}

int32 AGunBase::GetMagazineCapacity() const
{
	return MagazineCapacity;
}

bool AGunBase::IsMagazineFull() const
{
	return AmmoLeft == MagazineCapacity;
}

void AGunBase::Reload(int32 BulletCount)
{
	UGameplayStatics::SpawnSoundAttached(ReloadSound, Mesh, TEXT("MuzzleFlashSocket"));
    const int BulletToReload = FMath::Min(BulletCount + AmmoLeft, MagazineCapacity);
	AmmoLeft = BulletToReload;
}

int32 AGunBase::GetAmmoLeft() const
{
	return AmmoLeft;
}

void AGunBase::DrawDebugCam() const
{
	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	const auto Controller = Cast<APawn>(GetOwner())->GetController();

	if(Controller == nullptr)
	{
		return;
	}
	Controller->GetPlayerViewPoint(ViewPointLocation, ViewPointRotation);
	DrawDebugCamera(GetWorld(),
	                  ViewPointLocation, ViewPointRotation,
	                  90, 2, FColor::Red, true);
}

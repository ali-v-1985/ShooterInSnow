// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "ShooterInSnow/Actors/Combat/GunBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterInSnow/GameModes/ShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArmComponent->SetupAttachment(RootComponent);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
    Super::BeginPlay();
    SpawnWeapons();
    HideDefaultWeapon();
    UseChoseWeapon(WeaponInUse);
    Health = MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    ChangeHand();
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AShooterCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &AShooterCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUp);
    PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRight);
    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AShooterCharacter::Jump);
    PlayerInputComponent->BindAction(TEXT("ChangeHand"), IE_Pressed, this, &AShooterCharacter::ChangeHandDelegate);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AShooterCharacter::PullTrigger);
}

float AShooterCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                    AActor* DamageCauser)
{
    auto DamageToApply = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
    DamageToApply = FMath::Min(Health, DamageToApply);
    Health -= DamageToApply;
    
    if(IsDead())
    {
        AShooterGameModeBase* ShooterGameModeBase = GetWorld()->GetAuthGameMode<AShooterGameModeBase>();
        if(ShooterGameModeBase == nullptr)
        {
            UE_LOG(LogTemp, Warning, TEXT("No game mode found of type ShooterGameModeBase"));
            return DamageToApply;
        }
        ShooterGameModeBase->PawnKilled(this);
        DetachFromControllerPendingDestroy();
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        
    }
    return DamageToApply;
}

float AShooterCharacter::GetHealthPercent() const
{
    return Health / MaxHealth;
}

bool AShooterCharacter::IsDead() const
{
    return Health <= 0.0;
}

void AShooterCharacter::PullTrigger()
{
    WeaponInUse->Fire();
}

FVector AShooterCharacter::GetPatrolEndLocation() const
{
    return PatrolEndLocation;
}

AGunBase* AShooterCharacter::GetWeaponInUse() const
{
    return WeaponInUse;
}

void AShooterCharacter::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector() * Value);
}

void AShooterCharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector() * Value);
}

void AShooterCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRight(float Value)
{
    AddControllerYawInput(Value * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::ChangeHandDelegate()
{
    ShouldChangeHand = true;

    TargetRelativeLocationY = SpringArmComponent->GetRelativeLocation().Y * -1;
    TargetSocketOffsetY = SpringArmComponent->SocketOffset.Y * -1;
}

void AShooterCharacter::ChangeHand()
{
    if (SpringArmComponent && ShouldChangeHand)
    {
        ChangeSpringArmRelativeLocationY();

        ChangeSpringArmSocketOffsetY();

        if(FMath::IsNearlyEqual(SpringArmComponent->GetRelativeLocation().Y, TargetRelativeLocationY, 1.0f) 
            && FMath::IsNearlyEqual(SpringArmComponent->SocketOffset.Y, TargetSocketOffsetY, 1.0f))
        {
            ShouldChangeHand = false;
            auto RelativeLocation = SpringArmComponent->GetRelativeLocation();
            RelativeLocation.Y = TargetRelativeLocationY;
            SpringArmComponent->SetRelativeLocation(RelativeLocation);
            SpringArmComponent->SocketOffset.Y = TargetSocketOffsetY;
        }
    }
}

void AShooterCharacter::ChangeSpringArmRelativeLocationY() const
{
    auto SpringArmRelativeLocation = SpringArmComponent->GetRelativeLocation();
    const auto CurrentSpringArmLocationY = FMath::FInterpTo(SpringArmRelativeLocation.Y,
                                                            TargetRelativeLocationY, GetWorld()->GetDeltaSeconds(),
                                                            ChangeHandSpeed);

    SpringArmRelativeLocation.Y = CurrentSpringArmLocationY;
    SpringArmComponent->SetRelativeLocation(SpringArmRelativeLocation);
}

void AShooterCharacter::ChangeSpringArmSocketOffsetY() const
{
    auto SocketOffset = SpringArmComponent->SocketOffset;
    const auto CurrentSpringArmSocketOffsetY = FMath::FInterpTo(SocketOffset.Y,
                                                                TargetSocketOffsetY,
                                                                GetWorld()->GetDeltaSeconds(),
                                                                ChangeHandSpeed);

    SocketOffset.Y = CurrentSpringArmSocketOffsetY;
    SpringArmComponent->SocketOffset = SocketOffset;
}

void AShooterCharacter::SpawnWeapons()
{
    for(auto WeaponType : WeaponInventory)
    {
        const auto Weapon = GetWorld()->SpawnActor<AGunBase>(WeaponType);
        if (WeaponOfChoice == WeaponType)
        {
            WeaponInUse = Weapon;
        }
    }
}

void AShooterCharacter::UseChoseWeapon(AGunBase* Weapon)
{
    Weapon->AttachToComponent(GetMesh(),
                                   FAttachmentTransformRules::KeepRelativeTransform,
                                   TEXT("WeaponSocket"));
    Weapon->SetOwner(this);
}

void AShooterCharacter::HideDefaultWeapon() const
{
    GetMesh()->HideBoneByName(TEXT("weapon_r"), PBO_None);
}
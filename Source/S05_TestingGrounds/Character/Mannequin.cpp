// Fill out your copyright notice in the Description page of Project Settings.

#include "Mannequin.h"
#include "S05_TestingGrounds.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "../Weapons/Gun.h"


// Sets default values
AMannequin::AMannequin()
{
	PrimaryActorTick.bCanEverTick = true;
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(
		TEXT("FirstPersonCamera")
	);
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(
		-39.56f, 1.75f, 64.f // Position the camera
	);
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
	// Create a mesh component that will be used when being viewed from a
	// '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(
		TEXT("CharacterMesh1P")
	);
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	if (GunBlueprint == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing."));
		return;
	}
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	Gun->AttachToComponent( // attach gun mesh component
		Mesh1P,
		FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true),
		TEXT("GripPoint")
	);
	Gun->AnimInstance = Mesh1P->GetAnimInstance();

	/** Additional Instructions for v4.18 */
	// https://community.gamedev.tv/t/additional-instructions-for-later-versions-of-unreal/49212

	/** CURRENT REPO CODE */
	/*if (GunBlueprint == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Gun blueprint missing."));
		return;
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);

	//Attach gun mesh component to Skeleton, doing it here because the skelton is not yet created in the constructor
	if (IsPlayerControlled())
	{
		Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	}
	else
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_0"));
	}

	Gun->AnimInstance1P = Mesh1P->GetAnimInstance();
	Gun->AnimInstance3P = GetMesh()->GetAnimInstance();

	if (InputComponent != nullptr) {
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequin::PullTrigger);
	}*/
}

// Called every frame
void AMannequin::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMannequin::SetupPlayerInputComponent
(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMannequin::Fire()
{
	// TODO: Input to fire bug--mouse click never calls Fire method
	UE_LOG(LogTemp, Warning, TEXT("Fire method called."));
	Gun->OnFire();
}


/** REPO CODE */
/*void AMannequin::UnPossessed() {
	Super::UnPossessed();
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_0"));
}

void AMannequin::PullTrigger()
{
	Gun->OnFire();
}*/
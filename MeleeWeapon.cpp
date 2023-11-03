

#include "Weapons/MeleeWeapon.h"
#include "Components/BoxComponent.h"
#include "Components/CombatComponent.h"
#include "Player/AOSCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Sound/SoundCue.h"
#include "AdventureOfShinbi/AdventureOfShinbi.h"

AMeleeWeapon::AMeleeWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void AMeleeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	WeaponCapsuleTrace();
}

bool AMeleeWeapon::WeaponCapsuleTrace()
{
	if (bActivateWeaponTrace == false)
		return false;

	// 캡슐 트레이스로 적중한 FHitResult 배열 받아오기
	TArray<FHitResult> WeaponHitResults;
	const bool bHitSomething = GetCapsuleTraceHitResult(WeaponHitResults);

	if (bHitSomething == false)
		return false;

	if (WeaponOwner == nullptr)
	{
		WeaponOwner = Cast<AAOSCharacter>(GetOwner());
	}
	
	// 적중한 캐릭터에 데미지 적용 및 이펙트 재생
	TArray<AActor*> HitEnemies;
	for (FHitResult Result : WeaponHitResults)
	{
		if (Result.GetActor() == nullptr)
			continue;

		if (HitEnemies.Contains(Result.GetActor()) == false)
		{
			HitEnemies.Add(Result.GetActor());

			PlayAttackEffect(Result.ImpactPoint, Result.ImpactNormal.Rotation());

			AAOSCharacter* AC = Cast<AAOSCharacter>(GetOwner());
			if (AC)
			{
				Damage = AC->GetCombatComp()->GetDmgDebuffActivated() ? Damage * 0.7 : Damage;
			}

			UGameplayStatics::ApplyPointDamage
			(
				Result.GetActor(),
				Damage,
				Result.ImpactPoint,
				Result,
				WeaponOwner->GetController(),
				WeaponOwner,
				UDamageType::StaticClass()
			);

			if (CameraShakeHitImpact)
			{
				GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(CameraShakeHitImpact);
			}
		}
	}

	DeactivateWeaponTrace();

	return true;
}

bool AMeleeWeapon::GetCapsuleTraceHitResult(TArray<FHitResult>& HitResults)
{
	const USkeletalMeshSocket* WeaponTraceStart = ItemMesh->GetSocketByName("WeaponTraceStart");
	if (WeaponTraceStart == nullptr) 
		return false;

	const USkeletalMeshSocket* WeaponTraceEnd = ItemMesh->GetSocketByName("WeaponTraceEnd");
	if (WeaponTraceEnd == nullptr) 
		return false;

	UCollisionProfile* Profile = UCollisionProfile::Get();
	ETraceTypeQuery TraceType = Profile->ConvertToTraceType(ECC_PlayerWeaponTrace);

	const bool bHitSomething = UKismetSystemLibrary::CapsuleTraceMulti
	(
		this,
		WeaponTraceStart->GetSocketTransform(ItemMesh).GetLocation(),
		WeaponTraceEnd->GetSocketTransform(ItemMesh).GetLocation(),
		CapsuleRadius,
		CapsuleHalfHeight,
		TraceType,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResults,
		true
	);

	return bHitSomething;
}

void AMeleeWeapon::PlayAttackEffect(const FVector& Location, const FRotator& Rotation)
{
	if (ImpactParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, Location, Rotation);
	}
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, Location);
	}
}

void AMeleeWeapon::ActivateWeaponTrace()
{
	bActivateWeaponTrace = true;
}

void AMeleeWeapon::DeactivateWeaponTrace()
{
	bActivateWeaponTrace = false;
}
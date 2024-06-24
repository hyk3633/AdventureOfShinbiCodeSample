
#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "MeleeWeapon.generated.h"

/**
 * ���� ���� Ŭ����
 */

class UParticleSystem;
class USoundCue;

UCLASS()
class ADVENTUREOFSHINBI_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:

	AMeleeWeapon();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	/** ������ ĸ�� Ʈ���̽� ����� ���� ������ ���� �� ȿ�� ��� */
	virtual bool WeaponCapsuleTrace();

	/** ĸ�� Ʈ���̽� �˻� �� HitResult�� ���� */
	bool GetCapsuleTraceHitResult(TArray<FHitResult>& HitResults);

	void PlayAttackEffect(const FVector& Location, const FRotator& Rotation);

protected:

	/** ������ Ÿ�� ������ �����ϴ� ĸ�� Ʈ���̽��� ������ */
	float CapsuleRadius = 0.f;

	/** ������ Ÿ�� ������ �����ϴ� ĸ�� Ʈ���̽��� �߽ɿ��� ĸ�� �� �κ� ������ �Ÿ� */
	float CapsuleHalfHeight = 0.f;

	UPROPERTY(EditDefaultsOnly, Category = "Melee Weapon")
	UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Melee Weapon")
	USoundCue* ImpactSound;

	UPROPERTY(EditDefaultsOnly, Category = "Melee Weapon")
	TSubclassOf<UCameraShakeBase> CameraShakeHitImpact;

private:

	/** ������ ĸ�� Ʈ���̽��� Ȱ��ȭ */
	bool bActivateWeaponTrace = false;

public:

	void ActivateWeaponTrace();
	void DeactivateWeaponTrace();

};

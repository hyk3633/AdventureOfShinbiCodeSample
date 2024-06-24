
#pragma once

#include "CoreMinimal.h"
#include "Weapons/Weapon.h"
#include "Types/AmmoType.h"
#include "Types/WeaponType.h"
#include "RangedWeapon.generated.h"

/**
 * ���Ÿ� ����
 */

class AItemAmmo;
class USoundCue;
class UTexture2D;

// ũ�ν���� ����ü
USTRUCT(BlueprintType)
struct FCrosshairs
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Crosshairs")
	UTexture2D* CrosshairCenter;

	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Crosshairs")
	UTexture2D* CrosshairLeft;

	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Crosshairs")
	UTexture2D* CrosshairRight;

	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Crosshairs")
	UTexture2D* CrosshairTop;

	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Crosshairs")
	UTexture2D* CrosshairBottom;

};

UCLASS()
class ADVENTUREOFSHINBI_API ARangedWeapon : public AWeapon
{
	GENERATED_BODY()
	
public:

	ARangedWeapon();

	/** �߻� �Լ� */
	virtual void Firing();

protected:

	virtual void BeginPlay() override;

	/** ȭ�� ���߾ӿ��� ���� Ʈ���̽� ���� */
	void CrosshairLineTrace(FVector& OutHit);

	void PlayFireEffect(UParticleSystem* Particle, USoundCue* Sound);

protected:

	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Effect")
	UParticleSystem* MuzzleFlashParticle;

	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Effect")
	USoundCue* FireSound;

	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Effect")
	TSubclassOf<UCameraShakeBase> CameraShakeGunFire;

	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Effect")
	USoundCue* NoAmmoSound;

	/** �ڵ� �߻� ���� */
	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Status")
	bool bAutomaticFire = false;

	/** ����� */
	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Status", meta = (ClampMin = "0.0", ClampMax = "5.0", EditCondition = "bAutomaticFire"))
	float FireRate = 1.f;

	/** �ѱ� �ݵ� */
	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Status", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float GunRecoil = 0.35f;

private:

	UPROPERTY()
	AItem* AmmoItem;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AItem> AmmoClass;

	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Crosshairs")
	FCrosshairs Crosshairs;

protected:

	/** ������ ź�� ���� */
	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Info")
	EAmmoType AmmoType = EAmmoType::EAT_MAX;

	/** ������ �� Ȯ�� ���� */
	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Info", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float ZoomScope = 30.f;

	/** źâ�� ź�෮ */
	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Info" , meta = (ClampMin = "1", ClampMax = "1000"))
	int32 Magazine = 30;
	
	/** ������ ź�෮ */
	UPROPERTY(VisibleAnywhere, Category = "Ranged Weapon | Info")
	int32 LoadedAmmo = 0;

	/** ź�� �Ҹ� */
	UPROPERTY(EditAnywhere, Category = "Ranged Weapon | Info")
	int32 AmmoConsumption = 1;

public:

	AItem* GetAmmoItem() const;
	EAmmoType GetAmmoType() const;
	int32 GetMagazine() const;
	int32 GetLoadedAmmo() const;
	void SetLoadedAmmo(const int32 Quantity);
	float GetGunRecoil() const;
	bool GetAutomaticFire() const;
	float GetFireRate() const;
	float GetZoomScope() const;
	void ConsumeAmmo();
	void PlayNoAmmoSound();
	FCrosshairs GetCrosshairs() const;
};

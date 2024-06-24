
#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Types/WeaponType.h"
#include "Types/WeaponState.h"
#include "Weapon.generated.h"

/**
* ���� ������ �⺻ Ŭ����
*/

class AAOSCharacter;
class UBoxComponent;
class USoundCue;

UCLASS()
class ADVENTUREOFSHINBI_API AWeapon : public AItem
{
	GENERATED_BODY()

public:

	AWeapon();

	/** ȹ�� ȿ�� ��� �Լ� */
	virtual void PlayGainEffect();

	/** ���� ���� ���� */
	virtual void SetWeaponState(const EWeaponState State);

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	
	UPROPERTY()
	AAOSCharacter* WeaponOwner;

	UPROPERTY(EditAnywhere)
	float Damage = 20.f;

	/** ���� ���� enum class ���� */
	UPROPERTY(VisibleAnywhere)
	EWeaponState WeaponState = EWeaponState::EWS_MAX;

	/** ���� ���� enum class ���� */
	UPROPERTY(EditAnywhere, Category = "Weapon")
	EWeaponType WeaponType = EWeaponType::EWT_MAX;

private:

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USoundCue* PickAndEquipSound;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USoundCue* DropSound;

public:

	EWeaponType GetWeaponType() const;
	EWeaponState GetWeaponState() const;

	/** ĳ���� ��� �� ���� �޽��� ĳ���� �տ��� ����Ʈ������ ���� �޽��� �浹, ���� ���� ���� */
	void DropWeapon();
};

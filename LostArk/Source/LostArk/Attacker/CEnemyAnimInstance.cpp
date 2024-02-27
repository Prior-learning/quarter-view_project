#include "CEnemyAnimInstance.h"
#include "../Global.h"
#include "GameFramework/Character.h"

void UCEnemyAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OwnerCharacter = Cast<ACharacter>(TryGetPawnOwner());
}

void UCEnemyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{

	CheckNull(OwnerCharacter);
	Super::NativeUpdateAnimation(DeltaSeconds);

	Speed = OwnerCharacter->GetVelocity().Size2D();
	Direction = CalculateDirection(OwnerCharacter->GetVelocity(), OwnerCharacter->GetControlRotation());
	Pitch = OwnerCharacter->GetBaseAimRotation().Pitch;
}

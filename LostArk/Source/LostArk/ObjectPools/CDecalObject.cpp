#include "CDecalObject.h"
#include "Components/DecalComponent.h"
#include "CParticleManager.h"
#include "../UParticlePooling.h"


ACDecalObject::ACDecalObject()
{
   
}

void ACDecalObject::SetDecalInfo(FDecalInfo& info)
{
    mInfo = info;
    SetActorLocation(info.location);


    SetActorRotation(FQuat(info.direction));
    ShowDecal();
}
void ACDecalObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACDecalObject::SpawnParticle()
{
    ensureMsgf(mInfo.mImpact != nullptr, TEXT("Decal has not ParticleSystem"));
    if (!!mInfo.mImpact)
    {
        Fdir = GetActorForwardVector().GetSafeNormal2D();
        Rdir = GetActorRightVector().GetSafeNormal2D();

        switch (mInfo.shape)
        {
        case EDecalShape::Circle:
            CircleParticle();
            break;

        case EDecalShape::Triangle:
            AUParticlePooling *particle = ACParticleManager::Get().GetParticle();
            particle->SetActorLocation(GetActorLocation());
            particle->SetParticle(mInfo.mImpact);

            TriangleParticle(GetActorLocation(), 3);
            particle->SetPower(mInfo.mDamage);
            break;
        }
       
    }
}

void ACDecalObject::CircleParticle()
{
    int AngleAxis = 0;
    float distance = 256.f * mInfo.circum - 80.f; // 파티클의 중심이 원 살짝 안이여야 함.
    AUParticlePooling *particle;

    // prevent number from growind indefinitely

    while(AngleAxis != 360)
    {
        AngleAxis += 30;
        FVector location = GetActorLocation();
        FVector RotateValue = GetActorLocation().RotateAngleAxis(AngleAxis, FVector(0, 0, 1));
        RotateValue = RotateValue.GetSafeNormal2D() * distance;
        location.X += RotateValue.X; 
        location.Y += RotateValue.Y;
        //location.Z += RotateValue.Z;

        particle = ACParticleManager::Get().GetParticle();

        particle->SetActorScale3D(mInfo.mParticleScale);
        particle->SetActorLocation(location);
        particle->SetParticle(mInfo.mImpact);
        particle->SetPower(mInfo.mDamage);
    }
}

void ACDecalObject::TriangleParticle(FVector loc, int level)
{
    level--;
    if (level == 0)
        return;

    FVector location = loc;
    AUParticlePooling *particle;

    location += Fdir * 256.f / 2.f * mInfo.circum;
    // left
    {
        location += Rdir * 100.f;
        particle = ACParticleManager::Get().GetParticle();

        particle->SetActorLocation(location);
        particle->SetParticle(mInfo.mImpact);
        TriangleParticle(location, level);
    }
    //Right
    {
        location -= Rdir * 100.f * 2;
        particle = ACParticleManager::Get().GetParticle();

        particle->SetActorLocation(location);
        particle->SetParticle(mInfo.mImpact);
        TriangleParticle(location, level);
    }
   
}

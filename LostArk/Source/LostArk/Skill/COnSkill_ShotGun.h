#pragma once

#include "CoreMinimal.h"
#include "COnSkill.h"
#include "COnSkill_ShotGun.generated.h"


UCLASS()
class LOSTARK_API ACOnSkill_ShotGun : public ACOnSkill
{
	GENERATED_BODY()
  public:
    virtual void OnSkill() override;
    virtual void Begin_OnSkill() override;
    virtual void End_OnSkill() override;
    virtual void Trigger() override;


  protected:
    virtual void BeginPlay() override;

  public:
    virtual void Tick(float DeltaTime) override;

  private:
    float CoolTime;
    bool IsCoolDown;
};

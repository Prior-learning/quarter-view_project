#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "../Skill/CSkillData.h"
#include "CPSkillComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnSlotInfoChanged, int32); // 델리게이트 추가

UENUM(BlueprintType)
enum class ESkillButton : uint8
{
    F,
    E,
    Q,
    R,
    T,
    Max
};

USTRUCT(BlueprintType)
struct FSlotInfo
{
    GENERATED_BODY()

 public:
   bool bInCoolDown;
   float CoolTime;

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCPSkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCPSkillComponent();
  
  UFUNCTION(BlueprintCallable)
  UCSkillData* GetData(int a) {return Datas[a];}

  UFUNCTION(BlueprintCallable)
  ACOnSkill* GetSkill(int a) {return OnSkills[a];}

  UFUNCTION(BlueprintCallable)
  FSlotInfo GetInfo(int a){return SlotInfo[a]; }

  int GetSkillType()  {return CurrentSkilltype; }

  public:
  void OnFSkillUsed();
  void OnESkillUsed();
  void OnQSkillUsed();
  void OnRSkillUsed();
  void OnTSkillUsed();


    FOnSlotInfoChanged OnSlotInfoChanged;


protected:
	virtual void BeginPlay() override;
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
    void OnSkill(ESkillButton InButton);
protected:
  UPROPERTY(EditDefaultsOnly)
  class UCSkillData *Datas[(int32)ESkill_Type::Max];

  UPROPERTY(EditDefaultsOnly)
  class ACOnSkill *OnSkills[(int32)ESkill_Type::Max];

  UPROPERTY(EditDefaultsOnly)
  FSlotInfo SlotInfo[(int32)ESkill_Type::Max];

private:
  TMap<ESkillButton, ESkill_Type> SkillBind;
  int CurrentSkilltype;
};

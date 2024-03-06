#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "CMontageComponent.generated.h"

//
UENUM()
enum class EMontage_State : uint16
{
    Attack,
    Hitted,
    Roll,
    Reload,
    Dead,
    Max
};
USTRUCT(BlueprintType)
struct FMontageData : public FTableRowBase
{
    GENERATED_BODY()

  public:
    UPROPERTY(EditAnywhere)
    EMontage_State Type;

    UPROPERTY(EditAnywhere)
    class UAnimMontage *AnimMontage;

    UPROPERTY(EditAnywhere)
    float PlayRatio = 1.0f;

    UPROPERTY(EditAnywhere)
    FName StartSection;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTARK_API UCMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCMontageComponent();

protected:
	virtual void BeginPlay() override;

private:
    void PlayAnimMontage(EMontage_State InState);

protected:
    
    UPROPERTY(EditDefaultsOnly, Category = "DataTable")
    UDataTable *DataTable;

   	FMontageData *Datas[(int16)EMontage_State::Max];


		
};

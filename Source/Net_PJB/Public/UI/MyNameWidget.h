#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "MyNameWidget.generated.h"

UCLASS()
class NET_PJB_API UMyNameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	void SetPlayerStateInfo(class AMyPlayerState* InPS);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> NameText;
};

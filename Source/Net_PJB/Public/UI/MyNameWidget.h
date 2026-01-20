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

	UFUNCTION()
	void SetPlayerStateInfo(class AMyPlayerState* InPS);
	
	UFUNCTION()
	void UpdateNameText(const FString& NewName);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> NameText;
};

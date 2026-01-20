#include "UI/MyNameWidget.h"

#include "Components/TextBlock.h"

#include "GameFramework/PlayerState.h"
#include "Core/MyPlayerState.h"

void UMyNameWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMyNameWidget::SetPlayerStateInfo(AMyPlayerState* InPS)
{
	if (!InPS)
	{
		return;
	}
	NameText->SetText(FText::FromString(InPS->GetMyName()));

	if (!InPS->OnNameChangedDel.IsAlreadyBound(this, &UMyNameWidget::UpdateNameText))
	{
		InPS->OnNameChangedDel.AddDynamic(this, &UMyNameWidget::UpdateNameText);
	}
}

void UMyNameWidget::UpdateNameText(const FString& NewName)
{
	NameText->SetText(FText::FromString(NewName));
}
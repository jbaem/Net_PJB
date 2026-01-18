#include "UI/MyNameWidget.h"

#include "Components/TextBlock.h"

#include "GameFramework/PlayerState.h"
#include "Core/MyPlayerState.h"

void UMyNameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (AMyPlayerState* PS = Cast<AMyPlayerState>(GetOwningPlayerState()))
	{
		NameText->SetText(FText::FromString(PS->GetMyName()));
	}
}

void UMyNameWidget::SetPlayerStateInfo(AMyPlayerState* InPS)
{
	if (!InPS)
	{
		return;
	}
	NameText->SetText(FText::FromString(InPS->GetMyName()));
}

#include "UI/MyNameWidget.h"

#include "Components/TextBlock.h"

#include "GameFramework/PlayerState.h"
#include "Core/MyPlayerState.h"


void UMyNameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (APlayerState* PS = GetOwningPlayerState())
	{
		NameText->SetText(FText::FromString(PS->GetPlayerName()));
	}
}

void UMyNameWidget::SetPlayerStateInfo(AMyPlayerState* InPS)
{
	if (!InPS)
	{
		return;
	}

	NameText->SetText(FText::FromString(InPS->GetPlayerName()));
}

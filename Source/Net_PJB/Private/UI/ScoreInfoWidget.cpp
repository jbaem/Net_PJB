#include "UI/ScoreInfoWidget.h"

#include "Components/TextBlock.h"

void UScoreInfoWidget::UpdateName(const FString& InName)
{
	Name->SetText(FText::FromString(InName));
}

void UScoreInfoWidget::UpdateScore(int32 InScore)
{
	Score->SetText(FText::AsNumber(InScore));
}

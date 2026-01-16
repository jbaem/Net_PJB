#include "UI/MyHUD.h"

#include "Blueprint/UserWidget.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();

	InitMainWidget();

}

void AMyHUD::InitMainWidget()
{
	if (MainWidgetClass)
	{
		MainWidget = CreateWidget<UUserWidget>(GetWorld(), MainWidgetClass);
		if (MainWidget)
		{
			MainWidget->AddToViewport();
		}
	}
}

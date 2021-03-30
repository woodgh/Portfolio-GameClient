#include "GameClientGameModeBase.h"
#include "MainController.h"
#include "MainHUD.h"
#include "Dummy.h"

AGameClientGameModeBase::AGameClientGameModeBase()
{
	DefaultPawnClass = ADummy::StaticClass();
	PlayerControllerClass = AMainController::StaticClass();
	HUDClass = UMainHUD::StaticClass();
}
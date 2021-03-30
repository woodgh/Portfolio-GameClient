#pragma once
#include "GameClient.h"
#include "GameFramework/GameModeBase.h"
#include "GameClientGameModeBase.generated.h"

UCLASS()
class GAMECLIENT_API AGameClientGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AGameClientGameModeBase();
};

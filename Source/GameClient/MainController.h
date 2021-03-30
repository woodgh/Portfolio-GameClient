#pragma once
#include "GameClient.h"
#include "GameFramework/PlayerController.h"
#include "MainController.generated.h"

UCLASS()
class GAMECLIENT_API AMainController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainController();

public:
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

public:
	bool OnDelivery(class NetPlay::Packet* Packet);

private:
	bool ResDummyInfo(class NetPlay::Packet* Packet);

	bool ZoneInfo(class NetPlay::Packet* Packet);

	bool InSight(class NetPlay::Packet* Packet);

	bool OutOfSight(class NetPlay::Packet* Packet);

	bool OnTargetLocation(class NetPlay::Packet* Packet);

	bool OnChat(class NetPlay::Packet* Packet);

	void ChatMode(void);

private:
	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

private:
	UPROPERTY(VisibleAnywhere)
	TSubclassOf< class UMainHUD > ui_;

	UPROPERTY(VisibleAnywhere)
	TSubclassOf< class UChat > chat_;

private:
	TUniquePtr< class FNetClient > client_;

	TMap< int, class ADummy* > dummyGroup_;

	class UMainHUD* hud_ = nullptr;
};

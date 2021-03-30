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
	// 프로토콜 파싱하기
	bool OnDelivery(class NetPlay::Packet* Packet);

private:
	// 더미 정보 받기
	bool ResDummyInfo(class NetPlay::Packet* Packet);

	// 시야에 들어옴
	bool InSight(class NetPlay::Packet* Packet);

	// 시야에 멀어짐
	bool OutOfSight(class NetPlay::Packet* Packet);

	// 채팅
	bool OnChat(class NetPlay::Packet* Packet);

	// 채팅모드 (UI)
	void ChatMode(void);

private:
	// 채팅 메세지 입력 완료 처리
	UFUNCTION()
	void OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

private:
	UPROPERTY(VisibleAnywhere)
	TSubclassOf< class UMainHUD > ui_;		// HUD UI

	UPROPERTY(VisibleAnywhere)
	TSubclassOf< class UChat > chat_;		// 채팅 UI

private:
	TUniquePtr< class FNetClient > client_;	// 클라이언트 객체

	TMap< int, class ADummy* > dummyGroup_;	// 시야에 들어온 목록

	class UMainHUD* hud_ = nullptr;			// HUD 객체
};

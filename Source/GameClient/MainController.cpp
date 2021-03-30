#include "MainController.h"
#include "MainHUD.h"
#include "Chat.h"
#include "ChatMsg.h"
#include "Dummy.h"
#include "Kismet/GameplayStatics.h"

AMainController::AMainController()
	: client_(new FNetClient)
{
	PrimaryActorTick.bCanEverTick = true;

	// HUD 
	static ConstructorHelpers::FClassFinder< UUserWidget > UI(
		TEXT("WidgetBlueprint'/Game/UI/MainHUD.MainHUD_C'")
	);

	if (UI.Succeeded())
		ui_ = UI.Class;

	// 채팅
	static ConstructorHelpers::FClassFinder< UUserWidget > CHAT(
		TEXT("WidgetBlueprint'/Game/UI/Chat.Chat_C'")
	);

	if (CHAT.Succeeded())
		chat_ = CHAT.Class;
}

void AMainController::SetupInputComponent()
{
	// 채팅 모드 전환 초기화
	Super::SetupInputComponent();

	if (InputComponent)
		InputComponent->BindAction("ChatMode", IE_Pressed, this, &AMainController::ChatMode);
}

void AMainController::BeginPlay()
{
	Super::BeginPlay();

	// HUD UI 초기화
	if (ui_)
		hud_ = CreateWidget< UMainHUD >(this, ui_);

	if (hud_)
	{
		hud_->AddToViewport();

		UMainHUD::FTextCommitted Delegate;
		Delegate.AddDynamic(this, &AMainController::OnTextCommitted);
		
		hud_->SetTextCommitted(Delegate);
	}

	// 클라이언트 생성 및 접속 하기
	if (client_->Connect(TEXT("127.0.0.1"), 20000, this, &AMainController::OnDelivery) == false)
		UE_LOG(LogTemp, Error, TEXT("Failed to NetClient::Connect"));

	// 접속 후 서버에 초기 더미 정보 보내기
	ADummy* Dummy = Cast< ADummy >(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (Dummy == nullptr)
		return;

	NetPlay::Packet* Packet = nullptr;

	if (NetPlay::CreatePacket(&Packet) == false)
		return;

	*Packet
		<< Protocol::ReqDummyInfo
		<< Dummy->GetPlayable();

	if (client_->Send(Packet) == false)
		return;
}

void AMainController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 클라이언트 종료하기
	if (client_->Shutdown() == false)
		UE_LOG(LogTemp, Error, TEXT("Failed to NetClient::Shutdown"));

	Super::EndPlay(EndPlayReason);
}

void AMainController::Tick(float DeltaTime)
{
	// 클라이언트 업데이트
	client_->Update();

	// 위치 보내기
	ADummy* Dummy = Cast< ADummy >(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (Dummy == nullptr)
		return;

	if (Dummy->GetIndex() <= 0)
		return;

	FVector Location = Dummy->GetActorLocation();
	FVector Rotation = Dummy->GetActorRotation().Vector();
	FVector Velocity = Dummy->GetVelocity();

	if (hud_)
		hud_->SetActorInfo(Location, Rotation, Velocity, DeltaTime);
		
	NetPlay::Packet* SendPacket = nullptr;

	if (NetPlay::CreatePacket(&SendPacket) == false)
		return;

	*SendPacket
		<< Protocol::MoveToLocation
		<< Dummy->GetIndex()
		<< Location.X
		<< Location.Y
		<< Location.Z
		<< Rotation.X
		<< Rotation.Y
		<< Rotation.Z
		<< Velocity.X
		<< Velocity.Y
		<< Velocity.Z;

	if (client_->Send(SendPacket) == false)
		return;
}

bool AMainController::OnDelivery(NetPlay::Packet* Packet)
{
	// 프로토콜 파싱하기
	if (Packet == nullptr)
		return false;

	Protocol ProtoType = Protocol::Unknown;

	if (Packet->Read(&ProtoType) == false)
		return false;

	bool Result = false;

	switch (ProtoType)
	{
	case Protocol::ResDummyInfo:		// 더미 정보 받기
		Result = ResDummyInfo(Packet);
		break;

	case Protocol::InSight:				// 시야에 들어옴
		Result = InSight(Packet);
		break;

	case Protocol::OutOfSight:			// 시야에 멀어짐
		Result = OutOfSight(Packet);
		break;

	case Protocol::Chat:				// 채팅
		Result = OnChat(Packet);
		break;
	}

	if (Result == false)
		UE_LOG(LogTemp, Error, TEXT("Unknwon Protocol: %d"), ProtoType);

	return Result;
}

bool AMainController::ResDummyInfo(NetPlay::Packet* Packet)
{
	// 더미 정보 받기
	if (Packet == nullptr)
		return false;

	ADummy* Dummy = Cast< ADummy >(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (Dummy == nullptr)
		return false;

	int Index = 0;
	FVector Location;

	*Packet
		>> &Index
		>> &Location.X
		>> &Location.Y
		>> &Location.Z;

	Dummy->SetIndex(Index);
	Dummy->SetActorLocation(Location);

	return true;
}

bool AMainController::InSight(NetPlay::Packet* Packet)
{
	// 시야에 들어옴
	if (Packet == nullptr)
		return false;

	if (Packet == nullptr)
		return false;

	unsigned long Length = 0;

	while (Packet->ReadableBytes(Length))
	{
		int32 Index = 0;

		if (Packet->Read(&Index) == false)
			continue;

		bool Playable = false;

		if (Packet->Read(&Playable) == false)
			continue;

		FVector Location, Rotation, Velocity, TargetLocation;

		*Packet
			>> &Location.X
			>> &Location.Y
			>> &Location.Z
			>> &Rotation.X
			>> &Rotation.Y
			>> &Rotation.Z;

		ADummy* Dummy = nullptr;

		if (dummyGroup_.Contains(Index) == false)
		{
			// 시야 목록에 없으면 더미 생성하기
			Dummy = dummyGroup_.Add(Index, GetWorld()->SpawnActor< ADummy >(ADummy::StaticClass(), Location, Rotation.Rotation()));
			Dummy->SetIndex(Index);
			Dummy->SetPlayable(Playable);
			Dummy->SpawnDefaultController();
			Dummy->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
		}
		else
		{
			// 시야에 있으면 해당 더미 가져오기
			Dummy = dummyGroup_[Index];
		}

		// 더미 정보 업데이트
		if (Playable)
		{
			*Packet
				>> &Velocity.X
				>> &Velocity.Y
				>> &Velocity.Z;

			Dummy->MoveToActor(Location, Rotation, Velocity);
		}
		else
		{
			*Packet
				>> &TargetLocation.X
				>> &TargetLocation.Y
				>> &TargetLocation.Z;

			Dummy->MoveToLocation(Location, TargetLocation);
		}
	}

	return true;
}

bool AMainController::OutOfSight(NetPlay::Packet* Packet)
{
	// 시야에 멀어짐
	if (Packet == nullptr)
		return false;

	unsigned long Length = 0;

	while (Packet->ReadableBytes(Length))
	{
		int Index = 0;

		*Packet
			>> &Index;

		if (dummyGroup_.Contains(Index) == false)
			continue;

		ADummy* Dummy = dummyGroup_[Index];

		if (Dummy == nullptr)
			continue;

		if (dummyGroup_.Remove(Index) != 0)
			Dummy->Destroy();
	}

	return true;
}

bool AMainController::OnChat(class NetPlay::Packet* Packet)
{
	// 채팅
	if (Packet == nullptr)
		return false;
	
	int32 Index = 0;
	int32 Len = 0;
	char Msg[MaxChatLength] = { 0, };

	*Packet
		>> &Index
		>> &Len;

	if (Packet->Read(Msg, Len) == false)
		return false;
	
	UChatMsg* Chat = NewObject< UChatMsg >(this);

	if (Chat)
	{
		Chat->SetIndex(Index);
		Chat->SetMsg(UTF8_TO_TCHAR(Msg));

		hud_->AddChat(Chat);
	}
	
	return true;
}

void AMainController::ChatMode(void)
{
	// 엔터키 처리 -> 채팅 UI 포커스 활성화
	if (hud_)
		hud_->SetChatMode();
}

void AMainController::OnTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	// 채팅 입력이 완료 된 후 처리 부
	if (CommitMethod != ETextCommit::OnEnter)
		return;

	ADummy* Dummy = Cast< ADummy >(UGameplayStatics::GetPlayerCharacter(this, 0));

	if (Dummy == nullptr)
		return;

	if (Text.IsEmpty() == false)
	{
		NetPlay::Packet* SendPacket = nullptr;

		if (NetPlay::CreatePacket(&SendPacket) == false)
			return;

		int32 Length = Text.ToString().Len() * 4;

		*SendPacket
			<< Protocol::Chat
			<< Dummy->GetIndex()
			<< Length;

		SendPacket->Write(TCHAR_TO_UTF8(*Text.ToString()), Length);

		if (client_->Send(SendPacket) == false)
			return;

		UChatMsg* Chat = NewObject< UChatMsg >(this);

		if (Chat)
		{
			Chat->SetIndex(Dummy->GetIndex());
			Chat->SetMsg(Text.ToString());

			hud_->AddChat(Chat);
		}
	}

	// 입력 UI 초기화 및 인게임 포커스 활성화
	if (hud_)
		hud_->ClearChat();

	FInputModeGameOnly GameMode;
	SetInputMode(GameMode);

	FSlateApplication::Get().SetUserFocusToGameViewport(1);
}
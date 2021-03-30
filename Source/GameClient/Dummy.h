#pragma once
#include "GameClient.h"
#include "Dummy.generated.h"

UCLASS()
class GAMECLIENT_API ADummy : public ACharacter
{
	GENERATED_BODY()

public:
	ADummy();

	virtual ~ADummy();

public:
	// 더미 위치, 방향, 속도 기준으로 이동하기
	void MoveToActor(FVector& Location, FVector& Rotation, FVector& Velocity);

	// 더미를 목표 지점으로 이동하기
	void MoveToLocation(FVector& Location, FVector& TargetLocation);

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	inline void SetIndex(int32 Index)
	{
		index_ = Index;
	}

	inline int GetIndex(void) const
	{
		return index_;
	}

	inline void SetPlayable(bool Playable)
	{
		playable_ = Playable;
	}

	inline bool GetPlayable(void) const
	{
		return playable_;
	}

private:
	// 전방 이도
	void MoveFoward(float AxisValue);

	// 측면 이동
	void MoveRight(float AxisValue);
	
	// 마우스 X좌표 시점 이동
	void Turn(float Rate);

	// 마우스 Y좌표 시점 이동
	void LookUp(float Rate);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springArm_ = nullptr;		// 카메라 스프링 암

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera_ = nullptr;			// 카메라

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ui_ = nullptr;				// 메쉬 위의 식별값 UI

private:
	int32 index_ = 0;								// 식별값

	bool playable_ = true;							// 플레이 가능 하므로 true
};

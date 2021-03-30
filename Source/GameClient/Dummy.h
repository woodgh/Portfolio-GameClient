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
	// ���� ��ġ, ����, �ӵ� �������� �̵��ϱ�
	void MoveToActor(FVector& Location, FVector& Rotation, FVector& Velocity);

	// ���̸� ��ǥ �������� �̵��ϱ�
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
	// ���� �̵�
	void MoveFoward(float AxisValue);

	// ���� �̵�
	void MoveRight(float AxisValue);
	
	// ���콺 X��ǥ ���� �̵�
	void Turn(float Rate);

	// ���콺 Y��ǥ ���� �̵�
	void LookUp(float Rate);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springArm_ = nullptr;		// ī�޶� ������ ��

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera_ = nullptr;			// ī�޶�

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ui_ = nullptr;				// �޽� ���� �ĺ��� UI

private:
	int32 index_ = 0;								// �ĺ���

	bool playable_ = true;							// �÷��� ���� �ϹǷ� true
};

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
	void MoveToActor(FVector& Location, FVector& Rotation, FVector& Velocity);

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
	void MoveFoward(float AxisValue);

	void MoveRight(float AxisValue);
	
	void Turn(float Rate);

	void LookUp(float Rate);

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* springArm_ = nullptr;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* camera_ = nullptr;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* ui_ = nullptr;

private:
	int32 index_ = 0;

	bool playable_ = true;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"

void UMainHUD::SetActorInfo(FVector& Location, FVector& Rotation, FVector& Velocity, float DeltaTime)
{
	if (location_)
		location_->SetText(FText::FromString(FString::Printf(TEXT("Location: %+03.03f/%+03.03f/%+03.03f"), Location.X, Location.Y, Location.Z)));

	if (rotation_)
		rotation_->SetText(FText::FromString(FString::Printf(TEXT("Rotation: %+03.03f/%+03.03f/%+03.03f"), Rotation.X, Rotation.Y, Rotation.Z)));

	if (velocity_)
		velocity_->SetText(FText::FromString(FString::Printf(TEXT("Velocity: %+03.03f/%+03.03f/%+03.03f"), Velocity.X, Velocity.Y, Velocity.Z)));

	if (deltaTime_)
		deltaTime_->SetText(FText::FromString(FString::Printf(TEXT("DeltaTime: %+03.03f"), DeltaTime)));
}

void UMainHUD::AddChat(UChatMsg* Msg)
{
	if (Msg== nullptr)
		return;

	if (history_)
		history_->AddItem(Msg);

	history_->ScrollToBottom();
}

void UMainHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

void UMainHUD::SetChatMode(void)
{
	if (input_ && input_->HasKeyboardFocus() == false)
		input_->SetFocus();
}

void UMainHUD::ClearChat(void)
{
	if (input_)
		input_->SetText(FText());
}
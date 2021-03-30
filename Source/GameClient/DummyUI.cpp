// Fill out your copyright notice in the Description page of Project Settings.


#include "DummyUI.h"

void UDummyUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	// 더미 식별 UI 설정하기
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!dummyPtr_.IsValid())
		return;

	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	
	if (index_)
		index_->SetText(FText::FromString(FString::Printf(TEXT("< %d >"), dummyPtr_->GetIndex())));
}
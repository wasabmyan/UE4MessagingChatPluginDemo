// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"

/**
 *
 */
class SChatWindow : public SCompoundWidget
{
public:
	TSharedRef<SScrollBox> ChatScrollBox = SNew(SScrollBox);
	TSharedRef<SEditableTextBox> ChatEditableTextBox = SNew(SEditableTextBox);

	TWeakPtr<class FMessagingChatPluginModule> ChatPluginModule;
public:

	SLATE_BEGIN_ARGS(SChatWindow) {}
	SLATE_ARGUMENT(TWeakPtr<class FMessagingChatPluginModule>, ChatPluginModule)
	SLATE_END_ARGS()

	// widget construction
	void Construct(const FArguments& InArgs);

	// Button click event
	FReply OnSendButtonClicked();

	void AddMessageText(FText NickName, FText Message);
};

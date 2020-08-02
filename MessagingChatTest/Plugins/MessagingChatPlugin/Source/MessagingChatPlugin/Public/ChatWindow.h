// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "MessagingData.h"
/**
 *
 */
class SChatWindow : public SCompoundWidget
{
public:
	FString Nickname = FString(TEXT(""));
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

	// Add Message to chat window
	void AddMessageText(FText NickName, FText Message, FColor TextColor);

	void OnWindowClosed();

	// MESSAGING EVENTS
public:
	// initialize the Endpoint
	void InitializeServer();

	// Shutdown the Endpoint
	void ShutdownServer();

	// Message handler for FChatMessage, called by Message Bus when a message arrives
	void ChatMessageHandler(const FChatMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);

private:
	// The message endpoint
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> ChatMessageEndpoint;

};

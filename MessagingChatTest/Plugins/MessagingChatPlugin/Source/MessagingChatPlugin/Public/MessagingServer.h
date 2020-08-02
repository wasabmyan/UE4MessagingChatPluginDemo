// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MessageEndPoint.h"
#include "MessagingServer.generated.h"

USTRUCT()
struct FChatMessage
{
	GENERATED_BODY()

	FString Nickname;
	FString Message;
	FChatMessage() = default;
	FChatMessage(const FString & nick, const FString & message) : Nickname(nick), Message(message) {}
};

/**
 * 
 */
class MESSAGINGCHATPLUGIN_API MessagingServer
{
private:
	TSharedPtr<FMessageEndpoint, ESPMode::ThreadSafe> ChatMessageEndpoint;

public:
	// initialize the Endpoint
	void InitializeServer();

	void ShutdownServer();

	// Message handler for FChatMessage, called by Message Bus when a message arrives
	void ChatMessageHandler(const FChatMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context);
};

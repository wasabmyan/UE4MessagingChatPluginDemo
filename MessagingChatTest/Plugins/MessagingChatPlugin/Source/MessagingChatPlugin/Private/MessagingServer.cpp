// Fill out your copyright notice in the Description page of Project Settings.


#include "MessagingServer.h"
#include "MessageEndpointBuilder.h"

void MessagingServer::InitializeServer()
{
	// Initialize an endpoint that waits for the chat message arrives and connect to the message bus. This will return nullptr when something fails.
	ChatMessageEndpoint = FMessageEndpoint::Builder("ChatMessageEndpointName")
		.Handling<FChatMessage>(this, &MessagingServer::ChatMessageHandler);

	// If the endpoint is valid, we successfully connected to the message bus
	if (ChatMessageEndpoint.IsValid())
	{
		ChatMessageEndpoint->Subscribe<FChatMessage>();
	}	
}

void MessagingServer::ShutdownServer()
{
	// Release the message endpoint, which disconnects from the message bus and stop listening for messages.
	ChatMessageEndpoint.Reset();
}

void MessagingServer::ChatMessageHandler(const FChatMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)
{
	UE_LOG(LogTemp, Warning, TEXT("We just received a test message that said: %s"), *Message.Message);
}
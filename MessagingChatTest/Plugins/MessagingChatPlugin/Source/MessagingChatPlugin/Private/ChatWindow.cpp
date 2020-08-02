// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWindow.h"
#include "MessagingChatPlugin.h"
#include "MessageEndpointBuilder.h"

void SChatWindow::Construct(const FArguments& InArgs)
{
	// Construct Scrollbar
	ChatScrollBox.Get().AddSlot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		.Padding(5);

	// Set hint text for chat editable text box
	ChatEditableTextBox.Get().SetHintText(FText::FromString("Type here!"));

	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			ChatScrollBox
		]

		+ SVerticalBox::Slot()
		.VAlign(VAlign_Bottom)
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			[
				ChatEditableTextBox
			]

			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			.AutoWidth()
			[
				SNew(SButton)
				.OnClicked(this, &SChatWindow::OnSendButtonClicked)
				.Text(FText::FromString("Send"))
			]
		]
	];

	InitializeServer();
}

FReply SChatWindow::OnSendButtonClicked()
{
	if (!ChatEditableTextBox.Get().GetText().IsEmpty())
	{		
		AddMessageText(FText::FromString("Me"), ChatEditableTextBox.Get().GetText(), FColor::Green);		
		
		// If the endpoint is valid then broadcast the messege to every subscribers
		if (ChatMessageEndpoint.IsValid())
		{
			ChatMessageEndpoint->Publish<FChatMessage>(new  FChatMessage(Nickname, ChatEditableTextBox.Get().GetText().ToString()));
		}

		// Empty the chat box
		ChatEditableTextBox.Get().SetText(FText::GetEmpty());
	}
	
	return FReply::Handled();
}

// Add message to the chat window
void SChatWindow::AddMessageText(FText NickName, FText Message, FColor TextColor)
{
	ChatScrollBox.Get().AddSlot()
	[
		SNew(SHorizontalBox)

		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)
		.AutoWidth()
		[
			SNew(STextBlock)
			.Text(NickName)
			.ColorAndOpacity(TextColor)
		]

		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)		
		.AutoWidth()
		[
			SNew(STextBlock)
			.Text(FText::FromString(": "))
			.ColorAndOpacity(TextColor)
		]
		
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)		
		[
			SNew(STextBlock)
			.Text(Message)
			.ColorAndOpacity(TextColor)
		]
	];
}

void SChatWindow::OnWindowClosed()
{	
	ShutdownServer();	
}

///////////////  MESSAGING CHAT EVENTS IMPLEMENTED /////////////

void SChatWindow::InitializeServer()
{
	// Initialize an endpoint that waits for the chat message arrives and connect to the message bus. This will return nullptr when something fails.
	ChatMessageEndpoint = FMessageEndpoint::Builder("ChatMessageEndpointName")
		.Handling<FChatMessage>(this, &SChatWindow::ChatMessageHandler);

	// If the endpoint is valid, we successfully connected to the message bus
	if (ChatMessageEndpoint.IsValid())
	{
		ChatMessageEndpoint->Subscribe<FChatMessage>();
	}
}

void SChatWindow::ShutdownServer()
{	
	// If the endpoint is valid then release the message endpoint, which disconnects from the message bus and stop listening for messages.
	if (ChatMessageEndpoint.IsValid())
	{
		ChatMessageEndpoint.Reset();
	}
	
}

// Hanle the arrived message
void SChatWindow::ChatMessageHandler(const FChatMessage& Message, const TSharedRef<IMessageContext, ESPMode::ThreadSafe>& Context)
{
	// Check if the sender address is not the same then add arrived message to the chat window
	if (Context->GetSender() != ChatMessageEndpoint->GetAddress())
	{
		AddMessageText(FText::FromString(Message.Nickname), FText::FromString(Message.Message), FColor::Yellow);
	}		
}
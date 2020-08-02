// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWindow.h"
#include "MessagingChatPlugin.h"

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
}

FReply SChatWindow::OnSendButtonClicked()
{
	//FString TempString = ChatEditableTextBox.Get().GetText().ToString();
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *TempString);
	if (!ChatEditableTextBox.Get().GetText().IsEmpty())
	{
		AddMessageText(FText::FromString("Me"), ChatEditableTextBox.Get().GetText());
		ChatEditableTextBox.Get().SetText(FText::GetEmpty());
	}
	
	return FReply::Handled();
}

void SChatWindow::AddMessageText(FText NickName, FText Message)
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
		]

		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)		
		.AutoWidth()
		[
			SNew(STextBlock)
			.Text(FText::FromString(": "))
		]
		
		+ SHorizontalBox::Slot()
		.VAlign(VAlign_Center)
		.HAlign(HAlign_Fill)		
		[
			SNew(STextBlock)
			.Text(Message)
		]
	];
}

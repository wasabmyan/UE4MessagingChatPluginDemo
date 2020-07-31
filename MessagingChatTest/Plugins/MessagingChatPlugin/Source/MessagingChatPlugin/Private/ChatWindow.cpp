// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWindow.h"
#include "MessagingChatPlugin.h"

void ChatWindow::Construct(const FArguments& InArgs)
{
	
	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SScrollBox)
			
			+ SScrollBox::Slot()
			.VAlign(VAlign_Top)
			.Padding(5)
			[
				DefaulTextBlock
			]
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
			SNew(SEditableTextBox)
			.HintText(FText::FromString("Type here!"))
			]

			+ SHorizontalBox::Slot()
			.VAlign(VAlign_Fill)
			.HAlign(HAlign_Fill)
			.AutoWidth()
			[
				SNew(SButton)
				.Text(FText::FromString("Send"))
			]
		]
	];
}

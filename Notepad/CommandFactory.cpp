//CommandFactory.cpp
#include"Command.h"
#include"CommandFactory.h"
#include"NotepadForm.h"
#include"resource.h"

// FileCommand
#include"NewCommand.h"
#include"SaveCommand.h"
#include"SaveAsCommand.h"
#include"OpenCommand.h"
#include"PageSetupCommand.h"
#include"PrintCommand.h"
#include"PreviewCommand.h"
#include"CloseCommand.h"

// EditCommand
#include"RedoCommand.h"
#include"UndoCommand.h"
#include"CutCommand.h"
#include"CopyCommand.h"
#include"PasteCommand.h"
#include"CharacterCommand.h"
#include"ImeCharacterCommand.h"
#include"BackspaceCommand.h"
#include"DeleteCommand.h"
#include"BingSearchCommand.h"
#include"FindCommand.h"
#include"FindNextCommand.h"
#include"FindPreviousCommand.h"
#include"ReplaceDialogCommand.h"
#include"ReplaceCommand.h"
#include"GoToLineCommand.h"
#include"SelectAllCommand.h"
#include"DateCommand.h"

// FormatCommand
#include"WrapCommand.h"
#include"WrapLineCommand.h"
#include"WrapUICommand.h"
#include"FontCommand.h"

// ViewCommand
#include"StatusBarCommand.h"

// HelpCommand
#include"HelpCommand.h"

CommandFactory::CommandFactory(NotepadForm *notepadForm) {
	this->notepadForm = notepadForm;
}

CommandFactory::~CommandFactory() {

}

Command* CommandFactory::Create(Long id) {
	Command *command = 0;

	switch (id) {
	case IDM_FILE_NEW:
		command = new NewCommand(this->notepadForm);
		break;

	case IDM_FILE_NEW_FRAME:
		//command = new FileNewFrameCommand(this->notepadForm);
		break;

	case IDM_FILE_OPEN:
		command = new OpenCommand(this->notepadForm);
		break;

	case IDM_FILE_SAVE:
		command = new SaveCommand(this->notepadForm);
		break;

	case IDM_FILE_SAVEAS:
		command = new SaveAsCommand(this->notepadForm);
		break;

	case IDM_FILE_PAGESETUP:
		command = new PageSetupCommand(this->notepadForm);
		break;

	case IDM_FILE_PRINT:
		command = new PrintCommand(this->notepadForm);
		break;

	case IDM_FILE_PREVIEW:
		command = new PreviewCommand(this->notepadForm);
		break;

	case IDM_FILE_CLOSE:
		command = new CloseCommand(this->notepadForm);
		break;

	case IDM_EDIT_REDO:
		command = new RedoCommand(this->notepadForm);
		break;

	case IDM_EDIT_UNDO:
		command = new UndoCommand(this->notepadForm);
		break;

	case IDM_EDIT_CUT:
		command = new CutCommand(this->notepadForm);
		break;

	case IDM_EDIT_COPY:
		command = new CopyCommand(this->notepadForm);
		break;

	case IDM_EDIT_PASTE:
		command = new PasteCommand(this->notepadForm);
		break;

	case IDM_EDIT_CHARACTER:
		command = new CharacterCommand(this->notepadForm);
		break;

	case IDM_EDIT_IMECHARACTER:
		command = new ImeCharacterCommand(this->notepadForm);
		break;

	case IDM_EDIT_BACKSPACE:
		command = new BackspaceCommand(this->notepadForm);
		break;

	case IDM_EDIT_DELETE:
		command = new DeleteCommand(this->notepadForm);
		break;

	case IDM_EDIT_BING:
		command = new BingSearchCommand(this->notepadForm);
		break;

	case IDM_EDIT_FIND:
		command = new FindCommand(this->notepadForm);
		break;

	case IDM_EDIT_FINDNEXT:
		command = new FindNextCommand(this->notepadForm);
		break;

	case IDM_EDIT_FINDPREV:
		command = new FindPreviousCommand(this->notepadForm);
		break;

	case IDM_EDIT_REPLACEDIALOG:
		command = new ReplaceDialogCommand(this->notepadForm);
		break;

	case IDM_EDIT_REPLACE:
		command = new ReplaceCommand(this->notepadForm);
		break;

	case IDM_EDIT_MOVE:
		command = new GoToLineCommand(this->notepadForm);
		break;

	case IDM_EDIT_SELECT_ALL:
		command = new SelectAllCommand(this->notepadForm);
		break;

	case IDM_EDIT_DATE:
		command = new DateCommand(this->notepadForm);
		break;

	case IDM_FORMAT_WRAP:
		command = new WrapCommand(this->notepadForm);
		break;

	case IDM_FORMAT_WRAPLINE:
		command = new WrapLineCommand(this->notepadForm);
		break;

	case IDM_FORMAT_WRAPUI:
		command = new WrapUICommand(this->notepadForm);
		break;

	case IDM_FORMAT_FONT:
		command = new FontCommand(this->notepadForm);
		break;

	case IDM_VIEW_STATUSBAR:
		command = new StatusBarCommand(this->notepadForm);
		break;

	case IDM_HELP_HELP:
		command = new HelpCommand(this->notepadForm);
		break;

	default:
		break;
	
	}

	return command;
}
#if 0



if (id == IDM_FILE_SAVE) {
	command = new SaveCommand(this->notepadForm);
}

else if (id == IDM_FILE_SAVEAS) {
	command = new SaveAsCommand(this->notepadForm);
}

else if (id == IDM_FILE_OPEN) {
	command = new OpenCommand(this->notepadForm);
}

else if (id == IDM_FILE_CLOSE) {
	command = new CloseCommand(this->notepadForm);
}

else if (id == IDM_FORMAT_FONT) {
	command = new FontCommand(this->notepadForm);
}
else if (id == IDM_FORMAT_AUTOMATICCARRIAGERETURN) {
	menu = this->notepadForm->GetMenu();
	Long count = menu->GetMenuItemCount();

	subMenu = menu->GetSubMenu(2);//파일-0, 편집-1, 서식-2
	info.cbSize = sizeof(MENUITEMINFO);
	info.fMask = MIIM_STATE;
	VERIFY(subMenu->GetMenuItemInfoA(IDM_FORMAT_AUTOMATICCARRIAGERETURN, &info));

	if (info.fState == MFS_CHECKED) {
		command = new ManualCarriageReturnCommand(this->notepadForm);
	}
	else if (info.fState == MFS_UNCHECKED) {
		command = new AutomaticCarriageReturnCommand(this->notepadForm);
	}

}

else if (id == IDM_EDIT_SELECTALL) {
	command = new SelectAllCommand(this->notepadForm);
}


else if (id == IDM_VIEW_ZOOMIN) {
	command = new ZoomInCommand(this->notepadForm);
}

else if (id == IDM_VIEW_ZOOMOUT) {
	command = new ZoomOutCommand(this->notepadForm);
}


else if (id == IDM_VIEW_ZOOMDEFAULT) {
	command = new ZoomDefaultCommand(this->notepadForm);
}


else if (id == IDM_EDIT_FINDNEXT) {
	command = new FindNextCommand(this->notepadForm);
}

else if (id == IDM_EDIT_FINDPREVIOUS) {
	command = new FindPreviousCommand(this->notepadForm);
}

else if (id == IDM_EDIT_REPLACE) {
	command = new ReplaceMenuCommand(this->notepadForm);
}

else if (id == IDM_EDIT_FIND) {
	command = new FindCommand(this->notepadForm);
}

else if (id == IDM_EDIT_ERASE) {
	command = new EraseSeletedItemsCommand(this->notepadForm);
}

else if (id == IDM_EDIT_UNDO) {
	command = new UndoCommand(this->notepadForm);
}


else if (id == ID_ONIMECHAR) {
	command = new WriteImeCommand(this->notepadForm);
}

else if (id == ID_ONCHAR) {
	command = new WriteCommand(this->notepadForm);
}

else if (id == ID_BACKSPACE) {
	command = new BackspaceCommand(this->notepadForm);
}

else if (id == ID_DELETE) {
	command = new DeleteCommand(this->notepadForm);
}

else if (id == IDM_EDIT_PASTE) {
	command = new PasteCommand(this->notepadForm);
}
else if (id == IDM_EDIT_CUT) {
	command = new CutCommand(this->notepadForm);
}

else if (id == IDM_EDIT_COPY) {
	command = new CopyCommand(this->notepadForm);
}


else if (id == IDM_EDIT_DATETIME) {
	command = new DateTimeCommand(this->notepadForm);
}

else if (id == IDM_FILE_END) {
	command = new EndNotepadCommand(this->notepadForm);
}

else if (id == IDM_FILE_NEW) {
	command = new NewNotepadCommand(this->notepadForm);
}
else if (id == IDM_VIEW_STATUSBAR) {
	command = new StatusBarCommand(this->notepadForm);
}

else if (id == IDM_HELP_INFO) {
	command = new InformationCommand(this->notepadForm);
}

else if (id == IDM_FILE_PRINT) {
	command = new PrintCommand(this->notepadForm);
}

else if (id == IDM_FILE_PAGESETUP) {
	command = new PageSetupCommand(this->notepadForm);
}

else if (id == IDM_HELP_HELP) {
	command = new HelpCommand(this->notepadForm);
}
else if (id == ID_REPLACE) {
	command = new ReplaceCommand(this->notepadForm);
}
else if (id == ID_ENTER) {
	command = new EnterCommand(this->notepadForm);
}
#endif
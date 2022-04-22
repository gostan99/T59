#pragma once

#include <editor/Plugin.h>
#include <editor/EngineGuiWindow.h>

#include <UnigineWidgets.h>

#include <QObject>

class QAction;

class EngineGuiWindowPlugin final
	: public QObject
	, public ::Editor::Plugin
{
	Q_OBJECT
		Q_PLUGIN_METADATA(IID "com.unigine.EditorPlugin" FILE "EngineGuiWindowPlugin.json")
		Q_INTERFACES(Editor::Plugin)

public:
	bool init() override;
	void shutdown() override;

private:
	void create_window();
	void destroy_window();
	void build_gui();
	void setup_window();

	void onProcessBtnClicked();
	void onSetColorPaletBtnClicked();
	void onColorPaletFileDialogOkBtnClicked();
	void onColorPaletFileDialogCancelBtnClicked();
	void onSetMatFolderBtnClicked();
	void onMatFolderDialogOkBtnClicked();
	void onMatFolderDialogCancelBtnClicked();
	void onErrorDialogOkBtnClicked();
	void onErrorDialogCancelBtnClicked();

	void update();
	void drag_started(QDragEnterEvent* event);
	void drag_moved(QDragMoveEvent* event);
	void drag_left(QDragLeaveEvent* event);
	void drag_dropped(QDropEvent* event);
	void focus_changed();
	void focused();
	void unfocused();

private:
	QAction* action_{};
	Editor::EngineGuiWindow* window_{};
	Unigine::GuiPtr gui_;
	Unigine::WidgetLabelPtr label_;

	Unigine::WidgetDialogFilePtr colorPaletFileDialog;
	Unigine::WidgetDialogFilePtr matFolderDialog;
	Unigine::WidgetDialogPtr errorDialog;
	Unigine::String colorPaletPath;
	Unigine::String matFolderPath;
};

#include "EngineGuiWindowPlugin.h"
#include "../FracDino.h"

#include <UnigineComponentSystem.h>
#include <UnigineGame.h>
#include <UnigineMathLib.h>
#include <UnigineSet.h>

#include <editor/Actions.h>
#include <editor/Constants.h>
#include <editor/Selection.h>
#include <editor/Selector.h>
#include <editor/WindowManager.h>

#include <QDropEvent>
#include <QFileInfo>
#include <QMenu>
#include <QMimeData>

using namespace Unigine;

bool EngineGuiWindowPlugin::init()
{
	using Editor::WindowManager;
	QMenu* menu = WindowManager::findMenu(Constants::MM_WINDOWS);
	action_ = menu->addAction("Plugin - Vox Helper", this,
							  &EngineGuiWindowPlugin::create_window);

	connect(WindowManager::instance(), &WindowManager::windowHidden, this, [this](QWidget* w)
	{
		if (w == window_)
			destroy_window();
	});

	// register components
	ComponentSystem::get()->initialize();

	return true;
}

void EngineGuiWindowPlugin::shutdown()
{
	// unregister components

	disconnect(Editor::WindowManager::instance(), nullptr, this, nullptr);

	delete action_;
	action_ = nullptr;

	destroy_window();
}

void EngineGuiWindowPlugin::create_window()
{
	if (window_)
	{
		Editor::WindowManager::show(window_);
		return;
	}

	window_ = new Editor::EngineGuiWindow;

	setup_window();
	build_gui();

	Editor::WindowManager::add(window_, Editor::WindowManager::NEW_FLOATING_AREA);
	Editor::WindowManager::show(window_);
}

void EngineGuiWindowPlugin::destroy_window()
{
	label_.clear();
	gui_.clear();

	if (window_)
	{
		window_->clearCallbacks();
		Editor::WindowManager::remove(window_);
		delete window_;
		window_ = nullptr;
	}
}

void EngineGuiWindowPlugin::build_gui()
{
	gui_ = window_->getGui();

	WidgetWindowPtr main_window = WidgetWindow::create(gui_, "Engine Gui Window");
	main_window->setWidth(200);
	main_window->setHeight(300);
	main_window->setSizeable(true);

	#pragma region Buttons

	// Set color palet btn
	WidgetButtonPtr setColorPaletBtn = WidgetButton::create(gui_, "Set color palet");
	setColorPaletBtn->addCallback(Gui::CLICKED,
								  MakeCallback(this, &EngineGuiWindowPlugin::onSetColorPaletBtnClicked));
	main_window->addChild(setColorPaletBtn, Gui::ALIGN_EXPAND);
	colorPaletFileDialog = WidgetDialogFile::create(gui_, "File open dialog");
	colorPaletFileDialog->setPath("../data/");
	colorPaletFileDialog->setFilter(".png.jpeg");
	// setting "dialog_ok_clicked" function to handle CLICKED event for dialog Ok button
	colorPaletFileDialog->getOkButton()->addCallback(Gui::CLICKED, MakeCallback(this, &EngineGuiWindowPlugin::onColorPaletFileDialogOkBtnClicked));
	// setting "dialog_cancel_clicked" function to handle CLICKED event for dialog Cancel button
	colorPaletFileDialog->getCancelButton()->addCallback(Gui::CLICKED, MakeCallback(this, &EngineGuiWindowPlugin::onColorPaletFileDialogCancelBtnClicked));
	// adding the created file dialog widget to the system GUI and hiding it
	colorPaletFileDialog->setHidden(1);
	gui_->addChild(colorPaletFileDialog, Gui::ALIGN_OVERLAP | Gui::ALIGN_CENTER);

	// Set material folder path
	WidgetButtonPtr setMatFolderBtn = WidgetButton::create(gui_, "Set materials folder");
	setMatFolderBtn->addCallback(Gui::CLICKED,
								 MakeCallback(this, &EngineGuiWindowPlugin::onSetMatFolderBtnClicked));
	main_window->addChild(setMatFolderBtn, Gui::ALIGN_EXPAND);
	matFolderDialog = WidgetDialogFile::create(gui_, "File open dialog");
	matFolderDialog->setPath("../data/");
	matFolderDialog->setFilter(".mgraph");
	// setting "dialog_ok_clicked" function to handle CLICKED event for dialog Ok button
	matFolderDialog->getOkButton()->addCallback(Gui::CLICKED, MakeCallback(this, &EngineGuiWindowPlugin::onMatFolderDialogOkBtnClicked));
	// setting "dialog_cancel_clicked" function to handle CLICKED event for dialog Cancel button
	matFolderDialog->getCancelButton()->addCallback(Gui::CLICKED, MakeCallback(this, &EngineGuiWindowPlugin::onMatFolderDialogCancelBtnClicked));
	// adding the created file dialog widget to the system GUI and hiding it
	matFolderDialog->setHidden(1);
	gui_->addChild(matFolderDialog, Gui::ALIGN_OVERLAP | Gui::ALIGN_CENTER);

	// Process vox btn
	WidgetButtonPtr processVoxBtn = WidgetButton::create(gui_, "Process");
	processVoxBtn->addCallback(Gui::CLICKED,
							   MakeCallback(this, &EngineGuiWindowPlugin::onProcessBtnClicked));
	main_window->addChild(processVoxBtn, Gui::ALIGN_EXPAND);

	// Error dialog
	errorDialog = WidgetDialog::create(gui_, "Please set color palet and material folder path!");
	// setting "dialog_ok_clicked" function to handle CLICKED event for dialog Ok button
	errorDialog->getOkButton()->addCallback(Gui::CLICKED, MakeCallback(this, &EngineGuiWindowPlugin::onErrorDialogOkBtnClicked));
	// adding the created file dialog widget to the system GUI and hiding it
	// setting "dialog_cancel_clicked" function to handle CLICKED event for dialog Cancel button
	errorDialog->getCancelButton()->addCallback(Gui::CLICKED, MakeCallback(this, &EngineGuiWindowPlugin::onErrorDialogCancelBtnClicked));
	errorDialog->setHidden(1);
	gui_->addChild(errorDialog, Gui::ALIGN_OVERLAP | Gui::ALIGN_CENTER);

	#pragma endregion

	WidgetLabelPtr selection_label = WidgetLabel::create(gui_);
	main_window->addChild(selection_label, Gui::ALIGN_EXPAND);
	label_ = WidgetLabel::create(gui_);
	main_window->addChild(label_, Gui::ALIGN_EXPAND);
	gui_->addChild(main_window, Gui::ALIGN_OVERLAP);

	// bind selection change
	auto refresh_selection_label = [selection_label]()
	{
		StringStack<> s = "Selected Nodes:";

		if (Editor::SelectorNodes* selector = Editor::Selection::getSelectorNodes())
		{
			for (const NodePtr& node : selector->getNodes())
			{
				s += "\n\t";
				s += node->getName();
			}
		}

		selection_label->setText(s.get());
	};

	Editor::Selection* selection = Editor::Selection::instance();
	connect(selection, &Editor::Selection::changed, window_, refresh_selection_label);

	// Take the current state
	refresh_selection_label();
}

void EngineGuiWindowPlugin::setup_window()
{
	window_->setWindowTitle("Plugin - Optimize Vox Mesh");

	window_->setRenderingPolicy(Editor::EngineGuiWindow::RENDERING_POLICY_WINDOW_VISIBLE_AND_FOCUSED);

	window_->addUpdateCallback(MakeCallback(this, &EngineGuiWindowPlugin::update));
	window_->addDragEnterCallback(MakeCallback(this, &EngineGuiWindowPlugin::drag_started));
	window_->addDragMoveCallback(MakeCallback(this, &EngineGuiWindowPlugin::drag_moved));
	window_->addDragLeaveCallback(MakeCallback(this, &EngineGuiWindowPlugin::drag_left));
	window_->addDropCallback(MakeCallback(this, &EngineGuiWindowPlugin::drag_dropped));
	window_->addFocusChangedCallback(MakeCallback(this, &EngineGuiWindowPlugin::focus_changed));
	window_->addFocusInChangedCallback(MakeCallback(this, &EngineGuiWindowPlugin::focused));
	window_->addFocusOutChangedCallback(MakeCallback(this, &EngineGuiWindowPlugin::unfocused));
}

void optimizeVox(NodePtr node)
{
	ObjectMeshStaticPtr child;
	Vector<NodePtr> passChildren;
	Vector<NodePtr> removeChildren;
	for (size_t i = 0; i < node->getNumChildren(); i++)
	{
		child = checked_ptr_cast<ObjectMeshStatic>(node->getChild(i));
		if (child)
		{
			bool pass = true;
			auto intersection = Unigine::WorldIntersection::create();
			auto distance = 0.1f;
			auto p0 = child->getWorldBoundBox().getCenter();
			auto p1 = p0 + Math::vec3_forward * distance;
			Vector<NodePtr> exclude = { child };
			auto obj = World::getIntersection(p0, p1, 1, exclude, intersection);
			if (obj)
			{
				p1 = p0 + Math::vec3_back * distance;
				obj = World::getIntersection(p0, p1, 1, exclude, intersection);
				if (obj)
				{
					p1 = p0 + Math::vec3_up * distance;
					obj = World::getIntersection(p0, p1, 1, exclude, intersection);
					if (obj)
					{
						p1 = p0 + Math::vec3_down * distance;
						obj = World::getIntersection(p0, p1, 1, exclude, intersection);
						if (obj)
						{
							p1 = p0 + Math::vec3_left * distance;
							obj = World::getIntersection(p0, p1, 1, exclude, intersection);
							if (obj)
							{
								p1 = p0 + Math::vec3_right * distance;
								obj = World::getIntersection(p0, p1, 1, exclude, intersection);
								if (obj)
								{
									removeChildren.append(child);
									pass = false;
								}
							}
						}
					}
				}
			}
			if (pass)
			{
				passChildren.append(child);
			}
		}
	}

	// Remove Unwanted cube
	auto removeAct = Editor::RemoveNodesAction(removeChildren);
	removeAct.apply();
}

int getPaletIndex(Math::vec4 color, String colorPaletPath)
{
	// getting image size
	auto image = Image::create(colorPaletPath);
	int width = image->getWidth();
	int height = image->getHeight();
	Vector<Math::ivec3> colors;
	// running through all image pixels of the specified channel in a loop
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			// composing pixel id from its coords; (0, 0) - top-left corner
			int id = x + y * width;

			// setting a value for a pixel by its id
			Math::dvec4 color;
			image->get(id, color);
			color *= 255;
			colors.append({ (int)color.x,(int)color.y,(int)color.z });
		}
	}
	color *= 255;
	auto icolor = Math::ivec3(color.x, color.y, color.z);
	return colors.findIndex(icolor) + 1;
}

void EngineGuiWindowPlugin::onProcessBtnClicked()
{
	Log::message("btn clicked!\n");
	if (colorPaletPath.empty() || matFolderPath.empty())
	{
		// resetting file sepection, showing the dialog and setting permanent focus to it
		errorDialog->setHidden(0);
		errorDialog->setPermanentFocus();
		return;
	}

	if (Editor::SelectorNodes* selector = Editor::Selection::getSelectorNodes())
	{
		// Optimize
		for (const NodePtr& node : selector->getNodes())
		{
			optimizeVox(node);
		}

		// Add needed components
		auto dir = Dir::create();
		dir->open(matFolderPath);
		Map<int, MaterialPtr> materials;
		for (size_t i = 0; i < dir->getNumFiles(); i++)
		{
			String matName = dir->getFileName(i);
			matName = String::removeExtension(matName);
			matName = matName.substr(matName.find("#") + 1);
			int index = String::atoi(matName);
			if (!materials.contains(index))
			{
				String matPath = dir->getFileName(0);
				String before = String::split(matPath, "#")[1];

				before = String::split(before, ".")[0];
				matPath = matPath.replace(before, String::itoa(index));

				auto mat = Materials::loadMaterial(matPath);
				materials.append(index, mat);
			}
		}
		for (const NodePtr& node : selector->getNodes())
		{
			// Set up Riggid body and add needed components
			for (size_t i = 0; i < node->getNumChildren(); i++)
			{
				auto mesh = checked_ptr_cast<ObjectMeshStatic>(node->getChild(i));
				mesh->setCollision(true, 0);

				auto body = BodyRigid::create();
				auto shape = ShapeBox::create(body, mesh->getWorldBoundBox().getSize());
				shape->setBodyShapeTransform(Math::translate(mesh->getBoundBox().getCenter()));
				body->addShape(shape);
				mesh->setBody(body);

				auto cs = ComponentSystem::get();
				cs->addComponent<FracDino>(mesh);

				// Add materials
				auto color = mesh->getColor(0, 0);
				int paletIndex = getPaletIndex(color, colorPaletPath);
				if (materials.contains(paletIndex))
				{
					mesh->setMaterial(materials[paletIndex], 0);
				}
			}
		}
		dir->close();

		//// Add materials
		//auto dir = Dir::create();
		//dir->open(matFolderPath);
		//Set<int>matIndexes;

		//for (size_t i = 0; i < dir->getNumFiles(); i++)
		//{
		//	String matName = dir->getFileName(i);
		//	matName = String::removeExtension(matName);
		//	matName = matName.substr(matName.find("#") + 1);
		//	int index = String::atoi(matName);
		//	matIndexes.append(index);
		//}
		//for (const NodePtr& node : selector->getNodes())
		//{
		//	for (size_t i = 0; i < node->getNumChildren(); i++)
		//	{
		//		auto mesh = checked_ptr_cast<ObjectMeshStatic>(node->getChild(i));
		//		auto color = mesh->getColor(0, 0);
		//		int paletIndex = getPaletIndex(color, colorPaletPath);
		//		if (matIndexes.contains(paletIndex))
		//		{
		//			String matPath = dir->getFileName(0);
		//			String before = String::split(matPath, "#")[1];
		//			before = String::split(before, ".")[0];
		//			matPath = matPath.replace(before, String::itoa(paletIndex));
		//			auto mat = Materials::loadMaterial(matPath);
		//			mesh->setMaterial(mat, 0);
		//		}
		//	}
		//}
		//dir->close();
	}
}

void EngineGuiWindowPlugin::onSetColorPaletBtnClicked()
{
	//Log::message("btn clicked!\n");
	if (Editor::SelectorNodes* selector = Editor::Selection::getSelectorNodes())
	{
		// resetting file sepection, showing the dialog and setting permanent focus to it
		colorPaletFileDialog->setFile("");
		colorPaletFileDialog->setOkText("Set Color Palet");
		colorPaletFileDialog->setHidden(0);
		colorPaletFileDialog->setPermanentFocus();
	}
}

void EngineGuiWindowPlugin::onColorPaletFileDialogOkBtnClicked()
{
	// getting the current path selection fron the dialog and checking if the file exists
	String path = colorPaletFileDialog->getFile();
	if (!FileSystem::isFileExist(path))
		return;

	// if the file exists hiding the dialog, displaying the selected file on the "file_name" label and removing focus
	colorPaletPath = path;
	colorPaletFileDialog->setHidden(1);
	colorPaletFileDialog->removeFocus();
}

void EngineGuiWindowPlugin::onColorPaletFileDialogCancelBtnClicked()
{
	colorPaletFileDialog->setHidden(1);
	colorPaletFileDialog->removeFocus();
}

void EngineGuiWindowPlugin::onSetMatFolderBtnClicked()
{
	//Log::message("btn clicked!\n");
	if (Editor::SelectorNodes* selector = Editor::Selection::getSelectorNodes())
	{
		// resetting file sepection, showing the dialog and setting permanent focus to it
		matFolderDialog->setFile("");
		matFolderDialog->setOkText("Set Mat Folder");
		matFolderDialog->setHidden(0);
		matFolderDialog->setPermanentFocus();
	}
}

void EngineGuiWindowPlugin::onMatFolderDialogOkBtnClicked()
{
	// getting the current path selection fron the dialog and checking if the file exists
	String path = matFolderDialog->getPath();

	// if the file exists hiding the dialog, displaying the selected file on the "file_name" label and removing focus
	matFolderPath = path;
	matFolderDialog->setHidden(1);
	matFolderDialog->removeFocus();
}

void EngineGuiWindowPlugin::onMatFolderDialogCancelBtnClicked()
{
	matFolderDialog->setHidden(1);
	matFolderDialog->removeFocus();
}

void EngineGuiWindowPlugin::onErrorDialogOkBtnClicked()
{
	errorDialog->setHidden(1);
	errorDialog->removeFocus();
}

void EngineGuiWindowPlugin::onErrorDialogCancelBtnClicked()
{
	errorDialog->setHidden(1);
	errorDialog->removeFocus();
}

void EngineGuiWindowPlugin::update()
{
	const char* template_text = nullptr;
	if (Input::isKeyDown(Input::KEY_UP))
		template_text = "Arrow Up has been pressed: ";
	if (Input::isKeyDown(Input::KEY_DOWN))
		template_text = "Arrow Down has been pressed: ";

	if (template_text)
	{
		const char* label_text = label_->getText();
		int previous_value = 0;

		if (String::startsWith(label_text, template_text))
		{
			const char* value_text = label_text + strlen(template_text);
			previous_value = String::atoi(value_text);
		}

		StringStack<> new_text = template_text;
		new_text += String::itoa(previous_value + 1);
		label_->setText(new_text.get());
	}
}

void EngineGuiWindowPlugin::drag_started(QDragEnterEvent* event)
{
	if (event->mimeData()->hasUrls())
	{
		event->acceptProposedAction();
		gui_->setMouseCursor(Gui::CURSOR_DND);
	}
	else
		gui_->setMouseCursor(Gui::CURSOR_NA);
}

void EngineGuiWindowPlugin::drag_moved(QDragMoveEvent*) {}

void EngineGuiWindowPlugin::drag_left(QDragLeaveEvent*)
{
	const int cursor = gui_->getMouseCursor();
	if (cursor == Gui::CURSOR_DND || cursor == Gui::CURSOR_NA)
		gui_->setMouseCursor(Gui::CURSOR_NONE);
}

void EngineGuiWindowPlugin::drag_dropped(QDropEvent* event)
{
	const QMimeData* mime = event->mimeData();
	if (mime->hasUrls())
	{
		Log::message("%s: Dropped Files\n", window_->windowTitle().toUtf8().constData());
		for (const QUrl& url : mime->urls())
		{
			const QString& file_path = QFileInfo(url.toLocalFile()).absoluteFilePath();
			Log::message("%s\n", file_path.toUtf8().constData());
		}
	}
}

void EngineGuiWindowPlugin::focus_changed()
{
	Log::message("%s: Focus Changed\n", window_->windowTitle().toUtf8().constData());
	Log::message("%s: %s\n", window_->windowTitle().toUtf8().constData(),
				 window_->hasFocus() ? "Has Focus" : "Doesn't have Focus");
}

void EngineGuiWindowPlugin::focused()
{
	Log::message("%s: Focused\n", window_->windowTitle().toUtf8().constData());
}

void EngineGuiWindowPlugin::unfocused()
{
	label_->setText(nullptr);

	Log::message("%s: Unfocused\n", window_->windowTitle().toUtf8().constData());
}
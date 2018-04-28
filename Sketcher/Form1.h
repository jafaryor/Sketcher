#pragma once
#include "Element.h"
#include "Sketch.h"
#include "PenDialog.h"
#include "TextDialog.h"

namespace Sketcher {

	using namespace System;
	//содержит классы, определяющие типы данных, классы для событий, обработки событий и исключений и часто применяемые функции.
	using namespace System::ComponentModel;
	//содержит классы, поддерживающие функционирования компонентов GUI в приложении среды CLR.
	using namespace System::Collections;
	//содержит классы коллекций, позволяющие организовать данные различными способами.
	using namespace System::Windows::Forms;
	//содержит классы, поддерживающие использование в приложении компонентов Windows Form.
	using namespace System::Data;
	//содержит класы, поддерживающие технологию ADO.NET
	using namespace System::Drawing;
	//содержит классы, которые поддерживают основные графические операции, такие as рисование в форме или компоненте.
	using namespace System::Runtime::Serialization::Formatters::Binary;
	//необходим объект BinaryFormatter для сохранения эскиза
	using namespace System::IO;


	enum class ElementType{LINE, RECTANGLE, CIRCLE, CURVE, TEXT};		//Я добавил!!!
	enum class Mode{Normal, Move};		//Я юобавил!!! 

	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void): elementType(ElementType::LINE), color(Color::Black)	//Я добавил!!!		инициализация переменных.
			, drawing(false), firstPoint(0), tempElement(nullptr), sketch(gcnew Sketch())
			, highlightedElement(nullptr)
			, mode(Mode::Normal)
			, penDialog(gcnew PenDialog()), penWidth(1.0f)
			, textDialog(gcnew TextDialog())
			, formatter(gcnew BinaryFormatter()), sketchFilePath(nullptr)
		{
			InitializeComponent();
			//
			SetElementTypeButtonsState();
			SetColorButtonsState();
			lineStyleComboBox->SelectedIndex = 0;
			textFont = Font;		//свойство формы, предоставляющий шрифт по умолчанию.
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	protected: 

	private: System::Windows::Forms::ToolStripMenuItem^  createToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveasToolStripMenuItem;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  printToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  previewToolStripMenuItem;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  editToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  undoToolStripMenuItem;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^  cutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  copyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  pasteToolStripMenuItem;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
	private: System::Windows::Forms::ToolStripMenuItem^  выделитьвсеToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  indexToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  searchToolStripMenuItem;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator10;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  toolsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  elementToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  lineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rectangleToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  circleToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  curveToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  colorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  blackToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  redToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  greenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  blueToolStripMenuItem;

	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  createToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  openToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  saveToolStripButton;
	private: System::Windows::Forms::ToolStripButton^  printToolStripButton;

	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator5;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton1;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton2;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton3;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton4;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator6;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton5;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton6;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton7;
	private: System::Windows::Forms::ToolStripButton^  toolStripButton8;
	private: System::Windows::Forms::ContextMenuStrip^  contextMenuStrip1;


	private: System::Windows::Forms::ToolStripMenuItem^  sendToBackContextMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  deleteContextMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  moveContextMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  contextSeparator;

	private: System::Windows::Forms::ToolStripMenuItem^  lineContextMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rectangleContextMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  circleContextMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  curveContextMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  blackContextMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  redContextMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  greenContextMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  blueContextMenuItem;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator7;
private: System::Windows::Forms::ToolStripButton^  penWidthButton;
private: System::Windows::Forms::ToolStripComboBox^  lineStyleComboBox;
private: System::Windows::Forms::ToolStripMenuItem^  textToolStripMenuItem;
private: System::Windows::Forms::ToolStripButton^  textToolStripMenuItem1;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator8;
private: System::Windows::Forms::ToolStripMenuItem^  textToolStripMenuItem2;
private: System::Windows::Forms::ToolStripButton^  fontToolStripButton;
private: System::Windows::Forms::FontDialog^  fontDialog1;
private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
private: System::Windows::Forms::SaveFileDialog^  saveFileDialog;
private: System::Drawing::Printing::PrintDocument^  printDocument;
private: System::Windows::Forms::PrintDialog^  printDialog;












	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)	//Функция для установки окна приложения и любых , добавляемых в форму.
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->createToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveasToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->printToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->previewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->editToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->undoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->cutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->copyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pasteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->выделитьвсеToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->elementToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rectangleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->circleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->curveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->textToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->colorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->blackToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->redToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->greenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->blueToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->indexToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->searchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator10 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
			this->createToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->openToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->saveToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->printToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator5 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripButton1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton2 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton3 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton4 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator6 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripButton5 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton6 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton7 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripButton8 = (gcnew System::Windows::Forms::ToolStripButton());
			this->toolStripSeparator7 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->penWidthButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->lineStyleComboBox = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->textToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripButton());
			this->fontToolStripButton = (gcnew System::Windows::Forms::ToolStripButton());
			this->contextMenuStrip1 = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->sendToBackContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deleteContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->moveContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->contextSeparator = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->lineContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rectangleContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->circleContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->curveContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->blackContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->redContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->greenContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->blueContextMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator8 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->textToolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->fontDialog1 = (gcnew System::Windows::Forms::FontDialog());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog = (gcnew System::Windows::Forms::SaveFileDialog());
			this->printDocument = (gcnew System::Drawing::Printing::PrintDocument());
			this->printDialog = (gcnew System::Windows::Forms::PrintDialog());
			this->menuStrip1->SuspendLayout();
			this->toolStrip1->SuspendLayout();
			this->contextMenuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->fileToolStripMenuItem, 
				this->editToolStripMenuItem, this->toolsToolStripMenuItem, this->elementToolStripMenuItem, this->colorToolStripMenuItem, this->helpToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(682, 28);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {this->createToolStripMenuItem, 
				this->openToolStripMenuItem, this->toolStripSeparator, this->saveToolStripMenuItem, this->saveasToolStripMenuItem, this->toolStripSeparator1, 
				this->printToolStripMenuItem, this->previewToolStripMenuItem, this->toolStripSeparator2, this->exitToolStripMenuItem});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(44, 24);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// createToolStripMenuItem
			// 
			this->createToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->createToolStripMenuItem->Name = L"createToolStripMenuItem";
			this->createToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			this->createToolStripMenuItem->Size = System::Drawing::Size(174, 24);
			this->createToolStripMenuItem->Text = L"Create";
			this->createToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::createToolStripMenuItem_Click);
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
			this->openToolStripMenuItem->Size = System::Drawing::Size(174, 24);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// toolStripSeparator
			// 
			this->toolStripSeparator->Name = L"toolStripSeparator";
			this->toolStripSeparator->Size = System::Drawing::Size(171, 6);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			this->saveToolStripMenuItem->Size = System::Drawing::Size(174, 24);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveToolStripMenuItem_Click);
			// 
			// saveasToolStripMenuItem
			// 
			this->saveasToolStripMenuItem->Name = L"saveasToolStripMenuItem";
			this->saveasToolStripMenuItem->Size = System::Drawing::Size(174, 24);
			this->saveasToolStripMenuItem->Text = L"Save as";
			this->saveasToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveasToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(171, 6);
			// 
			// printToolStripMenuItem
			// 
			this->printToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"printToolStripMenuItem.Image")));
			this->printToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->printToolStripMenuItem->Name = L"printToolStripMenuItem";
			this->printToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::P));
			this->printToolStripMenuItem->Size = System::Drawing::Size(174, 24);
			this->printToolStripMenuItem->Text = L"Print";
			this->printToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::printToolStripMenuItem_Click);
			// 
			// previewToolStripMenuItem
			// 
			this->previewToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"previewToolStripMenuItem.Image")));
			this->previewToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->previewToolStripMenuItem->Name = L"previewToolStripMenuItem";
			this->previewToolStripMenuItem->Size = System::Drawing::Size(174, 24);
			this->previewToolStripMenuItem->Text = L"Preview";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(171, 6);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(174, 24);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::exitToolStripMenuItem_Click);
			// 
			// editToolStripMenuItem
			// 
			this->editToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(7) {this->undoToolStripMenuItem, 
				this->toolStripSeparator3, this->cutToolStripMenuItem, this->copyToolStripMenuItem, this->pasteToolStripMenuItem, this->toolStripSeparator4, 
				this->выделитьвсеToolStripMenuItem});
			this->editToolStripMenuItem->Name = L"editToolStripMenuItem";
			this->editToolStripMenuItem->Size = System::Drawing::Size(47, 24);
			this->editToolStripMenuItem->Text = L"Edit";
			// 
			// undoToolStripMenuItem
			// 
			this->undoToolStripMenuItem->Name = L"undoToolStripMenuItem";
			this->undoToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Z));
			this->undoToolStripMenuItem->Size = System::Drawing::Size(165, 24);
			this->undoToolStripMenuItem->Text = L"Undo";
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(162, 6);
			// 
			// cutToolStripMenuItem
			// 
			this->cutToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"cutToolStripMenuItem.Image")));
			this->cutToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->cutToolStripMenuItem->Name = L"cutToolStripMenuItem";
			this->cutToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::X));
			this->cutToolStripMenuItem->Size = System::Drawing::Size(165, 24);
			this->cutToolStripMenuItem->Text = L"Cut";
			// 
			// copyToolStripMenuItem
			// 
			this->copyToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"copyToolStripMenuItem.Image")));
			this->copyToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->copyToolStripMenuItem->Name = L"copyToolStripMenuItem";
			this->copyToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
			this->copyToolStripMenuItem->Size = System::Drawing::Size(165, 24);
			this->copyToolStripMenuItem->Text = L"Copy";
			// 
			// pasteToolStripMenuItem
			// 
			this->pasteToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pasteToolStripMenuItem.Image")));
			this->pasteToolStripMenuItem->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->pasteToolStripMenuItem->Name = L"pasteToolStripMenuItem";
			this->pasteToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::V));
			this->pasteToolStripMenuItem->Size = System::Drawing::Size(165, 24);
			this->pasteToolStripMenuItem->Text = L"Paste";
			// 
			// toolStripSeparator4
			// 
			this->toolStripSeparator4->Name = L"toolStripSeparator4";
			this->toolStripSeparator4->Size = System::Drawing::Size(162, 6);
			// 
			// выделитьвсеToolStripMenuItem
			// 
			this->выделитьвсеToolStripMenuItem->Name = L"выделитьвсеToolStripMenuItem";
			this->выделитьвсеToolStripMenuItem->Size = System::Drawing::Size(165, 24);
			this->выделитьвсеToolStripMenuItem->Text = L"Select all";
			// 
			// toolsToolStripMenuItem
			// 
			this->toolsToolStripMenuItem->Name = L"toolsToolStripMenuItem";
			this->toolsToolStripMenuItem->Size = System::Drawing::Size(57, 24);
			this->toolsToolStripMenuItem->Text = L"Tools";
			// 
			// elementToolStripMenuItem
			// 
			this->elementToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {this->lineToolStripMenuItem, 
				this->rectangleToolStripMenuItem, this->circleToolStripMenuItem, this->curveToolStripMenuItem, this->textToolStripMenuItem});
			this->elementToolStripMenuItem->Name = L"elementToolStripMenuItem";
			this->elementToolStripMenuItem->Size = System::Drawing::Size(75, 24);
			this->elementToolStripMenuItem->Text = L"Element";
			this->elementToolStripMenuItem->DropDownOpening += gcnew System::EventHandler(this, &Form1::elementToolStripMenuItem_DropDownOpening);
			// 
			// lineToolStripMenuItem
			// 
			this->lineToolStripMenuItem->Checked = true;
			this->lineToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->lineToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"lineToolStripMenuItem.Image")));
			this->lineToolStripMenuItem->Name = L"lineToolStripMenuItem";
			this->lineToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D1));
			this->lineToolStripMenuItem->Size = System::Drawing::Size(194, 24);
			this->lineToolStripMenuItem->Text = L"Line";
			this->lineToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::lineToolStripMenuItem_Click);
			// 
			// rectangleToolStripMenuItem
			// 
			this->rectangleToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"rectangleToolStripMenuItem.Image")));
			this->rectangleToolStripMenuItem->Name = L"rectangleToolStripMenuItem";
			this->rectangleToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D2));
			this->rectangleToolStripMenuItem->Size = System::Drawing::Size(194, 24);
			this->rectangleToolStripMenuItem->Text = L"Rectangle";
			this->rectangleToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::rectangleToolStripMenuItem_Click);
			// 
			// circleToolStripMenuItem
			// 
			this->circleToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"circleToolStripMenuItem.Image")));
			this->circleToolStripMenuItem->Name = L"circleToolStripMenuItem";
			this->circleToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D3));
			this->circleToolStripMenuItem->Size = System::Drawing::Size(194, 24);
			this->circleToolStripMenuItem->Text = L"Circle";
			this->circleToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::circleToolStripMenuItem_Click);
			// 
			// curveToolStripMenuItem
			// 
			this->curveToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"curveToolStripMenuItem.Image")));
			this->curveToolStripMenuItem->Name = L"curveToolStripMenuItem";
			this->curveToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::D4));
			this->curveToolStripMenuItem->Size = System::Drawing::Size(194, 24);
			this->curveToolStripMenuItem->Text = L"Curve";
			this->curveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::curveToolStripMenuItem_Click);
			// 
			// textToolStripMenuItem
			// 
			this->textToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"textToolStripMenuItem.Image")));
			this->textToolStripMenuItem->Name = L"textToolStripMenuItem";
			this->textToolStripMenuItem->Size = System::Drawing::Size(194, 24);
			this->textToolStripMenuItem->Text = L"Text";
			this->textToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::textToolStripMenuItem1_Click);
			// 
			// colorToolStripMenuItem
			// 
			this->colorToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->blackToolStripMenuItem, 
				this->redToolStripMenuItem, this->greenToolStripMenuItem, this->blueToolStripMenuItem});
			this->colorToolStripMenuItem->Name = L"colorToolStripMenuItem";
			this->colorToolStripMenuItem->Size = System::Drawing::Size(57, 24);
			this->colorToolStripMenuItem->Text = L"Color";
			this->colorToolStripMenuItem->DropDownOpening += gcnew System::EventHandler(this, &Form1::colorToolStripMenuItem_DropDownOpening);
			// 
			// blackToolStripMenuItem
			// 
			this->blackToolStripMenuItem->Checked = true;
			this->blackToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->blackToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"blackToolStripMenuItem.Image")));
			this->blackToolStripMenuItem->Name = L"blackToolStripMenuItem";
			this->blackToolStripMenuItem->Size = System::Drawing::Size(117, 24);
			this->blackToolStripMenuItem->Text = L"Black";
			this->blackToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::blackToolStripMenuItem_Click);
			// 
			// redToolStripMenuItem
			// 
			this->redToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"redToolStripMenuItem.Image")));
			this->redToolStripMenuItem->Name = L"redToolStripMenuItem";
			this->redToolStripMenuItem->Size = System::Drawing::Size(117, 24);
			this->redToolStripMenuItem->Text = L"Red";
			this->redToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::redToolStripMenuItem_Click);
			// 
			// greenToolStripMenuItem
			// 
			this->greenToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"greenToolStripMenuItem.Image")));
			this->greenToolStripMenuItem->Name = L"greenToolStripMenuItem";
			this->greenToolStripMenuItem->Size = System::Drawing::Size(117, 24);
			this->greenToolStripMenuItem->Text = L"Green";
			this->greenToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::greenToolStripMenuItem_Click);
			// 
			// blueToolStripMenuItem
			// 
			this->blueToolStripMenuItem->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"blueToolStripMenuItem.Image")));
			this->blueToolStripMenuItem->Name = L"blueToolStripMenuItem";
			this->blueToolStripMenuItem->Size = System::Drawing::Size(117, 24);
			this->blueToolStripMenuItem->Text = L"Blue";
			this->blueToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::blueToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->indexToolStripMenuItem, 
				this->searchToolStripMenuItem, this->toolStripSeparator10, this->aboutToolStripMenuItem});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(53, 24);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// indexToolStripMenuItem
			// 
			this->indexToolStripMenuItem->Name = L"indexToolStripMenuItem";
			this->indexToolStripMenuItem->Size = System::Drawing::Size(122, 24);
			this->indexToolStripMenuItem->Text = L"Index";
			// 
			// searchToolStripMenuItem
			// 
			this->searchToolStripMenuItem->Name = L"searchToolStripMenuItem";
			this->searchToolStripMenuItem->Size = System::Drawing::Size(122, 24);
			this->searchToolStripMenuItem->Text = L"Search";
			// 
			// toolStripSeparator10
			// 
			this->toolStripSeparator10->Name = L"toolStripSeparator10";
			this->toolStripSeparator10->Size = System::Drawing::Size(119, 6);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(122, 24);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::aboutToolStripMenuItem_Click);
			// 
			// toolStrip1
			// 
			this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(19) {this->createToolStripButton, 
				this->openToolStripButton, this->saveToolStripButton, this->printToolStripButton, this->toolStripSeparator5, this->toolStripButton1, 
				this->toolStripButton2, this->toolStripButton3, this->toolStripButton4, this->toolStripSeparator6, this->toolStripButton5, this->toolStripButton6, 
				this->toolStripButton7, this->toolStripButton8, this->toolStripSeparator7, this->penWidthButton, this->lineStyleComboBox, this->textToolStripMenuItem1, 
				this->fontToolStripButton});
			this->toolStrip1->Location = System::Drawing::Point(0, 28);
			this->toolStrip1->Name = L"toolStrip1";
			this->toolStrip1->Size = System::Drawing::Size(682, 28);
			this->toolStrip1->TabIndex = 1;
			this->toolStrip1->Text = L"toolStrip1";
			// 
			// createToolStripButton
			// 
			this->createToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->createToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"createToolStripButton.Image")));
			this->createToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->createToolStripButton->Name = L"createToolStripButton";
			this->createToolStripButton->Size = System::Drawing::Size(23, 25);
			this->createToolStripButton->Text = L"&Create";
			this->createToolStripButton->Click += gcnew System::EventHandler(this, &Form1::createToolStripMenuItem_Click);
			// 
			// openToolStripButton
			// 
			this->openToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->openToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"openToolStripButton.Image")));
			this->openToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->openToolStripButton->Name = L"openToolStripButton";
			this->openToolStripButton->Size = System::Drawing::Size(23, 25);
			this->openToolStripButton->Text = L"&Open";
			this->openToolStripButton->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// saveToolStripButton
			// 
			this->saveToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->saveToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"saveToolStripButton.Image")));
			this->saveToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->saveToolStripButton->Name = L"saveToolStripButton";
			this->saveToolStripButton->Size = System::Drawing::Size(23, 25);
			this->saveToolStripButton->Text = L"&Save";
			this->saveToolStripButton->Click += gcnew System::EventHandler(this, &Form1::saveToolStripMenuItem_Click);
			// 
			// printToolStripButton
			// 
			this->printToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->printToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"printToolStripButton.Image")));
			this->printToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->printToolStripButton->Name = L"printToolStripButton";
			this->printToolStripButton->Size = System::Drawing::Size(23, 25);
			this->printToolStripButton->Text = L"&Print";
			this->printToolStripButton->Click += gcnew System::EventHandler(this, &Form1::printToolStripMenuItem_Click);
			// 
			// toolStripSeparator5
			// 
			this->toolStripSeparator5->Name = L"toolStripSeparator5";
			this->toolStripSeparator5->Size = System::Drawing::Size(6, 28);
			// 
			// toolStripButton1
			// 
			this->toolStripButton1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton1.Image")));
			this->toolStripButton1->ImageTransparentColor = System::Drawing::Color::White;
			this->toolStripButton1->Name = L"toolStripButton1";
			this->toolStripButton1->Size = System::Drawing::Size(23, 25);
			this->toolStripButton1->Text = L"toolStripButton1";
			this->toolStripButton1->ToolTipText = L"Draw line";
			// 
			// toolStripButton2
			// 
			this->toolStripButton2->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton2.Image")));
			this->toolStripButton2->ImageTransparentColor = System::Drawing::Color::White;
			this->toolStripButton2->Name = L"toolStripButton2";
			this->toolStripButton2->Size = System::Drawing::Size(23, 25);
			this->toolStripButton2->Text = L"toolStripButton2";
			this->toolStripButton2->ToolTipText = L"Draw rectangle";
			this->toolStripButton2->Click += gcnew System::EventHandler(this, &Form1::rectangleToolStripMenuItem_Click);
			// 
			// toolStripButton3
			// 
			this->toolStripButton3->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton3->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton3.Image")));
			this->toolStripButton3->ImageTransparentColor = System::Drawing::Color::White;
			this->toolStripButton3->Name = L"toolStripButton3";
			this->toolStripButton3->Size = System::Drawing::Size(23, 25);
			this->toolStripButton3->Text = L"toolStripButton3";
			this->toolStripButton3->ToolTipText = L"Draw circle";
			this->toolStripButton3->Click += gcnew System::EventHandler(this, &Form1::circleToolStripMenuItem_Click);
			// 
			// toolStripButton4
			// 
			this->toolStripButton4->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton4->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton4.Image")));
			this->toolStripButton4->ImageTransparentColor = System::Drawing::Color::White;
			this->toolStripButton4->Name = L"toolStripButton4";
			this->toolStripButton4->Size = System::Drawing::Size(23, 25);
			this->toolStripButton4->Text = L"toolStripButton4";
			this->toolStripButton4->ToolTipText = L"Draw curve";
			this->toolStripButton4->Click += gcnew System::EventHandler(this, &Form1::curveToolStripMenuItem_Click);
			// 
			// toolStripSeparator6
			// 
			this->toolStripSeparator6->Name = L"toolStripSeparator6";
			this->toolStripSeparator6->Size = System::Drawing::Size(6, 28);
			// 
			// toolStripButton5
			// 
			this->toolStripButton5->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton5->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton5.Image")));
			this->toolStripButton5->ImageTransparentColor = System::Drawing::Color::White;
			this->toolStripButton5->Name = L"toolStripButton5";
			this->toolStripButton5->Size = System::Drawing::Size(23, 25);
			this->toolStripButton5->Text = L"toolStripButton5";
			this->toolStripButton5->ToolTipText = L"Draw in black";
			this->toolStripButton5->Click += gcnew System::EventHandler(this, &Form1::blackToolStripMenuItem_Click);
			// 
			// toolStripButton6
			// 
			this->toolStripButton6->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton6->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton6.Image")));
			this->toolStripButton6->ImageTransparentColor = System::Drawing::Color::White;
			this->toolStripButton6->Name = L"toolStripButton6";
			this->toolStripButton6->Size = System::Drawing::Size(23, 25);
			this->toolStripButton6->Text = L"toolStripButton6";
			this->toolStripButton6->ToolTipText = L"Draw in red";
			this->toolStripButton6->Click += gcnew System::EventHandler(this, &Form1::redToolStripMenuItem_Click);
			// 
			// toolStripButton7
			// 
			this->toolStripButton7->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton7->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton7.Image")));
			this->toolStripButton7->ImageTransparentColor = System::Drawing::Color::White;
			this->toolStripButton7->Name = L"toolStripButton7";
			this->toolStripButton7->Size = System::Drawing::Size(23, 25);
			this->toolStripButton7->Text = L"toolStripButton7";
			this->toolStripButton7->ToolTipText = L"Draw in green";
			this->toolStripButton7->Click += gcnew System::EventHandler(this, &Form1::greenToolStripMenuItem_Click);
			// 
			// toolStripButton8
			// 
			this->toolStripButton8->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->toolStripButton8->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"toolStripButton8.Image")));
			this->toolStripButton8->ImageTransparentColor = System::Drawing::Color::White;
			this->toolStripButton8->Name = L"toolStripButton8";
			this->toolStripButton8->Size = System::Drawing::Size(23, 25);
			this->toolStripButton8->Text = L"toolStripButton8";
			this->toolStripButton8->ToolTipText = L"Draw in blue";
			this->toolStripButton8->Click += gcnew System::EventHandler(this, &Form1::blueToolStripMenuItem_Click);
			// 
			// toolStripSeparator7
			// 
			this->toolStripSeparator7->Name = L"toolStripSeparator7";
			this->toolStripSeparator7->Size = System::Drawing::Size(6, 28);
			// 
			// penWidthButton
			// 
			this->penWidthButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->penWidthButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"penWidthButton.Image")));
			this->penWidthButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->penWidthButton->Name = L"penWidthButton";
			this->penWidthButton->Size = System::Drawing::Size(23, 25);
			this->penWidthButton->Text = L"toolStripButton9";
			this->penWidthButton->ToolTipText = L"Change pen width";
			this->penWidthButton->Click += gcnew System::EventHandler(this, &Form1::penWidthButton_Click);
			// 
			// lineStyleComboBox
			// 
			this->lineStyleComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->lineStyleComboBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->lineStyleComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"Solid lines", L"Dashed lines", L"Dotted lines", 
				L"Dash-dotted lines", L"Dash-dot-dotted lines"});
			this->lineStyleComboBox->Name = L"lineStyleComboBox";
			this->lineStyleComboBox->Size = System::Drawing::Size(150, 28);
			this->lineStyleComboBox->ToolTipText = L"Choose line style";
			this->lineStyleComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &Form1::lineStyleComboBox_SelectedIndexChanged);
			// 
			// textToolStripMenuItem1
			// 
			this->textToolStripMenuItem1->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->textToolStripMenuItem1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"textToolStripMenuItem1.Image")));
			this->textToolStripMenuItem1->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->textToolStripMenuItem1->Name = L"textToolStripMenuItem1";
			this->textToolStripMenuItem1->Size = System::Drawing::Size(23, 25);
			this->textToolStripMenuItem1->Text = L"toolStripButton9";
			this->textToolStripMenuItem1->ToolTipText = L"Input text";
			this->textToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::textToolStripMenuItem1_Click);
			// 
			// fontToolStripButton
			// 
			this->fontToolStripButton->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Image;
			this->fontToolStripButton->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"fontToolStripButton.Image")));
			this->fontToolStripButton->ImageTransparentColor = System::Drawing::Color::Magenta;
			this->fontToolStripButton->Name = L"fontToolStripButton";
			this->fontToolStripButton->Size = System::Drawing::Size(23, 25);
			this->fontToolStripButton->Text = L"toolStripButton9";
			this->fontToolStripButton->Click += gcnew System::EventHandler(this, &Form1::fontToolStripButton_Click);
			// 
			// contextMenuStrip1
			// 
			this->contextMenuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(14) {this->sendToBackContextMenuItem, 
				this->deleteContextMenuItem, this->moveContextMenuItem, this->contextSeparator, this->lineContextMenuItem, this->rectangleContextMenuItem, 
				this->circleContextMenuItem, this->curveContextMenuItem, this->blackContextMenuItem, this->redContextMenuItem, this->greenContextMenuItem, 
				this->blueContextMenuItem, this->toolStripSeparator8, this->textToolStripMenuItem2});
			this->contextMenuStrip1->Name = L"contextMenuStrip1";
			this->contextMenuStrip1->Size = System::Drawing::Size(165, 304);
			this->contextMenuStrip1->Opening += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::contextMenuStrip1_Opening);
			// 
			// sendToBackContextMenuItem
			// 
			this->sendToBackContextMenuItem->Name = L"sendToBackContextMenuItem";
			this->sendToBackContextMenuItem->Size = System::Drawing::Size(164, 24);
			this->sendToBackContextMenuItem->Text = L"Send to Back";
			this->sendToBackContextMenuItem->Click += gcnew System::EventHandler(this, &Form1::sendToBackContextMenuItem_Click);
			// 
			// deleteContextMenuItem
			// 
			this->deleteContextMenuItem->Name = L"deleteContextMenuItem";
			this->deleteContextMenuItem->Size = System::Drawing::Size(164, 24);
			this->deleteContextMenuItem->Text = L"Delete";
			this->deleteContextMenuItem->Click += gcnew System::EventHandler(this, &Form1::deleteContextMenuItem_Click);
			// 
			// moveContextMenuItem
			// 
			this->moveContextMenuItem->Name = L"moveContextMenuItem";
			this->moveContextMenuItem->Size = System::Drawing::Size(164, 24);
			this->moveContextMenuItem->Text = L"Move";
			this->moveContextMenuItem->Click += gcnew System::EventHandler(this, &Form1::moveContextMenuItem_Click);
			// 
			// contextSeparator
			// 
			this->contextSeparator->Name = L"contextSeparator";
			this->contextSeparator->Size = System::Drawing::Size(161, 6);
			// 
			// lineContextMenuItem
			// 
			this->lineContextMenuItem->Name = L"lineContextMenuItem";
			this->lineContextMenuItem->Size = System::Drawing::Size(164, 24);
			this->lineContextMenuItem->Text = L"Line";
			// 
			// rectangleContextMenuItem
			// 
			this->rectangleContextMenuItem->Name = L"rectangleContextMenuItem";
			this->rectangleContextMenuItem->Size = System::Drawing::Size(164, 24);
			this->rectangleContextMenuItem->Text = L"Rectangle";
			// 
			// circleContextMenuItem
			// 
			this->circleContextMenuItem->Name = L"circleContextMenuItem";
			this->circleContextMenuItem->Size = System::Drawing::Size(164, 24);
			this->circleContextMenuItem->Text = L"Circle";
			// 
			// curveContextMenuItem
			// 
			this->curveContextMenuItem->Name = L"curveContextMenuItem";
			this->curveContextMenuItem->Size = System::Drawing::Size(164, 24);
			this->curveContextMenuItem->Text = L"Curve";
			// 
			// blackContextMenuItem
			// 
			this->blackContextMenuItem->Name = L"blackContextMenuItem";
			this->blackContextMenuItem->Size = System::Drawing::Size(164, 24);
			this->blackContextMenuItem->Text = L"Black";
			// 
			// redContextMenuItem
			// 
			this->redContextMenuItem->Name = L"redContextMenuItem";
			this->redContextMenuItem->Size = System::Drawing::Size(164, 24);
			this->redContextMenuItem->Text = L"Red";
			// 
			// greenContextMenuItem
			// 
			this->greenContextMenuItem->Name = L"greenContextMenuItem";
			this->greenContextMenuItem->Size = System::Drawing::Size(164, 24);
			this->greenContextMenuItem->Text = L"Green";
			// 
			// blueContextMenuItem
			// 
			this->blueContextMenuItem->Name = L"blueContextMenuItem";
			this->blueContextMenuItem->Size = System::Drawing::Size(164, 24);
			this->blueContextMenuItem->Text = L"Blue";
			// 
			// toolStripSeparator8
			// 
			this->toolStripSeparator8->Name = L"toolStripSeparator8";
			this->toolStripSeparator8->Size = System::Drawing::Size(161, 6);
			// 
			// textToolStripMenuItem2
			// 
			this->textToolStripMenuItem2->Name = L"textToolStripMenuItem2";
			this->textToolStripMenuItem2->Size = System::Drawing::Size(164, 24);
			this->textToolStripMenuItem2->Text = L"Text";
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"Sketch";
			this->openFileDialog->Filter = L"Saved Sketches|*.ske| All files|*.*";
			this->openFileDialog->FilterIndex = 2;
			this->openFileDialog->InitialDirectory = L"C:\\Users\\Jafar\\Documents\\Visual C++\\Applications\\Sketcher\\Sketcher\\Saved Sketches" 
				L"";
			this->openFileDialog->Title = L"Open file";
			// 
			// saveFileDialog
			// 
			this->saveFileDialog->Filter = L"Saved Sketches|*.ske| All files|*.*";
			this->saveFileDialog->FilterIndex = 2;
			this->saveFileDialog->InitialDirectory = L"C:\\Users\\Jafar\\Documents\\Visual C++\\Applications\\Sketcher\\Sketcher\\Saved Sketches" 
				L"";
			this->saveFileDialog->Title = L"Save file";
			// 
			// printDocument
			// 
			this->printDocument->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &Form1::printDocument_PrintPage);
			// 
			// printDialog
			// 
			this->printDialog->Document = this->printDocument;
			this->printDialog->UseEXDialog = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlLightLight;
			this->ClientSize = System::Drawing::Size(682, 405);
			this->ContextMenuStrip = this->contextMenuStrip1;
			this->Controls->Add(this->toolStrip1);
			this->Controls->Add(this->menuStrip1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Sketcher";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			//this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Click += gcnew System::EventHandler(this, &Form1::lineToolStripMenuItem_Click);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->toolStrip1->ResumeLayout(false);
			this->toolStrip1->PerformLayout();
			this->contextMenuStrip1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

//=============================================================================================================
private:
		ElementType elementType;	//текущий элемент		Я добавил!!!
		Color color;				//текущая краска			Я добавил!!!

private: System::Void lineToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
			 //sender -- это объект пункта меню,	е -- это информация, относящиеся к данному событию.
			 elementType = ElementType::LINE;
			 SetElementTypeButtonsState();
		 }
private: System::Void rectangleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 elementType = ElementType::RECTANGLE;
			 SetElementTypeButtonsState();
		 }
private: System::Void circleToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 elementType = ElementType::CIRCLE;
			 SetElementTypeButtonsState();
		 }
private: System::Void curveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 elementType = ElementType::CURVE;
			 SetElementTypeButtonsState();
		 }

private: System::Void blackToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 color = Color::Black;
			 SetColorButtonsState();
		 }
private: System::Void redToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 color = Color::Red;
			 SetColorButtonsState();
		 }
private: System::Void greenToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 color = Color::Green;
			 SetColorButtonsState();
		 }
private: System::Void blueToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 color = Color::Blue;
			 SetColorButtonsState();
		 }
private: System::Void elementToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e) {
			 //Этот обработчик будет выполнятся перед отображением раскрывающегося меню Element
			 lineToolStripMenuItem->Checked = elementType == ElementType::LINE;
			 rectangleToolStripMenuItem->Checked = elementType == ElementType::RECTANGLE;
			 circleToolStripMenuItem->Checked = elementType == ElementType::CIRCLE;
			 curveToolStripMenuItem->Checked = elementType == ElementType::CURVE;
		 }
private: System::Void colorToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e) {
			 //Если условие для asой либо строки выполнится, то галочка ставится в определённую линию.
			 blackToolStripMenuItem->Checked = color == Color::Black;
			 redToolStripMenuItem->Checked = color == Color::Red;
			 greenToolStripMenuItem->Checked = color == Color::Green;
			 blueToolStripMenuItem->Checked = color == Color::Blue;
		 }


		 void SetElementTypeButtonsState(void)		//Я объявил!!!		устанавливает состояния кнопок типа элемента
		 {
			 toolStripButton1->Checked = elementType == ElementType::LINE;
			 toolStripButton2->Checked = elementType == ElementType::RECTANGLE;
			 toolStripButton3->Checked = elementType == ElementType::CIRCLE;
			 toolStripButton4->Checked = elementType == ElementType::CURVE;
			 textToolStripMenuItem1->Checked = elementType == ElementType::TEXT;
		 }

		 void SetColorButtonsState(void)			//Я объявил!!!		устанавливает состояния кнопок цветов.
		 {
			 toolStripButton5->Checked = color == Color::Black;
			 toolStripButton6->Checked = color == Color::Red;
			 toolStripButton7->Checked = color == Color::Green;
			 toolStripButton8->Checked = color == Color::Blue;
		 }

//=============================================================================================================
		 
		 bool drawing;		        // Drawing in progress when true,			Я добавил!!!
		 Point firstPoint;			// Records initial mouse cursor position,		Я добавил!!!
		 Element^ tempElement;		//Временный объект текущего типа		Я добавил!!!
		 Sketch^ sketch;			// Stores the whole sketch					Я доюавил!!!
		 Element^ highlightedElement;	// Currently highlighted element			Я доюавил!!!

private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
			 Graphics^ g = e->Graphics;
			 sketch->Draw(g);
			 if(tempElement != nullptr) tempElement->Draw(g);
		 }
private: System::Void Form1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 //предоставляет инфо о самом событии
			 if(e->Button == System::Windows::Forms::MouseButtons::Left)
			 {
				 firstPoint = e->Location;
				 if(mode == Mode::Normal)
				 {
					 if(elementType == ElementType::TEXT)
					 {
						 textDialog->TextString = L"";        // Reset the text box string  
						 textDialog->TextFont = textFont;     // Set the font for the edit box
						 if(textDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
						 {
							 tempElement = gcnew TextElement(color, firstPoint, textDialog->TextString, textFont);
							 sketch += tempElement;
							 sketch->saved = false;             // Sketch has changed so mark it not saved
							 Invalidate(tempElement->bound);    // The text element region
							 tempElement = nullptr;
							 Update();
						 }
						 drawing = false;
					 }
					 else drawing = true;
				 }
			 }
		 }
private: System::Void Form1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(drawing)
			 {
				 if(tempElement)
					 Invalidate(tempElement->bound);	//объявляет boundRec tempElement-а недествительной облстью
				 //это означает, что при перерисовке не рисует вся область, а только элемент указанный в аргументе.
				 switch(elementType)
				 {
				 case ElementType::LINE:
					 tempElement = gcnew Line(color, firstPoint, e->Location, penWidth, lineStyle);
					 break;
				 case ElementType::RECTANGLE:
					 tempElement = gcnew Rectangle(color, firstPoint, e->Location, penWidth, lineStyle);
					 break;
				 case ElementType::CIRCLE:
					 tempElement = gcnew Circle(color, firstPoint, e->Location, penWidth, lineStyle);
					 break;
				 case ElementType::CURVE:
					 if(tempElement)
						 safe_cast<Curve^>(tempElement)->Add(e->Location);
					 else
						 tempElement = gcnew Curve(color, firstPoint, e->Location, penWidth, lineStyle);
					 break;
				 }
				 //Invalidate();		//Инициализация повторной прорисовки формы.
				 Invalidate(tempElement->bound);                 // Invalidate new element area
				 Update();		//перерисовка недействительной части формы, которую указала функция Invalidate().
			 }

			 else if(mode == Mode::Normal)
			 {
				 // Find the element under the cursor - if any
				 Element^ element(sketch->HitElement(e->Location));
				 if(highlightedElement == element)        // If the old is same as the new
					 return;                                // there's nothing to do

				 // Reset any existing highlighted element
				 if(highlightedElement)
				 {
					 Invalidate(highlightedElement->bound);  // Invalidate element area
					 highlightedElement->highlighted = false;
					 highlightedElement = nullptr;
				 }
				 // Find and set new highlighted element, if any
				 highlightedElement = element;
				 if(highlightedElement)
				 {
					 highlightedElement->highlighted = true;
					 Invalidate(highlightedElement->bound);  // Invalidate element area
				 }
				 Update();                                 // Send a paint message
			 }
			 else if(mode == Mode::Move && e->Button == System::Windows::Forms::MouseButtons::Left)
			 {  // Move the highlighted element
				 if(highlightedElement)
				 {
					 sketch->saved = false;                       // Mark sketch as not saved
					 Invalidate(highlightedElement->bound);    // Region before move
					 highlightedElement->Move(e->X - firstPoint.X, e->Y - firstPoint.Y);
					 firstPoint = e->Location;
					 Invalidate(highlightedElement->bound);     // Region after move
					 Update();
				 }
			 }
		 }
private: System::Void Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if(!drawing)
			 {
				 mode = Mode::Normal;
				 return;
			 }
			 if(tempElement)
			 {
				 sketch += tempElement;
				 sketch->saved = false;           // Sketch has changed so mark it not saved
				 tempElement = nullptr;
				 Invalidate();
			 }
			 drawing = false;
		 }

//=============================================================================================================
//Перемещение элементов.
		 Mode mode;

private: System::Void contextMenuStrip1_Opening(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {
			 //Выполнятся перед открытием контексного менью.
			 contextMenuStrip1->Items->Clear();    // Remove existing items
			 if(highlightedElement)
			 {
				 contextMenuStrip1->Items->Add(moveContextMenuItem);
				 contextMenuStrip1->Items->Add(deleteContextMenuItem);
				 contextMenuStrip1->Items->Add(sendToBackContextMenuItem);
			 }
			 else
			 {
				 contextMenuStrip1->Items->Add(lineContextMenuItem);
				 contextMenuStrip1->Items->Add(rectangleContextMenuItem);
				 contextMenuStrip1->Items->Add(circleContextMenuItem);
				 contextMenuStrip1->Items->Add(curveContextMenuItem);
				 contextMenuStrip1->Items->Add(textToolStripMenuItem2);
				 contextMenuStrip1->Items->Add(contextSeparator);
				 contextMenuStrip1->Items->Add(blackContextMenuItem);
				 contextMenuStrip1->Items->Add(redContextMenuItem);
				 contextMenuStrip1->Items->Add(greenContextMenuItem);
				 contextMenuStrip1->Items->Add(blueContextMenuItem);

				 // Set checks for the menu items
				 lineContextMenuItem->Checked = elementType == ElementType::LINE;
				 rectangleContextMenuItem->Checked = elementType == ElementType::RECTANGLE;
				 circleContextMenuItem->Checked = elementType == ElementType::CIRCLE;
				 curveContextMenuItem->Checked = elementType == ElementType::CURVE;
				 textToolStripMenuItem2->Checked = elementType == ElementType::TEXT;
				 blackContextMenuItem->Checked = color == Color::Black;
				 redContextMenuItem->Checked = color == Color::Red;
				 greenContextMenuItem->Checked = color == Color::Green;
				 blueContextMenuItem->Checked = color == Color::Blue;
			 }
		 }
private: System::Void deleteContextMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(highlightedElement)
			 {
				 sketch->saved = false;                     // Mark sketch as not saved
				 sketch -= highlightedElement;              // Delete the highlighted element
				 Invalidate(highlightedElement->bound);
				 highlightedElement = nullptr;
				 Update();
			 }
		 }
private: System::Void sendToBackContextMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(highlightedElement)
			 {
				 sketch->saved = false;                      // Mark sketch as not saved
				 sketch -= highlightedElement;               // Delete the highlighted element
				 sketch->Push_front(highlightedElement);     // then add it back to the beginning
				 highlightedElement->highlighted = false;
				 Invalidate(highlightedElement->bound);
				 highlightedElement = nullptr;
				 Update();
			 }
		 }
private: System::Void moveContextMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 mode = Mode::Move;
		 }

//=============================================================================================================
		 
		 PenDialog^ penDialog;		// The pen width dialog object
		 float penWidth;			// Current pen width
		 DashStyle lineStyle;		// Current line drawing style
		 System::Drawing::Font^ textFont;		// Font for drawing text
		 TextDialog^ textDialog;	// The text dialog object

private: System::Void penWidthButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(penDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				 //ShowDialog() -- открывает диалоговое окно и возвращает значения  доступных в перечислении:
				 //System::Window::Forms::DialogResult: None, OK, Cancel, Abort, Retry, Ignore, Yes, No.
				 penWidth = penDialog->PenWidth;      // Get the pen width
			 }
		 }
private: System::Void lineStyleComboBox_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
			 switch(lineStyleComboBox->SelectedIndex)
			 {
			 case 1:
				 lineStyle = DashStyle::Dash;
				 break;    
			 case 2:
				 lineStyle = DashStyle::Dot;
				 break;    
			 case 3:
				 lineStyle = DashStyle::DashDot;
				 break;    
			 case 4:
				 lineStyle = DashStyle::DashDotDot;
				 break;    
			 default:
				 lineStyle = DashStyle::Solid;
				 break;    
			 }
		 }
private: System::Void textToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
			 elementType = ElementType::TEXT;
			 SetElementTypeButtonsState();
		 }
private: System::Void fontToolStripButton_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(fontDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				 textFont = fontDialog1->Font;
			 }
		 }

//=============================================================================================================
		 BinaryFormatter^ formatter;
		 String^ sketchFilePath;			//путь к файлу эскиза

		 void SaveSketch(void)
		 {
			 if(sketch->saved)
				 return;                // Nothing to do because the sketch was not modified

			 if(sketchFilePath == nullptr)
			 {
				 // File has not yet been saved before, so show the save dialog
				 SaveSketchAs();
			 }
			 else
			 {
				 // File has been saved before, so just save it using the same name
				 Stream^ stream = File::OpenWrite(sketchFilePath);            
				 formatter->Serialize(stream, sketch);
				 stream->Close();
			 }
		 }

		 void SaveSketchAs(void)
		 {
			 if(saveFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				 Stream^ stream = File::Open(saveFileDialog->FileName, FileMode::Create);
				 if(stream != nullptr)
				 {
					 formatter->Serialize(stream, sketch);
					 stream->Close();
					 sketchFilePath = saveFileDialog->FileName;
					 sketch->saved = true;
				 }
				 else	//если файл не был создан
				 {
					 MessageBox::Show(L"Failed to create sketch file stream!");
				 }
			 }
		 }

		 void SaveSketchCheck(void)
		 {
			 if(!sketch->saved)
			 {
				 String^ message = L"The current sketch is not saved.\nSave the current sketch?";
				 String^ caption = L"Sketch Not Saved";
				 MessageBoxButtons buttons = MessageBoxButtons::YesNo;

				 // Displays the MessageBox to warn about unsaved sketch
				 if ( MessageBox::Show(this, message, caption, buttons) ==
					 System::Windows::Forms::DialogResult::Yes)
				 {
					 SaveSketch();
				 }
			 }
		 }

private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 SaveSketch();
		 }
private: System::Void saveasToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 SaveSketchAs();
		 }
private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 Stream^ stream;
			 if(!sketch->saved)
			 {
				 String^ message = L"The current sketch is not saved.\nSave the current sketch?";
				 String^ caption = L"Sketch Not Saved";
				 MessageBoxButtons buttons = MessageBoxButtons::YesNo;

				 // Displays the MessageBox to warn about unsaved sketch
				 if (MessageBox::Show(this, message, caption, buttons) == System::Windows::Forms::DialogResult::Yes)
				 {
					 //Перечмсления MessageBoxButton, определяющее кнопки, которые будут включены в окно сообщений.
					 //Перечисления MessageBoxButton:	OK, OKCancel, AbortRetryIgnore, YesNoCancel, YesNo и RetryCancel.
					 SaveSketch();
				 }
			 }

			 // Now open a new sketch
			 if(openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			 {
				 stream = openFileDialog->OpenFile();
					//возвращает ссылку на поток, инкапсулирующий выбранный в диалоговом окне файл.
				 if(stream != nullptr)
				 {
					 sketch = safe_cast<Sketch^>(formatter->Deserialize(stream));
					 stream->Close();
					 sketch->saved = true;
					 sketchFilePath = openFileDialog->FileName;
					 Invalidate();
				 }
			 }
		 }
private: System::Void createToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 SaveSketchCheck();
			 sketch = gcnew Sketch();
			 sketchFilePath = nullptr;
			 Invalidate();
			 Update();
		 }
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
			 SaveSketchCheck();
		 }
private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 SaveSketchCheck();
			 Close();
		 }
private: System::Void printDocument_PrintPage(System::Object^  sender, System::Drawing::Printing::PrintPageEventArgs^  e) {
			 sketch->Draw(e->Graphics);
		 }
private: System::Void printToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(printDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 printDocument->Print();
		 }
private: System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
			 String^ message = L"This program made by programmer from Tajikistan - Jafar";
			 String^ caption = L"About creator";
			 MessageBoxButtons button = MessageBoxButtons::OK;
			 MessageBox::Show(this, message, caption,  button);
		 }
};
}


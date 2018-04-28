#pragma once

namespace Sketcher {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ TextDialog
	/// </summary>
	public ref class TextDialog : public System::Windows::Forms::Form
	{
	public:
		TextDialog(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~TextDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  textOKButton;
	private: System::Windows::Forms::Button^  textCancelButton;
	private: System::Windows::Forms::TextBox^  textBox1;
	protected: 


	protected: 

	private:
		/// <summary>
		/// “ребуетс€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ќб€зательный метод дл€ поддержки конструктора - не измен€йте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textOKButton = (gcnew System::Windows::Forms::Button());
			this->textCancelButton = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textOKButton
			// 
			this->textOKButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->textOKButton->Location = System::Drawing::Point(482, 12);
			this->textOKButton->Name = L"textOKButton";
			this->textOKButton->Size = System::Drawing::Size(100, 40);
			this->textOKButton->TabIndex = 1;
			this->textOKButton->Text = L"OK";
			this->textOKButton->UseVisualStyleBackColor = true;
			// 
			// textCancelButton
			// 
			this->textCancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->textCancelButton->Location = System::Drawing::Point(482, 58);
			this->textCancelButton->Name = L"textCancelButton";
			this->textCancelButton->Size = System::Drawing::Size(100, 40);
			this->textCancelButton->TabIndex = 2;
			this->textCancelButton->Text = L"Cancel";
			this->textCancelButton->UseVisualStyleBackColor = true;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 12);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(442, 86);
			this->textBox1->TabIndex = 0;
			// 
			// TextDialog
			// 
			this->AcceptButton = this->textOKButton;
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->textCancelButton;
			this->ClientSize = System::Drawing::Size(594, 107);
			this->ControlBox = false;
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->textCancelButton);
			this->Controls->Add(this->textOKButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"TextDialog";
			this->Text = L"Create Text Element";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public: property String^ TextString
			{
				String^ get() {return textBox1->Text; }
				void set(String^ text) { textBox1->Text = text; }
			}
	public: property System::Drawing::Font^ TextFont
			{
				void set(System::Drawing::Font^ font) { textBox1->Font = font; }
			}

	
	};
}

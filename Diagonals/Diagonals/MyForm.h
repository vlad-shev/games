#pragma once
#include "Table.h"
namespace Diagonals {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  pl1;
	private: System::Windows::Forms::TextBox^  pl2;
			 Table^ table;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pl1 = (gcnew System::Windows::Forms::TextBox());
			this->pl2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(227, 129);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(96, 47);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Новая игра";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(224, 23);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(62, 29);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Игрок 1: ";
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(224, 52);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(62, 29);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Игрок 2: ";
			// 
			// pl1
			// 
			this->pl1->Location = System::Drawing::Point(292, 23);
			this->pl1->Name = L"pl1";
			this->pl1->ReadOnly = true;
			this->pl1->Size = System::Drawing::Size(30, 20);
			this->pl1->TabIndex = 3;
			// 
			// pl2
			// 
			this->pl2->Location = System::Drawing::Point(292, 52);
			this->pl2->Name = L"pl2";
			this->pl2->ReadOnly = true;
			this->pl2->Size = System::Drawing::Size(30, 20);
			this->pl2->TabIndex = 4;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(335, 211);
			this->Controls->Add(this->pl2);
			this->Controls->Add(this->pl1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		table = gcnew Table(this);
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				table->getFieldFromTable(i, j)->getPicture()->MouseClick +=
					gcnew MouseEventHandler(this, &MyForm::table_Click);
	}
	private: System::Void table_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		table->setMark(table->getFieldFromTable(sender));
		pl1->Text = Convert::ToString(table->getPl1());
		pl2->Text = Convert::ToString(table->getPl2());
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		table->Clear();
		table = gcnew Table(this);
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
				table->getFieldFromTable(i, j)->getPicture()->MouseClick +=
				gcnew MouseEventHandler(this, &MyForm::table_Click);
	}
	};
}
#pragma once
#include "Table.h"
namespace test {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MyForm
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
		/// ќсвободить все используемые ресурсы.
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
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		Table^ table;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::NumericUpDown^  NUD1;
	private: System::Windows::Forms::NumericUpDown^  NUD2;
			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->NUD1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->NUD2 = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NUD1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NUD2))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(509, 237);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(111, 50);
			this->button1->TabIndex = 0;
			this->button1->Text = L"ѕерезапустить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(509, 181);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(111, 50);
			this->button2->TabIndex = 1;
			this->button2->Text = L"ќткрыть пол€";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// NUD1
			// 
			this->NUD1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->NUD1->Location = System::Drawing::Point(509, 139);
			this->NUD1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 0 });
			this->NUD1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->NUD1->Name = L"NUD1";
			this->NUD1->Size = System::Drawing::Size(43, 26);
			this->NUD1->TabIndex = 2;
			this->NUD1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 25, 0, 0, 0 });
			// 
			// NUD2
			// 
			this->NUD2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->NUD2->Location = System::Drawing::Point(577, 139);
			this->NUD2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 15, 0, 0, 0 });
			this->NUD2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->NUD2->Name = L"NUD2";
			this->NUD2->Size = System::Drawing::Size(43, 26);
			this->NUD2->TabIndex = 3;
			this->NUD2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 15, 0, 0, 0 });
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
				static_cast<System::Int32>(static_cast<System::Byte>(224)));
			this->ClientSize = System::Drawing::Size(632, 299);
			this->Controls->Add(this->NUD2);
			this->Controls->Add(this->NUD1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"—апер";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NUD1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NUD2))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		table = gcnew Table((int)NUD1->Value, (int)NUD2->Value, this);
		for(int i = 0; i < (int)NUD1->Value; i++)
			for (int j = 0; j < (int)NUD2->Value; j++)
			{
				PictureBox^ pb = table->get_matrix()[i, j]->getPB();
				pb->MouseClick += gcnew MouseEventHandler(this, &MyForm::pb_MouseClick);
			}
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		table->Refresh((int)NUD1->Value, (int)NUD2->Value);
		for (int i = 0; i < (int)NUD1->Value; i++)
			for (int j = 0; j < (int)NUD2->Value; j++)
			{
				PictureBox^ pb = table->get_matrix()[i, j]->getPB();
				pb->MouseClick += gcnew MouseEventHandler(this, &MyForm::pb_MouseClick);
			}
	};
	private: System::Void pb_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		Field^ field = table->find(sender);
		if (e->Button == Windows::Forms::MouseButtons::Left)
			table->openField(table->find(sender));
		if (e->Button == Windows::Forms::MouseButtons::Right)
			field->checkFlag();
	}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e)
{
	table->openAll();
}
};
}

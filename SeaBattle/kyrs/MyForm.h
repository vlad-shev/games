#pragma once
#include "Game.h"
namespace kyrs {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}
	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
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
		/// ������������ ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

	private: System::Windows::Forms::Button^  button1;//������ ����� ����-�������� ������
			 Game^ game;//���������� ����

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ��������� ����� ��� ��������� ������������ � �� ��������� 
		/// ���������� ����� ������ � ������� ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(506, 70);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(99, 61);
			this->button1->TabIndex = 1;
			this->button1->Text = L"����� ����";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(617, 213);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		game = gcnew Game(this);//������� � ��������� ������� ���� � ���������
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				game->getComputerTable()->getFieldFromTable(i, j)->getPicture()->MouseClick +=
					gcnew MouseEventHandler(this, &MyForm::computerTable_Click);//���� ������ �� ������� �������
				game->getPlayerTable()->getFieldFromTable(i, j)->getPicture()->MouseClick +=
					gcnew MouseEventHandler(this, &MyForm::userTable_Click);
			}
	}
	private: System::Void userTable_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) 
	{
		if (e->Button == Windows::Forms::MouseButtons::Left)
			game->LeftClickOnPlayerTable(sender);
		if (e->Button == Windows::Forms::MouseButtons::Right)
			game->RightClickOnPlayerTable(sender);
	}
	private: System::Void computerTable_Click(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
	{
		game->PlayerShot(sender);
		game->ComputerShot();
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		game->Clear();//�������� � �.�����
		game = gcnew Game(this);
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				game->getComputerTable()->getFieldFromTable(i, j)->getPicture()->MouseClick +=
					gcnew MouseEventHandler(this, &MyForm::computerTable_Click);
				game->getPlayerTable()->getFieldFromTable(i, j)->getPicture()->MouseClick +=
					gcnew MouseEventHandler(this, &MyForm::userTable_Click);
			}
	}
	};
}
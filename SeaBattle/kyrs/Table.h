#pragma once
#include "Field.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
ref class Table
{
private:
	const int width = 10;
	const int height = 10;
	int indent;// ������ ����� ����
	array<Field^, 2>^ table;
	void generate()
	{
		table = gcnew array<Field^, 2>(width, height);
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				table[i, j] = gcnew Field();// ������� ����
				table[i, j]->setDefaultStyle(i, j, indent);// ������� �������� PB
			}

	}
public:
	Table(int i)
	{
		indent = i;
		generate();
	}
	List<Field^>^ getUnavailable(int i, int j)
	{
		List<Field^>^ Near = gcnew List<Field^>;
		if (i - 1 >= 0 && j - 1 >= 0) Near->Add(table[i - 1, j - 1]);
		if (j - 1 >= 0) Near->Add(table[i, j - 1]);
		if (i + 1 < width && j - 1 >= 0) Near->Add(table[i + 1, j - 1]);
		if (i + 1 < width) Near->Add(table[i + 1, j]);
		if (i - 1 >= 0) Near->Add(table[i - 1, j]);
		if (i - 1 >= 0 && j + 1 < height) Near->Add(table[i - 1, j + 1]);
		if (j + 1 < height) Near->Add(table[i, j + 1]);
		if (i + 1 < width && j + 1 < height) Near->Add(table[i + 1, j + 1]);
		return Near;
	}
	Field^ getFieldFromTable(System::Object^ obj)
	{
		for (int i = 0; i < width; i++)//����� �������� ������ ������ �� ���� ���� 
			for (int j = 0; j < height; j++)
				if (obj->Equals(table[i, j]->getPicture()))
					return table[i, j];
	}
	Field^ getFieldFromTable(int i, int j)// �������� �� ����������� 
	{
		return table[i, j];
	}

	int getIndent()  //�������� ������ � ������������ ����� ����
	{
		return indent;
	}
	void openUnhitted() //�������� ���� ���������� �����
	{
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				if (!table[i, j]->isHitted())
					table[i, j]->setHitted();
	}
};

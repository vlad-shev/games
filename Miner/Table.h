#pragma once
#include "Field.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
ref class Table
{
private:
	Form^ form;
	int width;
	int height;
	int bombsCount;
	int unopened;
	array<Field^, 2>^ matrix;
	void generate() 
	{
		matrix = gcnew array<Field^, 2>(width, height);
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				matrix[i, j] = gcnew Field();
				matrix[i, j]->setLocation(20*i, 20*j);
				matrix[i, j]->getPB()->BorderStyle = BorderStyle::FixedSingle;
				matrix[i, j]->getPB()->Size = System::Drawing::Size(20, 20);
				matrix[i, j]->getPB()->SizeMode = PictureBoxSizeMode::Zoom;
				matrix[i, j]->getPB()->Image = Image::FromFile("icons/closed.png");
				form->Controls->Add(matrix[i, j]->getPB());
			}

	}
	void setBombs()
	{
		setBombCount();
		int count = bombsCount;
		Random^ rand = gcnew Random;
		while (count)
		{
			int i = rand->Next(0, width);
			int j = rand->Next(0, height);
			if (matrix[i, j]->getBomb())
				continue;
			else
				matrix[i, j]->setBomb();
			count--;
		}
	}
	void countAllNearbyBombs()
	{
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				int count = 0;
				if (i - 1 >= 0 && j - 1 >= 0) count += matrix[i - 1, j - 1]->getBomb();
				if (j - 1 >= 0) count += matrix[i, j - 1]->getBomb();
				if (i + 1 < width && j - 1 >= 0) count += matrix[i + 1, j - 1]->getBomb(); ;
				if (i + 1 < width) count += matrix[i + 1, j]->getBomb(); ;
				if (i - 1 >= 0 ) count += matrix[i - 1, j]->getBomb() ;
				if (i - 1 >= 0 && j + 1 < height) count += matrix[i - 1, j + 1]->getBomb();
				if (j + 1 < height) count += matrix[i, j + 1]->getBomb(); ;
				if (i + 1 < width && j + 1 < height) count += matrix[i + 1, j + 1]->getBomb();
				matrix[i, j]->setNearbyBombCount(count);
			}
	}
public:
	Table(int w, int h, Form^ f)
	{
		if (w < 4 || h < 4) 
			throw gcnew Exception("Enter numbs >4");
		form = f;
		width = w;
		height = h;
		setUnopened();
		setBombCount();
		generate();
		setBombs();
		countAllNearbyBombs();
	}
	void Refresh(int w, int h) 
	{
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				form->Controls->Remove(matrix[i, j]->getPB());
		setWH(w, h);
		setBombCount();
		setUnopened();
		matrix = gcnew array<Field^, 2>(width, height);
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				matrix[i, j] = gcnew Field();
				matrix[i, j]->setLocation(20 * i, 20 * j);
				matrix[i, j]->getPB()->BorderStyle = BorderStyle::FixedSingle;
				matrix[i, j]->getPB()->Size = System::Drawing::Size(20, 20);
				matrix[i, j]->getPB()->SizeMode = PictureBoxSizeMode::Zoom;
				matrix[i, j]->getPB()->Image = Image::FromFile("icons/closed.png");
				form->Controls->Add(matrix[i, j]->getPB());
			}
		setBombs();
		countAllNearbyBombs();
	}
	void setUnopened() 
	{
		unopened = width * height;
	}
	void setBombCount()
	{
		bombsCount = (double)width * height / 100 * 26;
	}
	void setWH(int w, int h)
	{
		width = w;
		height = h;
		setBombCount();
	}
	Field^ find(System::Object^ obj)
	{
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)

				if (obj->Equals(matrix[i, j]->getPB()))
					return matrix[i, j];
	}
	array<Field^, 2>^ get_matrix()
	{return matrix;}
	void openAll()
	{
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				matrix[i, j]->openAny();
	}
	void openField(Field^ field)
	{
		if (field->getBomb() && !field->isFlaged())
		{
			field->showBomb();
			openAll();
		}
		else
		{
			field->open();
			unopened -= 1;
			if (!field->getNearbyBombCount()) openNearby(field);
		}
		if (unopened == bombsCount) openAll();
	}
	void openNearby(Field^ field) 
	{
		int i = field->getX() / 20;
		int j = field->getY() / 20;
		List<Field^> near;
		if (i - 1 >= 0 && j - 1 >= 0) near.Add(matrix[i - 1, j - 1]);
		if (j - 1 >= 0) near.Add(matrix[i, j - 1]);
		if (i + 1 < width && j - 1 >= 0) near.Add(matrix[i + 1, j - 1]);
		if (i + 1 < width) near.Add(matrix[i + 1, j]);
		if (i - 1 >= 0) near.Add(matrix[i - 1, j]);
		if (i - 1 >= 0 && j + 1 < height) near.Add(matrix[i - 1, j + 1]);
		if (j + 1 < height) near.Add(matrix[i, j + 1]);
		if (i + 1 < width && j + 1 < height) near.Add(matrix[i + 1, j + 1]);
		for each(Field^ f in near)
		{
			if (!f->isOpened())
				openField(f);
		}

	}
};
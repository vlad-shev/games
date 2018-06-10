#pragma once
#include "Field.h"
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
ref class Table
{
private:
	Form^ form;
	bool player;
	int pl1;
	int pl2;
	const int width = 6;
	const int height = 6;
	array<Field^, 2>^ table;
	void generate()
	{
		table = gcnew array<Field^, 2>(width, height);
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				table[i, j] = gcnew Field();
				table[i, j]->setDefaultStyle(i, j);
				form->Controls->Add(getFieldFromTable(i, j)->getPicture());
			}

	}
public:
	Table(Form^ f)
	{
		form = f;
		player = true;
		pl1 = 0;
		pl2 = 0;
		generate();
	}
	void Clear()
	{
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				form->Controls->Remove(getFieldFromTable(i, j)->getPicture());
	}
	void RecolorUpLeft(int x, int y)
	{
		List<Field^>^ Near = gcnew List<Field^>;
		for (int i = x, j = y; i >= 0 && j >= 0; i--, j--)
		{
			if (i == x && y == j) continue;
			Field^ n = getFieldFromTable(i, j);
			if (n->isMarked() && n->getColor() != player)
				Near->Add(getFieldFromTable(i, j));
			else if (n->isMarked() && n->getColor() == player)
			{
				Recolor(Near);
				break;
			}
			else
				break;
		}
	}
	void RecolorUp(int x, int y)
	{
		List<Field^>^ Near = gcnew List<Field^>;
		for (int j = y, i = x; j >= 0; j--)
		{
			if (i == x && y == j) continue;
			Field^ n = getFieldFromTable(i, j);
			if (n->isMarked() && n->getColor() != player)
				Near->Add(getFieldFromTable(i, j));
			else if (n->isMarked() && n->getColor() == player)
			{
				Recolor(Near);
				break;
			}
			else
				break;
		}
	}
	void RecolorUpRight(int x, int y)
	{
		List<Field^>^ Near = gcnew List<Field^>;
		for (int i = x, j = y; i < width && j >= 0; i++, j--)
		{
			if (i == x && y == j) continue;
			Field^ n = getFieldFromTable(i, j);
			if (n->isMarked() && n->getColor() != player)
				Near->Add(getFieldFromTable(i, j));
			else if (n->isMarked() && n->getColor() == player)
			{
				Recolor(Near);
				break;
			}
			else
				break;
		}
	}
	void RecolorLeft(int x, int y)
	{
		List<Field^>^ Near = gcnew List<Field^>;
		for (int i = x, j = y; i >= 0; i--)
		{
			if (i == x && y == j) continue;
			Field^ n = getFieldFromTable(i, j);
			if (n->isMarked() && n->getColor() != player)
				Near->Add(getFieldFromTable(i, j));
			else if (n->isMarked() && n->getColor() == player)
			{
				Recolor(Near);
				break;
			}
			else
				break;
		}
	}
	void RecolorRight(int x, int y)
	{
		List<Field^>^ Near = gcnew List<Field^>;
		for (int i = x, j = y; i < width; i++)
		{
			if (i == x && y == j) continue;
			Field^ n = getFieldFromTable(i, j);
			if (n->isMarked() && n->getColor() != player)
				Near->Add(getFieldFromTable(i, j));
			else if (n->isMarked() && n->getColor() == player)
			{
				Recolor(Near);
				break;
			}
			else
				break;
		}
	}
	void RecolorDownLeft(int x, int y)
	{
		List<Field^>^ Near = gcnew List<Field^>;
		for (int i = x, j = y; i >= 0 && j < height; i--, j++)
		{
			if (i == x && y == j) continue;
			Field^ n = getFieldFromTable(i, j);
			if (n->isMarked() && n->getColor() != player)
				Near->Add(getFieldFromTable(i, j));
			else if (n->isMarked() && n->getColor() == player)
			{
				Recolor(Near);
				break;
			}
			else
				break;
		}
	}
	void RecolorDown(int x, int y)
	{
		List<Field^>^ Near = gcnew List<Field^>;
		for (int i = x, j = y; j < height; j++)
		{
			if (i == x && y == j) continue;
			Field^ n = getFieldFromTable(i, j);
			if (n->isMarked() && n->getColor() != player)
				Near->Add(getFieldFromTable(i, j));
			else if (n->isMarked() && n->getColor() == player)
			{
				Recolor(Near);
				break;
			}
			else
				break;
		}
	}
	void RecolorDownRight(int x, int y)
	{
		List<Field^>^ Near = gcnew List<Field^>;
		for (int i = x, j = y; i < width && j < height; i++, j++)
		{
			if (i == x && y == j) continue;
			Field^ n = getFieldFromTable(i, j);
			if (n->isMarked() && n->getColor() != player)
				Near->Add(getFieldFromTable(i, j));
			else if (n->isMarked() && n->getColor() == player)
			{
				Recolor(Near);
				break;
			}
			else
				break;
		}
	}
	void RecolorAllSides(Field^ f)
	{
		int x = f->getX() / 35;
		int y = f->getY() / 35;
		RecolorUpLeft(x, y);
		RecolorUp(x, y);
		RecolorUpRight(x, y);
		RecolorLeft(x, y);
		RecolorRight(x, y);
		RecolorDownLeft(x, y);
		RecolorDown(x, y);
		RecolorDownRight(x, y);
	}
	Field^ getFieldFromTable(System::Object^ obj)
	{
		for (int i = 0; i < width; i++) 
			for (int j = 0; j < height; j++)
				if (obj->Equals(table[i, j]->getPicture()))
					return table[i, j];
	}
	Field^ getFieldFromTable(int i, int j)
	{
		return table[i, j];
	}
	void setMark(Field^ f)
	{
		if (f->isMarked()) return;
		f->setMarked(player);
		updateCount();
		RecolorAllSides(f);
		player = !player;
	}
	void Recolor(List<Field^>^ lst)
	{
		for each(Field^ f in lst)
		{
			f->Recolor();
			updateCountRecolor();
		}
	}
	int getPl1() 
	{
		return pl1;
	}
	int getPl2()
	{
		return pl2;
	}
	void updateCount() 
	{
		if (player)
			pl1++;
		else
			pl2++;
	}
	void updateCountRecolor()
	{
		if (player)
		{
			pl1++;
			pl2--;
		}
		else
		{
			pl1--;
			pl2++;
		}
	}

};

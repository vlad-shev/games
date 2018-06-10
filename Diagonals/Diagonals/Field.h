#pragma once
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
ref class Field
{
private:
	bool mark;
	bool color;
	PictureBox^ pictureBox;
public:
	Field()
	{
		mark = false;
		pictureBox = gcnew PictureBox();
	}
	PictureBox^ getPicture()
	{
		return pictureBox;
	}
	void setDefaultStyle(int i, int j)
	{
		pictureBox->Location = Point(35 * i, 35 * j);
		pictureBox->BorderStyle = BorderStyle::FixedSingle;
		pictureBox->Size = System::Drawing::Size(35, 35);
		pictureBox->SizeMode = PictureBoxSizeMode::Zoom;
		pictureBox->BackColor = Color::White;
	}
	void Recolor()
	{
		if (!mark) return;
		color = !color;
		if (color)
			pictureBox->Image = Image::FromFile("icons/white.png");
		else
			pictureBox->Image = Image::FromFile("icons/black.png");
	}
	void setMarked(bool pl)
	{
		mark = true;
		color = pl;
		if (pl)
			pictureBox->Image = Image::FromFile("icons/white.png");
		else
			pictureBox->Image = Image::FromFile("icons/black.png");
	}
	bool isMarked()
	{
		return mark;
	}
	bool getColor()
	{
		return color;
	}
	int getX()
	{
		return (int)pictureBox->Location.X;
	}
	int getY()
	{
		return (int)pictureBox->Location.Y;
	}
};
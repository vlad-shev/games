#pragma once
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
ref class Field
{
private:
	bool ship;
	bool hitted;
	bool shipAvailable;
	PictureBox^ pictureBox;
public:
	Field()
	{
		ship = false;
		hitted = false;
		shipAvailable = true;
		pictureBox = gcnew PictureBox();
	}
	PictureBox^ getPicture()
	{
		return pictureBox;
	}
	void setDefaultStyle(int i , int j, int indent)
	{
		pictureBox->Location = Point(23 * i + indent, 23 * j);
		pictureBox->BorderStyle = BorderStyle::FixedSingle;
		pictureBox->Size = System::Drawing::Size(23, 23);
		pictureBox->SizeMode = PictureBoxSizeMode::Zoom;
		pictureBox->Image = Image::FromFile("icons/background.png");
	}
	void setShip()
	{
		ship = true;
		shipAvailable = false;
	}
	void setShipUnavailable()
	{
		shipAvailable = false;
	}
	void setHitted()
	{
		hitted = true;
		if(ship)
			pictureBox->Image = Image::FromFile("icons/hitted.png");
		else
			pictureBox->Image = Image::FromFile("icons/miss.png");
	}
	bool isShipAvailable()
	{
		return shipAvailable;
	}
	bool isHitted()
	{
		return hitted;
	}
	bool isShip()
	{
		return ship;
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
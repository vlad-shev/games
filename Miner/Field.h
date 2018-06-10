#pragma once
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
ref class Field
{
private:
	bool bomb;
	bool flag;
	bool isOpen;
	int nearbyBombs;
	Point location;
	PictureBox pBox;
public:
	Field()
	{
		bomb = false;
		flag = false;
		nearbyBombs = 0;
	}
	PictureBox^ getPB()
	{
		return %pBox;
	}
	void setLocation(int i, int j)
	{
		location = Point(i, j);
		pBox.Location = location;
	}
	void setBomb()
	{
		bomb = true;
	}
	void setNearbyBombCount(int count)
	{
		nearbyBombs = count;
	}
	bool isOpened()
	{
		return isOpen;
	}
	bool getBomb()
	{
		return bomb;
	}
	bool getFlag()
	{
		return flag;
	}
	int getX()
	{
		return location.X;
	}
	int getY()
	{
		return location.Y;
	}
	int getNearbyBombCount()
	{
		return nearbyBombs;
	}
	Point getLocation()
	{
		return location;
	}
	bool isFlaged() 
	{
		return flag;
	}
	void checkFlag()
	{
		if (isOpen) return;
		flag = !flag;
		if (flag)
			pBox.Image = Image::FromFile("icons/flaged.png");
		else
			pBox.Image = Image::FromFile("icons/closed.png");

	}
	void open()
	{
		if (isOpen || flag) return;
		else
		{
			isOpen = true;
			if (bomb)
				pBox.Image = Image::FromFile("icons/bomb.png");
			else
			{
				if (nearbyBombs)
					pBox.Image = Image::FromFile("icons/num" +
						Convert::ToString(nearbyBombs) + ".png");
				else
					pBox.Image = Image::FromFile("icons/opened.png");
			}

		}
	}
	void openAny()
	{
		if (isOpen) return;
		else
		{
			isOpen = true;
			if (bomb)
				pBox.Image = Image::FromFile("icons/bomb.png");
			else
			{
				if (nearbyBombs)
					pBox.Image = Image::FromFile("icons/num" +
						Convert::ToString(nearbyBombs) + ".png");
				else
					pBox.Image = Image::FromFile("icons/opened.png");
			}

		}
	}
	void showBomb()
	{
		isOpen = true;
		if (flag) return;
		pBox.Image = Image::FromFile("icons/bombed.png");
	}
};

#pragma once
#include "Field.h" 
using namespace System::Collections::Generic;
ref class Ship
{
private:
	bool isDestroyed;
	List<List<Field^>^> nearby;
	List<Field^> shipParts;
public:
	Ship() 
	{
		isDestroyed = false;
	}
	void Add(Field^ f)
	{
		shipParts.Add(f);
	}
	void AddNearby(List<Field^>^ l)
	{
		nearby.Add(l);
	}
	void setUnavailable() 
	{
		for each(List<Field^>^ l in nearby)
			for each(Field^ f in l)
				f->setShipUnavailable();
	}
	void showUnavailable()
	{
		for each(List<Field^>^ l in nearby)
			for each(Field^ f in l)
			{
				if(!f->isShip())
					f->getPicture()->Image = Image::FromFile("icons/miss.png");
			}
	}
	void CheckIsDestroyed()
	{
		bool flag = true;
		for each(Field^ f in shipParts) 	//���� ����� ��� �� ����������, �� � ���� ������� �� �����.

			if (!f->isHitted()) flag = false;
		if (flag)
		{
			isDestroyed = true;
			for each(Field^ f in shipParts)//���� �����, �� ������ ��������
				f->getPicture()->Image = Image::FromFile("icons/killed.png");
			showUnavailable();
				
		}
	}
	void showShip()//������� ���������
	{
		for each(Field^ f in shipParts)
			f->getPicture()->Image = Image::FromFile("icons/ship.png");
	}
	bool getIsDestroyed()
	{
		return isDestroyed;
	}
	bool isPart(Field^ f)//��� �� ���� ������ �������
	{
		for each(Field^ part in shipParts)
			if (part->Equals(f)) return true;
		return false;
	}
	int getLen() //����� �������=����� ������ ��� ������
	{
		return shipParts.Count;
	}
};


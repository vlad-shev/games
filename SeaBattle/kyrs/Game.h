#pragma once
#include "Table.h"
#include "Ship.h"
ref class Game
{
private:
	Form^ form;
	Table^ playerTable;
	Table^ computerTable;
	List<Ship^> computerShips;
	List<Ship^> playerShips;
	bool playerAllShipsSet;
	bool playerReady;

	void addControls()
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				form->Controls->Add(playerTable->getFieldFromTable(i, j)->getPicture());
				form->Controls->Add(computerTable->getFieldFromTable(i, j)->getPicture());
			}
	}
public:
	Game(Form^ f)
	{
		form = f;
		playerTable = gcnew Table(260);
		computerTable = gcnew Table(0);
		playerReady = false;
		playerAllShipsSet = false;
		addControls();
		setAllCompShips();
	}
	Table^ getPlayerTable() 
	{
		return playerTable;
	}
	Table^ getComputerTable() 
	{
		return computerTable;
	}
	void Clear()
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				form->Controls->Remove(playerTable->getFieldFromTable(i, j)->getPicture());
				form->Controls->Remove(computerTable->getFieldFromTable(i, j)->getPicture());
			}
	}
	void setHorizontalShip(int len) 
	{
		bool flag = true;
		Random^ rand = gcnew Random;
		while (true)
		{
			flag = true;
			int i = rand->Next(0, 10 - len);
			int j = rand->Next(0, 10);
			for (int k = i; k < i + len; k++)
			{
				Field^ f = computerTable->getFieldFromTable(k, j);//получить поле из таблицы с такимим индексами
				if (!f->isShipAvailable())
					flag = false;
			}
			if (!flag) //тогда ищем новые координаты и устанавливаем корабл
			{
				flag = true;
				continue;
			}
			Ship^ ship = gcnew Ship();// создаем пустой корабл
			for (int k = i; k < i + len; k++)
			{
				Field^ f = computerTable->getFieldFromTable(k, j);
				f->setShip();
				ship->Add(f);
			}
			computerShips.Add(ship);//надо добавить корабл!
			for (int k = i; k < i + len; k++)
				ship->AddNearby(computerTable->getUnavailable(k, j));
			ship->setUnavailable();
			break;
		}
	}
	void setVerticalShip(int len)
	{
		bool flag = true;
		Random^ rand = gcnew Random;
		while (true)
		{
			flag = true;
			int i = rand->Next(0, 10);
			int j = rand->Next(0, 10 - len);
			for (int k = j; k < j + len; k++)
			{
				Field^ f = computerTable->getFieldFromTable(i, k);
				if (!f->isShipAvailable())
					flag = false;
			}
			if (!flag)
			{
				flag = true;
				continue;
			}
			Ship^ ship = gcnew Ship();
			for (int k = j; k < j + len; k++)
			{
				Field^ f = computerTable->getFieldFromTable(i,k);
				f->setShip();
				ship->Add(f);
			}
			computerShips.Add(ship);
			for (int k = j; k < j + len; k++)
				ship->AddNearby(computerTable->getUnavailable(i, k));
			ship->setUnavailable();
			break;
		}
	}
	void setComputerShip(int len) // рандомно выбирает 1 или 0, если 1(горизонтал), а если 0 наоборот
	{
		Random^ rand = gcnew Random();
		bool flag = rand->Next(0, 2);
		if (flag)
			setHorizontalShip(len);
		else
			setVerticalShip(len);
	}
	void setAllCompShips()
	{
		setComputerShip(4); //сразу устанавл 4-палубный корабл
		for (int i = 0; i < 2; i++)
		{
			setComputerShip(3);//переходим два раза по циклу , чтоб поставить 2 корабл 3-палубных
			setComputerShip(2);//тоже самое
		}
		for (int i = 0; i < 4; i++)
			setComputerShip(1);
	}
	void setHorizontalShip(int len, int i, int j)
	{
		bool flag = false;
		if (i + len > 10) return;
		for (int k = i; k < i + len; k++)
		{
			Field^ f = playerTable->getFieldFromTable(k, j);
			if (!f->isShipAvailable())flag = true;
		}
		if (flag) return;
		Ship^ ship = gcnew Ship();
		for (int k = i; k < i + len; k++)
		{
			Field^ f = playerTable->getFieldFromTable(k, j);
			f->setShip();
			ship->Add(f);
			ship->showShip();
		}
		playerShips.Add(ship);
		for (int k = i; k < i + len; k++)
			ship->AddNearby(playerTable->getUnavailable(k, j));
		ship->setUnavailable();
	}
	void setVerticalShip(int len, int i, int j)
	{
		bool flag = false;
		if (j + len > 10) return;
		for (int k = j; k < j + len; k++)
		{
			Field^ f = playerTable->getFieldFromTable(i, k);
			if (!f->isShipAvailable()) flag = true;
		}
		if (flag) return;
		Ship^ ship = gcnew Ship();
		for (int k = j; k < j + len; k++)
		{
			Field^ f = playerTable->getFieldFromTable(i, k);
			f->setShip();
			ship->Add(f);
			ship->showShip();
		}
		playerShips.Add(ship);
		for (int k = j; k < j + len; k++)
			ship->AddNearby(playerTable->getUnavailable(i, k));
		ship->setUnavailable();
	}
	void LeftClickOnPlayerTable(Object^ obj)
	{
		if (playerShips.Count == 9)
		{
			playerAllShipsSet = true;
			playerReady = true;
			return;
		}
		Field^ f = playerTable->getFieldFromTable(obj);//координаты (i,j)--столбцы и строки....находим положение кораблей
		int i = (f->getX() - playerTable->getIndent()) / 23;
		int j = f->getY()/ 23;
		if (playerShips.Count < 1)
			setVerticalShip(4, i, j);
		else if (playerShips.Count >= 1 && playerShips.Count < 3 )
			setVerticalShip(3, i, j);
		else if (playerShips.Count >= 3 && playerShips.Count < 5)
			setVerticalShip(2, i, j);
		else
			setVerticalShip(1, i, j);
		if (playerShips.Count == 9)
		{
			playerAllShipsSet = true;
			playerReady = true;
			return;
		}
	}
	void RightClickOnPlayerTable(Object^ obj)
	{
		if (playerShips.Count == 9)
		{
			playerAllShipsSet = true;
			playerReady = true;
			return;
		}
		Field^ f = playerTable->getFieldFromTable(obj);
		int i = (f->getX() - playerTable->getIndent()) / 20;
		int j = f->getY() / 20;
		if (playerShips.Count < 1)
			setHorizontalShip(4, i, j);
		else if (playerShips.Count >= 1 && playerShips.Count < 3)
			setHorizontalShip(3, i, j);
		else if (playerShips.Count >= 3 && playerShips.Count < 5)
			setHorizontalShip(2, i, j);
		else
			setHorizontalShip(1, i, j);
		if (playerShips.Count == 9)
		{
			playerAllShipsSet = true;
			playerReady = true;
			return;
		}
	}
	void PlayerShot(Object^ obj)
	{
		if (!playerReady || !playerAllShipsSet) return;
		Field^ f = computerTable->getFieldFromTable(obj);
		if (f->isHitted()) return;
		f->setHitted();
		if (f->isShip())
		{
			for each(Ship^ s in computerShips)
				if (s->isPart(f))
				{
					s->CheckIsDestroyed();
					break;
				}
		}
		else
			playerReady = false;
		CheckPlayerWin();
	}
	void ComputerShot() 
	{
		if (playerReady || !playerAllShipsSet) return;
		Field^ f;
		while (true)
		{
			Random^ rand = gcnew Random();
			int i = rand->Next(0, 10);
			int j = rand->Next(0, 10);
			f = playerTable->getFieldFromTable(i, j);
			if (!f->isHitted()) break;
		}
		f->setHitted();
		if (f->isShip())
		{
			for each(Ship^ s in playerShips)
				if (s->isPart(f))
				{
					s->CheckIsDestroyed();
					break;
				}
			ComputerShot();
		}
		else
			playerReady = true;
		CheckComputerWin();

	}
	void CheckPlayerWin() 
	{
		bool flag = true;
		for each(Ship^ s in computerShips)
			if (!s->getIsDestroyed())
				flag = false;
		if (flag)
			computerTable->openUnhitted();
	}
	void CheckComputerWin()
	{
		bool flag = true;
		for each(Ship^ s in playerShips)
			if (!s->getIsDestroyed())
				flag = false;
		if (flag)
			for each(Ship^ s in computerShips)
			{ 
				s->showShip();
				playerReady = false;
			}
	}
};
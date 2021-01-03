#include "stdafx.h"
#include "Inventory.h"


//-------------------------------------------Konstruktor-------------------------------------/
Inventory::Inventory(unsigned capacity)
{
	this->capacity = capacity;
	this->initalize();
}
//-------------------------------------------Destruktor-------------------------------------/
Inventory::~Inventory()
{
	this->clear();
}

//-------------------------------------------Funkcje-------------------------------------/
void Inventory::initalize()
{
	this->capacity = 10;
	this->numberOfItems = 0;
	this->itemArray = new Item * [this->capacity];
	this->nullify();
}

void Inventory::clear()
{
	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		delete this->itemArray[i];
	}
	delete[] this->itemArray;//usuwa glowny *
}

void Inventory::expand()
{
}

void Inventory::nullify(const unsigned from)
{
	for (size_t i = from; i < capacity; i++)
	{
		this->itemArray[i] = nullptr;
	}
}
unsigned const& Inventory::size()
{
	return this->numberOfItems;
}

unsigned const& Inventory::maxSize()
{
	return this->capacity;
}

void Inventory::clear_1()
{
	for (size_t i = 0; i < this->numberOfItems; i++)
	{
		delete this->itemArray[i];
	}
	this->numberOfItems = 0;
	this->nullify();
}

const bool Inventory::empty() const
{
	return this->numberOfItems==0;
}

const bool Inventory::addItem(Item* item)
{
	if (this->numberOfItems<this->capacity)//sprawdzam czy moge dodac
	{
		this->itemArray[this->numberOfItems++]=item->clone();
		return true;
	}
	return false;
}

const bool Inventory::remove(unsigned index) 
{
	if (this->numberOfItems>0)
	{
		if (index < 0 || index >= this->capacity)
		{
			return false;
		}
		delete this->itemArray[index];
		this->itemArray[index] = nullptr;
		--this->numberOfItems;
		return true;

	}
}


const bool Inventory::saveToFile(string file_name)
{
	return false;
}

const bool Inventory::loadFromFile(string file_name)
{
	return false;
}

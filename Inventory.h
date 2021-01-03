#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"

class Inventory
{
private:
	Item** itemArray;
	unsigned capacity;
	unsigned numberOfItems;

	void initalize();//inicjalizuje zmienne w private
	void clear();//usuwa zawartosc
	void expand();
	void nullify(const unsigned from=0);
public:
	//konstruktor
	Inventory(unsigned capacity);
	//destruktor
	virtual~Inventory();

	//funkcje
	unsigned const& size();
	unsigned const& maxSize();
	void clear_1();
	const bool empty()const;
	const bool addItem(Item* item) ;
	const bool remove(unsigned index) ;
	const bool saveToFile(string file_name);
	const bool loadFromFile(string file_name);
};

#endif // !INVENTORY_H


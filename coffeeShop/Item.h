#pragma once
#include<iostream>
#include<fstream>



// class item

class Item
{
protected:

	int remainStock;

	float item_cost;

	std::string name;

public:

	int item_id;

	Item();

	void display_item_list();

	void item_list_forCustom();

	void display_item();              // view a specific item

	int is_exist(int);                // check if the item exist on the list

	void add_item();

	void edit_amount(int);            // edit recieving item amount

	void edit_item(int);

	void delete_item(int);

};


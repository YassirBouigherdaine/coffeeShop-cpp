#pragma once
#include"Home.h"
#include"Item.h"



// class coffshop

class coffShop : public Item
{
	struct Order
	{
		Item item;

		int tableNum = 0;

		int Day, Mon, Year;

		int Hour, Min;

		int NumOfItems = 0;

		Order* next = nullptr;
	};

	Order* front;
	Order* rear;

	int length;

public:

	coffShop();

	~coffShop();                  

	void enqueue_order();         // add order to the list 

	void dequeue_order();          // deliver order 

	void print_queues();          // display list of orders

	bool is_empty();              // check if the list is empty

	void peek();                 // view the first order

	void display_report();       // coffeeshop report

	void clear_list();           // clear list of orders

};


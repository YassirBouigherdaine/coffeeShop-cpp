#include "coffShop.h"






coffShop::coffShop(): front(nullptr), rear(nullptr), length(0)
{}

coffShop::~coffShop()
{
    // destroy list

	clear_list();
}

// append node at the end

void coffShop::enqueue_order()
{
	
	Order* newOrder = new Order;
	newOrder->next = nullptr;

	system("cls");

	std::cout << "\n\t\t**************************************************\n";
	std::cout << "\t\t*                   MAKE ORDER                   *\n";
	std::cout << "\t\t**************************************************\n\n";

	std::cout << "\n\n\t\t Table number : ";
	std::cin >> newOrder->tableNum;
	std::cout << "\n\n\t\t Date (day/month/year): ";
	std::cin >> newOrder->Date;
	std::cout << "\n\n\t\t Item id : ";
	std::cin >> newOrder->item.item_id;
	std::cout << "\n\n\t\t number of items : ";
	std::cin >> newOrder->NumOfItems;
	
	if (front == nullptr)
	{
		front = rear = newOrder;
	}
	else
	{
		rear->next = newOrder;
		rear = newOrder;
	}

	length++;
}



void coffShop::dequeue_order()
{
	if (front != nullptr)
	{
		// saving operation

		std::ofstream Fout("ordersServed.txt", std::ios::app | std::ios::binary);

		Fout << front->tableNum <<"\t"<< front->Date << "\t" << front->item.item_id << "\t" << front->NumOfItems<< "\t" << std::endl;

		Fout.close();

		// the bill

		std::ifstream fin;
		fin.open("Inventory.txt", std::ios::in | std::ios::binary);

		while (!fin.eof())
		{
			fin.read((char*)this, sizeof(Item));

			if (item_id == front->item.item_id)
			{
				double price = item_cost + (item_cost * 0.3);

				std::cout << "\n ***************\n";
				std::cout << " coffeeshop name ";
				std::cout << "\n ***************\n";
				std::cout << "\n\n-----------------------------------Bill no: ------------------------------------\n";
				std::cout << "\n--------------------------------------------------------------------------------\n";
				std::cout << "\n\t\t Item name     \t\t\tPrice \t\tAmount  \t\t              \n";
				std::cout << "\n--------------------------------------------------------------------------------\n";
				std::cout << "\t\t " << name << "\t\t\t" << price << " \t\t" << front->NumOfItems << " \t\t " << "\n\n";
				std::cout << "\n--------------------------------------------------------------------------------\n";
				std::cout << "                                               Toltal:          " << price * front->NumOfItems << "      \n";
				std::cout << "--------------------------------------------------------------------------------\n\n";
				std::cout << "\n\t\t\t Thank you for visiting us \n";
				std::cin.get();
				std::cout << "\n\n\t\t\t Press [ENTER] to continue";
				std::cin.get();
			}
		}

		fin.close();

		// deleting order

		Order* orderToDelete = front;
		front = front->next;
		delete orderToDelete;

		// if there is one order the rear must be updated

		if (front == nullptr)
		{
			rear = nullptr;
		}
	}

	length--;
}

	

void coffShop::print_queues()
{
	// display list of orders

	Order* currOrder = front;

	std::cout << "\n\t\t\tLIST OF ORDERS\t\t\t"<<length<<" order\n";
	std::cout << "\n----------------------------------------------------------------\n";

	while (currOrder != nullptr)
	{
		std::cout << "\t\t\tDate : " << currOrder->Date <<"\n\n";
		std::cout <<" Table number : "<< currOrder->tableNum << "\t";
		std::cout << "Item id : "<< currOrder->item.item_id<< "\t";
		std::cout << "number of Items: " << currOrder->NumOfItems;
		std::cout << "\n----------------------------------------------------------------\n";
		
		currOrder = currOrder->next;
	}

	std::cin.get();
	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}

bool coffShop::is_empty()
{
	if (front == nullptr)
	{
		return true;
	}

	return false;
}

// check the first order in the list

void coffShop::peek()
{
	if (front != nullptr)
	{
		std::cout << "\n------------------------------------------------------------------\n";
		std::cout << "\t\t\t\tORDER\n";
		std::cout << "\n------------------------------------------------------------------\n";
		std::cout << "\t\t\t Date : " << front->Date << "\n\n";
		std::cout << "\tTable number : " << front->tableNum << "\t";
		std::cout << "Item id : " << front->item.item_id << "\t";
		std::cout << "number of Items: " << front->NumOfItems;
		std::cout << "\n------------------------------------------------------------------\n";
	}
	else
	{
		std::cout << "\n\t\t\t List is empty\n";
	}

	std::cin.get();
	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}

void coffShop::display_report()
{
	int op;

	do
	{
		system("cls");

		std::cout << "\n\t\t**************************************************\n";
		std::cout << "\t\t*             INVENTORY REPORT                    *\n";
		std::cout << "\t\t**************************************************\n\n";

		std::cout << "\t\t\t\t [1] IN\n";
		std::cout << "\t\t\t\t [2] OUT\n";
		std::cout << "\t\t\t\t [3] Exit\n";

		std::cout << "\n\t\t\t>Enter your choice: ";
		std::cin >> op;

		if (op == 1)
		{
			// display list of received amount of items

			std::ifstream fin;
			fin.open("amountAdded.txt", std::ios::in | std::ios::binary);

			int id, amountAdded;
			std::string date;

			if (fin.is_open())
			{
				system("cls");

				std::cout << "\n----------------------------------RECEIVED AMOUNT------------------------------------------\n\n";
				std::cout << "-------------------------------------------------------------------------------------------\n";
				std::cout << "    \t\tDATE\t\tID\tRECEIVED AMOUNT\n";
				std::cout << "-------------------------------------------------------------------------------------------\n";

				fin >> date >> id >> amountAdded;

				while (!fin.eof())
				{
					std::cout <<"  \t\t"<< date << "\t" << id << "\t" << amountAdded << "\t" << std::endl;
					std::cout << "-------------------------------------------------------------------------------------------\n";
					fin >> date >> id >> amountAdded;
				}
			}
			else
			{
				std::cout << "\n\t\tError occurred in opening the file\n";
			}

			fin.close();
			std::cin.get();
			std::cout << "\n\n\t\t\t Press [ENTER] to continue";
			std::cin.get();
		}


		else if (op == 2)
		{
			// display list of orders served $$
			
			std::ifstream fin("ordersServed.txt", std::ios::in | std::ios::binary);
			
			Order* currOrder = front;

			if (fin.is_open())
			{
				system("cls");

				std::cout << "\n----------------------------------ORDERS SERVED--------------------------------------------\n";
				std::cout << "-------------------------------------------------------------------------------------------\n";
				std::cout << "\t\tTABLE  \t DATE\t\tID \t  ITEMS \n";
				std::cout << "-------------------------------------------------------------------------------------------\n";
				
				fin >> currOrder->tableNum >> currOrder->Date >> currOrder->item.item_id >> currOrder->NumOfItems;

				while (!fin.eof())
				{
					std::cout << "\t\t"<<currOrder->tableNum << "\t" << currOrder->Date << "\t" << currOrder->item.item_id << "\t" << currOrder->NumOfItems << "\t" << std::endl;
					std::cout << "-------------------------------------------------------------------------------------------\n";
					fin >> currOrder->tableNum >> currOrder->Date >> currOrder->item.item_id >> currOrder->NumOfItems;
				}
			}
			else
			{
				std::cout << "\n\t\tError occurred in opening the file\n";
			}

			fin.close();
			std::cin.get();
			std::cout << "\n\n\t\t\t Press [ENTER] to continue";
			std::cin.get();
		}
	
	} while (op != 3);

	
	
}


void coffShop::clear_list()
{
	Order* orderToDelete = front;
	Order* nextOrder = nullptr;

	if (front != nullptr)
	{
		while (orderToDelete != nullptr)
		{
			nextOrder = orderToDelete->next;

			delete orderToDelete;

			orderToDelete = nextOrder;
		}

		front = nullptr;
		rear = nullptr;

		std::cout << "The list is empty\n";
	}
}
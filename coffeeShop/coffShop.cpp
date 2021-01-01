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

	int id, exist = 0;

	system("cls");

	std::cout << "\n\t\t**************************************************\n";
	std::cout << "\t\t*                   MAKE ORDER                   *\n";
	std::cout << "\t\t**************************************************\n\n";

	std::cout << "\n\n\t\t Item id : ";
	std::cin >> id;

	exist = is_exist(id);

	if (exist)
	{
		newOrder->item.item_id = id;

		std::cout << "\n\n\t\t Table number : ";
		std::cin >> newOrder->tableNum;
		std::cout << "\n\n\t\t Date (day/month/year): ";
		std::cin >> newOrder->Date;
		std::cout << "\n\n\t\t number of items : ";
		std::cin >> newOrder->NumOfItems;

		if (is_empty())
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

	else
	{
		std::cin.get();
		std::cout << "\n\t\t\t Item not found\n";
		std::cin.get();
	}
	
}



void coffShop::dequeue_order()
{
	if (!is_empty())
	{
		// saving operation

		std::ofstream Fout("ordersServed.txt", std::ios::app | std::ios::binary);

		Fout << front->tableNum <<"\t"<< front->Date << "\t" << front->item.item_id << "\t" << front->NumOfItems<< "\t" << std::endl;

		Fout.close();

		// the bill

		std::ifstream fin;
		fin.open("stock.txt", std::ios::in | std::ios::binary);

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
				break;
			}
		}

		fin.close();

		// deleting order

		Order* orderToDelete = front;
		front = front->next;
		delete orderToDelete;

		// if there is one order the rear must be updated

		if (is_empty())
		{
			rear = nullptr;
		}

		length--;
	}
	else
	{
		std::cout << "\n\t\t\t List is empty\n";
	}

	std::cin.get();
	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
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
	if (!is_empty())
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
		}

		else if (op == 2)
		{
			// display list of orders served $$
			
			std::ifstream fin("ordersServed.txt", std::ios::in | std::ios::binary);

			int tableN, id, n_of_items;
			std::string date;

			if (fin.is_open())
			{
				system("cls");

				std::cout << "\n----------------------------------ORDERS SERVED--------------------------------------------\n";
				std::cout << "-------------------------------------------------------------------------------------------\n";
				std::cout << "\t\tTABLE-N  \t DATE\t\tID \t  ITEMS \n";
				std::cout << "-------------------------------------------------------------------------------------------\n";
				
				fin >> tableN >> date >> id >> n_of_items;

				while (!fin.eof())
				{
					std::cout << "\t\t" << tableN << "\t\t" << date << "\t" << id << "\t   " << n_of_items << std::endl;
					std::cout << "-------------------------------------------------------------------------------------------\n";
					fin >> tableN >> date >> id >> n_of_items;
				}
			}
			else
			{
				std::cout << "\n\t\tError occurred in opening the file\n";
			}

			fin.close();
		}

		std::cin.get();
		std::cout << "\n\n\t\t\t Press [ENTER] to continue";
		std::cin.get();
	
	} while (op != 3);
}


void coffShop::clear_list()
{
	Order* orderToDelete = front;
	Order* nextOrder = nullptr;

	if (!is_empty())
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
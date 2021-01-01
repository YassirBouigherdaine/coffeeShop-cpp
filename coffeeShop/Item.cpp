#include "Item.h"



Item::Item(): item_id (0), name ("Unknown"), item_cost (0), remainStock (0)
{}


void Item::display_item_list()
{
	system("cls");

	std::cout << "\n----------------------------------ITEM LIST------------------------------------------------\n";
	std::cout << "-------------------------------------------------------------------------------------------\n";
	std::cout << "\tID\tNAME\t\tITEM COST\tREMAIN STOCK\n";
	std::cout << "-------------------------------------------------------------------------------------------\n";

	std::ifstream fin;
	fin.open("stock.txt", std::ios::in | std::ios::binary);
	fin.read((char*)this, sizeof(Item));

	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::cout << "\t" << item_id << "\t" << name << "\t  " << item_cost << "\t\t  " << remainStock << std::endl;
			std::cout << "-------------------------------------------------------------------------------------------\n";

			fin.read((char*)this, sizeof(Item));
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


void Item::item_list_forCustom()
{
	system("cls");

	std::cout << "\n----------------------------------DRINKS LIST----------------------------------------------\n";
	std::cout << "-------------------------------------------------------------------------------------------\n";
	std::cout << "\tID\t NAME\t\tITEM PRICE\n";
	std::cout << "-------------------------------------------------------------------------------------------\n";

	std::ifstream fin;
	fin.open("stock.txt", std::ios::in | std::ios::binary);
	fin.read((char*)this, sizeof(Item));

	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::cout << "\t" << item_id << "\t" << name << "\t  " << item_cost + (item_cost * 0.3) <<"$\n";
			std::cout << "-------------------------------------------------------------------------------------------\n";

			fin.read((char*)this, sizeof(Item));
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


void Item::display_item()
{
	int id, op, exist = 0;

	std::ifstream fin;
	fin.open("stock.txt", std::ios::in | std::ios::binary);

	std::cout << "\n\t\t Enter ID : ";
	std::cin >> id;

	exist = is_exist(id);

	if (exist)
	{
		while (!fin.eof())
		{
			fin.read((char*)this, sizeof(Item));

			if (item_id == id)
			{
				system("cls");

				std::cout << "\n----------------------------------ITEM DETAILS----------------------------------------------------------\n";
				std::cout << "---------------------------------------------------------------------------------------------------------\n";
				std::cout << "\tID \t NAME \t     ITEM COST   REMAIN STOCK\t\n";
				std::cout << "--------------------------------------------------------------------------------------------------------\n";

				std::cout << "\t" << item_id << "\t" << name << "\t  " << item_cost << "\t  " << remainStock << std::endl;

				std::cout << "--------------------------------------------------------------------------------------------------------\n";

				// advertising to avoid exceptions and risks

				if (remainStock <= 10)
				{
					std::cout << "\n\n\t\t\t Contact the supplier\n";
				}

				break;
			}
		}

		fin.close();

		std::cout << "\n\n\t\t*******************************************************\n";
		std::cout << "\t\t**                                                   **\n";
		std::cout << "\t\t*                     ITEM OPTIONS                    *\n";
		std::cout << "\t\t**                                                   **\n";
		std::cout << "\t\t*******************************************************\n\n";

		std::cout << "\t\t\t\t [1] Edit amount\n";
		std::cout << "\t\t\t\t [2] Edit item\n";
		std::cout << "\t\t\t\t [3] Delete item\n";
		std::cout << "\t\t\t\t [4] Exit\n";

		std::cout << "\n\t\t\t>Enter your choice: ";
		std::cin >> op;

		switch (op)
		{
		case 1: edit_amount(id);
			break;

		case 2: edit_item(id);
			break;

		case 3: delete_item(id);
			break;

		case 4: break;
			break;
		}
		
	}
	else
	{
		std::cout << "\n\t\tItem not found\n";
	}

	std::cin.get();
	std::cout << "\n\n\t\t\t Press [ENTER] to continue";
	std::cin.get();
}



int Item::is_exist(int id)
{
	std::ifstream fin;
	fin.open("stock.txt", std::ios::in | std::ios::binary);

	while (!fin.eof())
	{
		fin.read((char*)this, sizeof(Item));

		if (item_id == id)
		{
			return 1;
		}
	}

	fin.close();

	return 0;
}


void Item::add_item()
{
	system("cls");

	std::ofstream fout;
	fout.open("stock.txt", std::ios::app | std::ios::binary);

	int id, exist = 0;

	std::cout << "\n\n\t\tEnter item details :\n";
	std::cout << "\n\t\t Enter ID : ";
	std::cin >> id;

	exist = is_exist(id);

	if (!exist)
	{
		item_id = id;
		std::cout << "\n\t\t Item name: ";
		std::cin >> name;
		std::cout << "\n\t\t Item cost: ";
		std::cin >> item_cost;
		std::cout << "\n\t\t Amount:";
		std::cin >> remainStock;

		fout.write((char*)this, sizeof(Item));

		std::cin.get();
		std::cout << "\n\t\t\t Item has been created successfully\n";
		std::cin.get();
	}

	else
	{
		std::cout << "\n\n\t\t\tItem already exist\n";
		std::cin.get();
	}

	fout.close();
}


void Item::edit_amount(int id)
{
	int amountAdded;                            //received amount
	std::string date;                           //day/mon/year
	
	std::fstream file("stock.txt", std::ios::out | std::ios::in | std::ios::binary);
	std::ofstream newFile("amountAdded.txt", std::ios::app | std::ios::binary);

	std::cout << "\n\n\t\t Enter date: ";
	std::cin >> date;                                   
	std::cout << "\n\n\t\t Enter amount: ";
	std::cin >> amountAdded;
	                                   
	// save operation in new file

	newFile << date << "\t" << id << "\t" << amountAdded << "\t" << std::endl;

	while (file.read((char*)this, sizeof(Item)))
	{
		if (id == item_id)
		{
			remainStock += amountAdded;
			
			unsigned __int64 pos = file.tellg();

			file.seekp(pos - sizeof(Item), std::ios::beg);
			file.write((char*)this, sizeof(Item));
			break;
		}
	}

	file.close();
	newFile.close();

	std::cin.get();
	std::cout << "\n\t\t\t operation has been registered successfully\n";
	system("cls");
}


void Item::edit_item(int id)
{
	std::fstream file;
	file.open("stock.txt", std::ios::in | std::ios::out | std::ios::binary);

	if (file.good())
	{
		while (file.read((char*)this, sizeof(Item)))
		{
			if (id == item_id)
			{
				system("cls");

				std::cout << "\n\n\t\t Enter news details : ";

				std::cout << "\n\n\t\t ID: ";
				std::cin >> item_id;
				std::cout << "\n\t\t Item name: ";
				std::cin >> name;
				std::cout << "\n\t\t Item cost: ";
				std::cin >> item_cost;
				std::cout << "\n\t\t Amount:";
				std::cin >> remainStock;

				int pos = -1 * static_cast<int>(sizeof(Item));
				file.seekp(pos, std::ios::cur);
				file.write((char*)this, sizeof(Item));

				std::cin.get();
				std::cout << "\n\t\t\t Item modified successfully\n";
				break;
			}
		}
	}
	else
	{
		std::cout << "\n\t\tError occurred in opening the file\n";
	}

	file.close();
	system("cls");
}


void Item::delete_item(int id)
{
	std::fstream fin("stock.txt", std::ios::in | std::ios::binary);
	std::fstream newFile("tempFile.txt", std::ios::app | std::ios::binary);

	while (fin.read((char*)this, sizeof(Item)))
	{
		if (item_id != id)
		{
			newFile.write((char*)this, sizeof(Item));
		}
	}

	fin.close();
	newFile.close();
	remove("stock.txt");
	rename("tempFile.txt", "stock.txt");
	
	system("cls");
	std::cout << "\n\t\t\t Item was deleted successfully\n";
	
}



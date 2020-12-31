#include"Home.h"




coffShop coffee;



// Home functions

// the main function

void main_menu()
{
	int op;

	while (true)
	{
		system("cls");

		std::cout << "\t\t*******************************************************\n";
		std::cout << "\t\t*******************************************************\n";
		std::cout << "\t\t**                                                   **\n";
		std::cout << "\t\t*                       WELCOME                       *\n";
		std::cout << "\t\t**                                                   **\n";
		std::cout << "\t\t*******************************************************\n";
		std::cout << "\t\t*******************************************************\n\n\n";
		std::cout << "\t\t\t\t   [1] CUSTOMER\n";
		std::cout << "\t\t\t\t   [2] ADMIN\n\n";
		std::cout << "\n\t\t\t>Enter your choice: ";
		std::cin >> op;

		if (op == 1)
		{
			customer_menu();
		}

		else if (op == 2)
		{
			admin_access();
		}
	}
}


// customer menu

void customer_menu()
{
	int op;

	do
	{
		system("cls");

		std::cout << "\t\t*******************************************************\n";
		std::cout << "\t\t*******************************************************\n";
		std::cout << "\t\t**                                                   **\n";
		std::cout << "\t\t*              COFFEESHOP SYSTEM MANAGEMENT           *\n";
		std::cout << "\t\t*                          HOME                       *\n";
		std::cout << "\t\t**                                                   **\n";
		std::cout << "\t\t*******************************************************\n";
		std::cout << "\t\t*******************************************************\n\n\n";

		std::cout << "\t\t\t\t   [1] view drinks list\n";
		std::cout << "\t\t\t\t   [2] Make order\n";
		std::cout << "\t\t\t\t   [3] Exit\n";

		std::cout << "\n\t\t\t>Enter your choice: ";
		std::cin >> op;

		switch (op)
		{
		case 1: coffee.item_list_forCustom();
			break;

		case 2: coffee.enqueue_order();
			break;
		}

	} while (op != 3);
}


// admin menu

void admin_menu()
{
	int op, id = 0;

	do
	{
		system("cls");

		std::cout << "\t\t*******************************************************\n";
		std::cout << "\t\t*******************************************************\n";
		std::cout << "\t\t**                                                   **\n";
		std::cout << "\t\t*              COFFEESHOP SYSTEM MANAGEMENT           *\n";
		std::cout << "\t\t*                          HOME                       *\n";
		std::cout << "\t\t**                                                   **\n";
		std::cout << "\t\t*******************************************************\n";
		std::cout << "\t\t*******************************************************\n\n\n";

		std::cout << "\t\t\t\t [1] Deliver order \n";
		std::cout << "\t\t\t\t [2] Make order \n";
		std::cout << "\t\t\t\t [3] Display list of orders\n";
		std::cout << "\t\t\t\t [4] View the first order\n";
		std::cout << "\t\t\t\t [5] View drinks list\n";
		std::cout << "\t\t\t\t [6] View item\n";
		std::cout << "\t\t\t\t [7] Add item\n";
		std::cout << "\t\t\t\t [8] Inventory report\n";
		std::cout << "\t\t\t\t [9] Exit\n";

		std::cout << "\n\t\t\t>Enter your choice: ";
		std::cin >> op;

		system("cls");
		switch (op)
		{
		case 1: coffee.dequeue_order();
			break;

		case 2: coffee.enqueue_order();
			break;

		case 3: coffee.print_queues();
			break;

		case 4: coffee.peek();
			break;

		case 5: coffee.display_item_list();
			break;

		case 6: coffee.display_item();
			break;

		case 7: coffee.add_item();
			break;

		case 8: coffee.display_report();
			break;
		}

	} while (op != 9);
}


// admin access function (login or register)

int checkAccess(std::string userName, std::string passWord)
{
	std::string user_name;
	std::string pass_word;

	std::ifstream fin;
	fin.open("admin.txt", std::ios::in | std::ios::binary);

	fin >> user_name >> pass_word;

	if (userName == user_name && passWord == pass_word)
	{
		return 1;
	}

	fin.close();

	return 0;
}



void creatAcount()
{
	system("cls");

	std::string code, user_name, pass_word;

	std::ofstream fout;
	fout.open("admin.txt", std::ios::app | std::ios::binary);

	// creating account will be private 

	do
	{
		std::cout << "\n\n\t\t\t>Enter code : ";
		std::cin >> code;

	} while (code != "755admin033");                // this code only for the manager

	system("cls");

	std::cout << "\t\t**************************************************\n";
	std::cout << "\t\t*                   CREAT ACOUNT                 *\n";
	std::cout << "\t\t**************************************************\n";

	std::cout << "\n\n\t\t username : ";
	std::cin >> user_name;
	std::cout << "\n\t\t password : ";
	std::cin >> pass_word;

	fout << user_name << std::endl << pass_word;
	fout.close();

	login();
}



// login staff

void login()
{
	int access = 0;
	std::string userName, passWord;

	while (!access)
	{
		system("cls");

		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t***********************      *********************\n";
		std::cout << "\t\t*                                                *\n";
		std::cout << "\t\t*               COFFEESHOP MANAGEMENT            *\n";
		std::cout << "\t\t*                     WELCOME                    *\n";
		std::cout << "\t\t*                                                *\n";
		std::cout << "\t\t***********************      *********************\n";
		std::cout << "\t\t**************************************************\n\n";
		std::cout << "\t\t\t\tusername: ";
		std::cin >> userName;
		std::cout << "\t\t\t\tpassword: ";
		std::cin >> passWord;

		access = checkAccess(userName, passWord);

		if (access)
		{
			system("cls");

			std::cout << "\n\t\t**************************************************\n";
			std::cout << "\t\t\t\t Welcome " << userName <<std::endl;
			std::cout << "\t\t**************************************************\n\n";
			std::cin.get();
			std::cout << "\n\t\t\t\tPress [Enter] to continue";
			std::cin.get();

			admin_menu();
		}

		else
		{
			std::cout << "\n\t\t\t Invalid username or password\n";
			std::cout << "\n\t\t\t Press [Enter] to continue";
			std::cin.get();
			std::cin.get();
		}
	}
}



// admin log-in

void admin_access()
{
	int op;

	do
	{
		system("cls");

		std::cout << "\t\t**************************************************\n";
		std::cout << "\t\t*                     WELCOME                    *\n";
		std::cout << "\t\t**************************************************\n\n\n";
		std::cout << "\t\t\t\t[1] Register\n";
		std::cout << "\t\t\t\t[2] login\n";
		std::cout << "\t\t\t\t[3] Exit\n";
		std::cout << "\n\t\t\t>Enter your choice: ";
		std::cin >> op;

		if (op == 1)
		{
			creatAcount();
		}
		else if (op == 2)
		{
			login();
		}

	} while (op != 3);
}





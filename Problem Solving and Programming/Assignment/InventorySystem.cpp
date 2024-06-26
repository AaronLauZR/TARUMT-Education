#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <stdio.h>
#include <time.h>
#include<fstream>
using namespace std;
void loginPage();
void login();
void forgot();
void displayHome();
void displayMenu();
void display_history();
int valid_input(char ch);
int input(int select);
void calculate_add();
void validate_take();
void calculate_take();
char decision;
int amount;
int choice;
int total;
int valid;
int num = 0;
string book[6] = { " 1. Newspaper          "," 2. Magazine           "," 3. Comic              "," 4. Novel              "," 5. Reference Book     "," 6. Story Book         " };
int stock[6] = { 1000,1000,1000,1000,1000,1000 };
const char* item[100];
int quantity[100];
int chance = 0;
char choices;
void loginPage()
{   // validate chance = 3 or not
	if (chance == 3) {
		cout << "Too many invalid login attempts.\nExiting.\n";
	}
	else {
		// show current date and time
		system("CLS");
		cout << "Current Date    : ";
		system("date/t");
		cout << "Current Time is : ";
		system("time/t");
		cout << endl;
		// display logo
		cout << "##########     ########     ########    #      ##   ##########   #########    " << endl;
		cout << "#         #   #        #   #        #   #    ##     #            #        #   " << endl;
		cout << "#        #    #        #   #        #   # ##        #            #        #   " << endl;
		cout << "#########     #        #   #        #   ##          #########    #########    " << endl;
		cout << "#        #    #        #   #        #   # ##        #            # ##         " << endl;
		cout << "#         #   #        #   #        #   #   ##      #            #   ##       " << endl;
		cout << "##########     ########     ########    #      ##   ##########   #     ###    " << endl << endl;
		//display loginPage
		cout << "****************************************" << endl;
		cout << "           Welcome to BOOKER            " << endl;
		cout << "****************************************" << endl << endl;
		cout << "   1. Login" << endl;
		cout << "   2. Forgot Password (or) Username" << endl;
		cout << "   3. Exit" << endl << endl;
		// display choice
		cout << " Enter your choice : ";
		//read choice
		cin >> choices;
		cout << endl;
		//validate choice
		if (isalpha(choices) != 0) {
			cout << "You've made a mistake , give it a try again" << endl;
			system("pause");
			loginPage();
		}
		else {

			switch (choices)
			{
			case '1':
				login();
				break;
			case '2':
				forgot();
				break;
			case '3':
				system("CLS");
				cout << "Current Date    : ";
				system("date/t");
				cout << "Current Time is : ";
				system("time/t");
				cout << endl;
				// display end logo
				cout << "#########   ####  ####         #          #####   ####   ###   ####   " << endl;
				cout << "#       #   #  #  #  #        #  #        #    #  #  #   # # ## ##    " << endl;
				cout << "#### ####   #  ####  #       #    #       #  #  # #  #   # ## ##      " << endl;
				cout << "   # #      #        #      #  ##  #      #  ##  ##  #   #   ##       " << endl;
				cout << "   # #      #  ####  #     #  #  #  #     #  # #  #  #   # ## ##      " << endl;
				cout << "   # #      #  #  #  #    #  ######  #    #  #  #    #   # # ## ##    " << endl;
				cout << "   ###      ####  ####   ####      ####   ####   #####   ###   ####   " << endl << endl;
				cout << "Thanks for using this program!" << endl;
				break;
			default:
				cout << "You've made a mistake , give it a try again" << endl;
				system("pause");
				loginPage();
			}
		}
	}

}

void login()
{
	int count = 0;
	string user, pass, u, p;
	system("cls");
	//display login
	cout << " Please enter the following details." << endl << endl;
	cout << "   USERNAME : ";
	cin >> user;
	cout << "   PASSWORD : ";
	cin >> pass;
	//read database
	ifstream input("database.txt");
	//loop until end of databse.txt
	while (input >> u >> p)
	{
		// if found,count = 1
		if (u == user && p == pass)

		{
			count = 1;
			system("cls");
		}
	}
	//when loop end and stop reading database.txt
	input.close();
	//validate username and password,if count=1 valid,else invalid
	if (count == 1)
	{
		cout << "Current Date    : ";
		system("date/t");
		cout << "Current Time is : ";
		system("time/t");
		cout << endl;
		cout << "LOGIN SUCCESSFUL!" << endl << endl;
		cout << "Hello " << user << "." << endl;
		cout << "We're glad that you're here." << endl << endl;
		cout << "Hope you enjoy using this program!" << endl;
		chance -= chance;
		system("pause");
		displayHome();
	}
	else
	{
		cout << "\nLOGIN ERROR\nPlease check your username and password\n";
		// if login error,chance increase 1.
		chance += 1;
		system("pause");
		loginPage();
	}


}


void forgot()
{
	int ch;
	system("cls");
	//display forgot choice
	cout << endl << " Forgotten username or password? We're here for help!" << endl << endl;
	cout << "   1. Search your password by username" << endl;
	cout << "   2. Search your username by password" << endl;
	cout << "   3. Return to Main menu" << endl << endl;
	cout << " Enter your choice :";
	cin >> ch;
	//validate choice
	switch (ch)
	{
	case 1:
	{
		int count = 0;
		string searchuser, su, sp;
		cout << "\nEnter your remembered username :";
		cin >> searchuser;
		//read database.txt
		ifstream input("database.txt");
		//loop until end of databse.txt
		while (input >> su >> sp)
		{
			//if found,count = 1
			if (su == searchuser)
			{
				count = 1;
			}
		}
		//when loop end and stop reading database.txt
		input.close();
		//if count = 1,user success to login.else error
		if (count == 1)
		{
			cout << "\n\nHurray, account found\n";
			cout << "\nYour password is " << sp << endl;
			system("pause");
			system("cls");
			loginPage();
		}
		else
		{
			cout << "\nSorry, Your userID is not found in our database\n";
			cout << "Please kindly contact your system administrator for more details \n" << endl;
			system("pause");
			loginPage();
		}
		break;
	}
	case 2:
	{
		int count = 0;
		string searchpass, su2, sp2;
		cout << "\nEnter the remembered password :";
		cin >> searchpass;
		//read database.txt
		ifstream input("database.txt");
		//loop until end of databse.txt
		while (input >> su2 >> sp2)
		{
			//if found ,count = 1
			if (sp2 == searchpass)
			{
				count = 1;
			}
		}
		//when loop end and stop reading database.txt
		input.close();
		//if count = 1,user success to login.else error
		if (count == 1)
		{
			cout << "\nYour password is found in the database \n";
			cout << "\nYour Id is : " << su2 << endl;
			system("pause");
			system("cls");
			loginPage();
		}
		else
		{
			cout << endl << "Sorry, We cannot found your password in our database \n";
			cout << "kindly contact your administrator for more information\n" << endl;
			system("pause");
			loginPage();
		}

		break;
	}

	case 3:
	{
		cin.get();
		loginPage();
		break;
	}
	default:
		cout << endl << "Sorry, You entered wrong choice. Kindly try again" << endl;
		system("pause");
		forgot();
		break;
	}
}


void displayHome() {
	//display time
	system("CLS");
	cout << "Current Date    : ";
	system("date/t");
	cout << "Current Time is : ";
	system("time/t");
	//display main menu
	cout << endl;
	cout << "==============================" << endl;
	cout << "             HOME             " << endl;
	cout << "==============================" << endl;
	cout << "      1. Edit                 " << endl;
	cout << "      2. View                 " << endl;
	cout << "      3. Inventory History    " << endl;
	cout << "      4. Logout               " << endl;
	cout << "==============================" << endl;
	cout << endl;
}

void displayMenu() {
	//display time
	system("CLS");
	cout << "Current Date    : ";
	system("date/t");
	cout << "Current Time is : ";
	system("time/t");
	cout << endl;
	cout << "==============================" << endl;
	cout << "          INVENTORY           " << endl;
	cout << "==============================" << endl;

	//display inventory menu
	for (int i = 0; i <= 5; i++) {
		cout << book[i] << " ";
		cout << stock[i] << endl;
	}
	cout << endl;
	// add or take
	cout << " Please choose what you want (1~6) : ";
	cin >> choice;
}

void displayInventory() {
	//display time
	system("CLS");
	cout << "Current Date    : ";
	system("date/t");
	cout << "Current Time is : ";
	system("time/t");
	cout << endl;
	//display inventory menu title
	cout << "==============================" << endl;
	cout << "          INVENTORY           " << endl;
	cout << "==============================" << endl;
	//display inventory menu
	for (int i = 0; i <= 5; i++) {
		cout << book[i] << " ";
		cout << stock[i] << endl;
	}
	cout << endl;
	system("pause");
}

int valid_input(char ch) {
	//validation for ch if is digit that it will return the error message
	if (isdigit(ch) != 0) {
		cout << "Digit is not allowed !" << endl;
	}
	//if the ch is in lowercase, it will automatically change to uppercase
	if (islower(ch) != 0) {
		ch = toupper(ch);
	}
	//validation for add(A) and take(T), if not A and T, it will display error message
	if (ch != 'A' && ch != 'T') {
		cout << "Please enter only 'A' or 'T'\n";
		cout << "Try Again !\n";
	}

	return ch;
}

void calculate_add() {
	//Prompt and get quantity
	cout << "Enter quantity to add : ";
	cin >> amount;

}

void validate_take() {
	do
	{
		//Prompt and get quantity
		cout << "Enter quantity to take:  ";
		cin >> amount;
		//Read user choice of inventory menu
		if (choice == 1)
		{
			//If user enter amount is greater than current inventory, display error message
			if (amount > stock[0])
			{
				cout << "Invalid ! The current inventory of newspaper is " << stock[0] << " only. Try again" << endl;
				valid = 0;
			}
			//If user enter an negative value
			else if (amount < 0)
			{
				cout << "Invalid ! Please enter only positive integer. Try again" << endl;
				valid = 0;
			}
			else
			{
				valid = 1;
			}
		}
		else if (choice == 2)
		{
			//If user enter amount is greater than current inventory, display error message
			if (amount > stock[1])
			{
				cout << "Invalid ! The current inventory of magazine is: " << stock[1] << " only. Try again" << endl;
				valid = 0;
			}
			//If user enter an negative value
			else if (amount < 0)
			{
				cout << "Invalid ! Please enter only positive integer. Try again" << endl;
				valid = 0;
			}
			else
			{
				valid = 1;
			}
		}
		else if (choice == 3)
		{
			//If user enter amount is greater than current inventory, display error message
			if (amount > stock[2])
			{
				cout << "Invalid ! The current inventory of comic is: " << stock[2] << " only. Try again" << endl;
				valid = 0;
			}
			//If user enter an negative value
			else if (amount < 0)
			{
				cout << "Invalid ! Please enter only positive integer. Try again" << endl;
				valid = 0;
			}
			else
			{
				valid = 1;
			}
		}
		else if (choice == 4)
		{
			//If user enter amount is greater than current inventory, display error message
			if (amount > stock[3])
			{
				cout << "Invalid ! The current inventory of novel is: " << stock[3] << " only. Try again" << endl;
				valid = 0;
			}
			//If user enter an negative value
			else if (amount < 0)
			{
				cout << "Invalid ! Please enter only positive integer. Try again" << endl;
				valid = 0;
			}
			else
			{
				valid = 1;
			}
		}
		else if (choice == 5)
		{
			//If user enter amount is greater than current inventory, display error message
			if (amount > stock[4])
			{
				cout << "Invalid ! The current inventory of reference book is: " << stock[4] << " only. Try again" << endl;
				valid = 0;
			}
			//If user enter an negative value
			else if (amount < 0)
			{
				cout << "Invalid ! Please enter only positive integer. Try again" << endl;
				valid = 0;
			}
			else
			{
				valid = 1;
			}
		}
		else if (choice == 6)
		{
			//If user enter amount is greater than current inventory, display error message
			if (amount > stock[5])
			{
				cout << "Invalid ! The current inventory of story book is: " << stock[5] << " only. Try again" << endl;
				valid = 0;
			}
			//If user enter an negative value
			else if (amount < 0)
			{
				cout << "Invalid ! Please enter only positive integer. Try again" << endl;
				valid = 0;
			}
			else
			{
				valid = 1;
			}
		}
	} while (valid == 0); //loop to prompt amount again if amount is invalid
}
void calculate_take() {

	//Calculate the final inventory base on user choice
	if (choice == 1)
	{
		//update stock
		stock[0] -= amount;
		cout << "Successful take " << amount << " newspaper." << endl;
		//store all information into array
		item[num] = " newspaper ";
		quantity[num] = -1 * amount;
		num++;
	}
	//Calculate the final inventory base on user choice
	else if (choice == 2)
	{
		//update stock
		stock[1] -= amount;
		cout << "Successful take " << amount << " magazine." << endl;
		//store all information into array
		item[num] = " magazine ";
		quantity[num] = -1 * amount;
		num++;
	}
	//Calculate the final inventory base on user choice
	else if (choice == 3)
	{
		//update stock
		stock[2] -= amount;
		cout << "Successful take " << amount << " comic." << endl;
		//store all information into array
		item[num] = " comic ";
		quantity[num] = -1 * amount;
		num++;
	}
	//Calculate the final inventory base on user choice
	else if (choice == 4)
	{
		//update stock
		stock[3] -= amount;
		cout << "Successful take " << amount << " novel." << endl;
		//store all information into array
		item[num] = " novel ";
		quantity[num] = -1 * amount;
		num++;
	}
	//Calculate the final inventory base on user choice
	else if (choice == 5)
	{
		//update stock
		stock[4] -= amount;
		cout << "Successful take " << amount << " reference book." << endl;
		//store all information into array
		item[num] = " reference book ";
		quantity[num] = -1 * amount;
		num++;
	}
	//Calculate the final inventory base on user choice
	else
	{
		//update stock
		stock[5] -= amount;
		cout << "Successful take " << amount << " story book." << endl;
		//store all information into array
		item[num] = " story book ";
		quantity[num] = -1 * amount;
		num++;
	}

}
void display_history() {
	system("CLS");
	// Display heading
	cout << "==========================" << endl;
	cout << "    Inventory History     " << endl;
	cout << "==========================" << endl;
	cout << "(oldest to latest)" << endl;
	// Loop to display inventory edit history
	for (int t = 0; t < num; t++)
	{
		if (quantity[t] < 0)
		{
			cout << "\n" << setw(16) << item[t] << quantity[t] << endl;
		}
		else
		{
			cout << "\n" << setw(16) << item[t] << "+" << quantity[t] << endl;
		}
	}
	system("pause");
}

int main() {
	//declare variable
	char option = 0;
	int ttl = 0;
	int sum;
	char select;

	loginPage();
	if (chance == 3) {
		return 0;
	}
	else if (choices == '3') {
		return 0;
	}
	else {
		do {
			do {
				//display main menu
				displayHome();
				//prompt user choice
				cout << " Enter your choice : ";
				cin >> select;
				//display error message if user input is character
				if (isalpha(select)) {
					cout << endl << "Character is not acceptable." << endl;
					system("pause");
				}
				//get user input and check
				else {
					input(select);
				}
				//loop again if user input is character, 2 or 3
			} while (select == '2' || isalpha(select) != 0 || select == '3');
			if (chance == 3) {
				return 0;
			}
			else if (choices == '3') {
				return 0;
			}

			do {
				displayMenu();
				//prompt and get user option
				cout << "\nPlease select you want to add(A) or take(T) : ";
				cin >> option;
				//validaiton for option
				option = valid_input(option);
				switch (option) {
				case 'A':
					if (choice == 1) {
						calculate_add();
						sum = amount;
						cout << "Successful add " << sum << " newspaper." << endl;
						stock[0] += sum;
						item[num] = " newspaper ";
						quantity[num] = amount;
						num++;
					}
					else if (choice == 2) {
						calculate_add();
						sum = amount;
						cout << "Successful add " << sum << " magazine" << endl;
						stock[1] += sum;
						item[num] = " magazine ";
						quantity[num] = amount;
						num++;
					}
					else if (choice == 3) {
						calculate_add();
						sum = amount;
						cout << "Successful add " << sum << " comic" << endl;
						stock[2] += sum;
						item[num] = " comic ";
						quantity[num] = amount;
						num++;
					}
					else if (choice == 4) {
						calculate_add();
						sum = amount;
						cout << "Successful add " << sum << " novel" << endl;
						stock[3] += sum;
						item[num] = " novel ";
						quantity[num] = amount;
						num++;
					}
					else if (choice == 5) {
						calculate_add();
						sum = amount;
						cout << "Successful add " << sum << " novel" << endl;
						stock[4] += sum;
						item[num] = " reference book ";
						quantity[num] = amount;
						num++;
					}
					else if (choice == 6) {
						calculate_add();
						sum = amount;
						cout << "Successful add " << sum << " novel" << endl;
						stock[5] += sum;
						item[num] = " story book ";
						quantity[num] = amount;
						num++;
					}
					else if (choice > 6 || choice < 1) {
						cout << "You have enter a wrong value" << endl;
						cout << "Please enter only digit (1-6):";
						cin >> choice;
						if (choice == 1) {
							calculate_add();
							sum = amount;
							cout << "Successful add " << sum << " newspaper." << endl;
							stock[0] += sum;
							item[num] = " newspaper ";
							quantity[num] = amount;
							num++;
						}
						else if (choice == 2) {
							calculate_add();
							sum = amount;
							cout << "Successful add " << sum << " magazine" << endl;
							stock[1] += sum;
							item[num] = " magazine ";
							quantity[num] = amount;
							num++;
						}
						else if (choice == 3) {
							calculate_add();
							sum = amount;
							cout << "Successful add " << sum << " comic" << endl;
							stock[2] += sum;
							item[num] = " comic ";
							quantity[num] = amount;
							num++;
						}
						else if (choice == 4) {
							calculate_add();
							sum = amount;
							cout << "Successful add " << sum << " novel" << endl;
							stock[3] += sum;
							item[num] = " novel ";
							quantity[num] = amount;
							num++;
						}
						else if (choice == 5) {
							calculate_add();
							sum = amount;
							cout << "Successful add " << sum << " novel" << endl;
							stock[4] += sum;
							item[num] = " reference book ";
							quantity[num] = amount;
							num++;
						}
						else if (choice == 6) {
							calculate_add();
							sum = amount;
							cout << "Successful add " << sum << " novel" << endl;
							stock[5] += sum;
							item[num] = " story book ";
							quantity[num] = amount;
							num++;
						}
						else if (choice > 6 || choice < 1) {
							cout << "You have enter a wrong value" << endl;
							cout << "You are going to exit now" << endl;
						}
					}
					break;
				case'T':
					validate_take();
					calculate_take();
					break;
				}
				//prompt user if he or she want to continue or not
				cout << endl << "Do you want to continue (Y/N) : ";
				cin >> decision;
			} while (decision == 'Y' || decision == 'y');
		} while (decision == 'N' || decision == 'n');

		return 0;
	}
}
int input(int select) {
	//if user input is 1, start the calculation
	if (select == '1') {
		displayMenu();
	}
	//if user input is 2, display inventory menu
	else if (select == '2') {
		displayInventory();
	}
	//if user input is 3, display edit history
	else if (select == '3') {
		display_history();
	}
	//if user input is 4, go back to login 
	else if (select == '4') {
		main();
	}
	//if user input is other digit, display error message and loop back
	else {
		cout << endl << "Please only enter the valid digit." << endl;
		system("pause");
	}
	return select;
}
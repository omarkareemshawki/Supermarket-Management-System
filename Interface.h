#pragma once
/*
* This heade contains functions for displaying interface
*/

#include<iostream>
#include"Functions.h"
#include"Product.h"
#include<algorithm>
#include"Customer.h"
#include<string>
#include<ctime>
using namespace std;
using namespace FUNCTIONS;
using namespace CUSTOMER;
#pragma warning(disable : 4996) // disabling warning regargind unsafe error

namespace INTER
{
	char user_state = 'c'; // state of the user (a - for admin, c - for customer)

	// declaration of funcrions
	Customer dummy("dum", 0, 'f', "cock@mail", "123456789");
	void adminView();
	void customerView(Customer &customer);
	void back(Customer &customer);
	void cartPointDelete(Customer customer);
	void cartTotalDelete(string cart_address, Customer &customer);
	void cartOrder(string cart_address, Customer &customer);
	void cartFunctionality(Customer &customer);
	void addToCart(string ID,string amount, Customer &customer);
	string cartPath(Customer& customer);

	void name() // printing out beatutiful name of the market
	{
		cout << "\x1b[36m";
		cout<<"\t    __  ___           __        __ "<<endl;
		cout<<"\t   /  |/  /___ ______/ /_____  / /_"<<endl;
		cout<< "\t  / /|_/ / __ `/ ___/ //_/ _ \\/ __/" <<endl;
		cout<<"\t / /  / / /_/ / /  /, < / __/ /_ " <<endl;
		cout<<"\t/_/  /_/\\__,_/_/  /_/|_|\\___/\\__/  " <<endl;
		cout << "\x1b[0m";
	}


	void passwordField(string password, char type,Customer c)
	{
		/// <summary>
		///		Function that prints field for passport and also checks if password is true
		/// </summary>
		/// <param name="password"> Reference password that is correct </param>
		/// <param name="type">  Wheather it is user or admin </param>
		string input = "";
		cout << "\n\n\n\t\t\t\t  Enter a password: ";
		frame("            ");
		cout << "\x1b[A";
		do { // asks for an input until password will match
			cout << "\n\t\t\t\t\x1b[2A\x1b[C";
			eraser(input.length() * 2); // deleting garbage
			cout << "\x1b[19C" <<"\x1b[36m" << char(186) << "\x1b[0m" << "\x1b[20D";
			getline(cin, input);

			// If password is wrong - prints type of an error
			if (input != password) {
				string error = "\n\n\t\t\tPassword is wrong!";
				if (input.length() > 12) { error = "\n\n\t\t\tInput is too long!"; }
				else if (input.length() < 6) { error = "\n\n\t\t\tInput is too short!"; }

				cout << error + "Please, try again. \x1b[2A";
			}

		} while (input != password);
		if (type == 'a') { adminView(); }
		else {
			string cart_path = cartPath(c);
			ifstream read_cart(cart_path, ios::binary | ios::app );
			customerView(c);
		}

	}
	

	void multipleFrames(string type, string buttons[], int size)
	{
		system("CLS");
		/// <summary>
		///		Creates long table with selection categories
		/// </summary>
		/// <param name="type"> Type of table(Naming to be displayed)</param>
		/// <param name="buttons">Array of needed buttons </param>
		/// <param name="size"> Size of that array</param>
		string blank = "", temp;
		cout << "\x1b[36m";
		cout << "\n\t\t     " + type + "\n\n";
		for (int i = 0; i < size; i++) // Diplay number of records
		{
			temp = buttons[i].substr(0, buttons[i].find(" "));
			temp = blank_adder(temp, 12);
			if (i == 0) {
				cout << "\t\t" << char(201);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(187) << endl;
			}
			else {
				cout << "\t\t" << char(204);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(185) << endl;
			}
			cout << "\t\t" << char(186) << "     \x1b[37m["+to_string(i+1)+"]\x1b[36m    " << char(186) << endl;
			cout << "\t\t" << char(186) << "\x1b[37m" << temp << "\x1b[36m" << char(186) << endl;
			temp = buttons[i].substr(buttons[i].find(" "));
			temp = blank_adder(temp, 12);
			cout << "\t\t" << char(186) << "\x1b[37m" << temp << "\x1b[36m" << char(186) << endl;
		}
		// Closing item with "Go back"
		cout << "\t\t" << char(204);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(185) << endl;
		cout << "\t\t" << char(186) << "     \x1b[37m[" + to_string(size + 1) + "]\x1b[36m    " << char(186) << endl;
		cout << "\t\t" << char(186) << "     \x1b[37mGo\x1b[36m     " << char(186) << endl;
		cout << "\t\t" << char(186) << "    \x1b[37mBack\x1b[36m    " << char(186) << endl;
		cout << "\t\t" << char(200);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(188) << endl;
		cout << "\x1b[0m"; // coloring end

	}

	
	void line()
	{
		cout << "\x1b[36m\n-------------------------------------------------------------------------------------------------------------------\x1b[0m\n";
	}


	void logo(int tabs) // function to dusplay a logo
	{
		string spaces = ""; // Adding particular amount of tabs
		for (int i = 0; i < tabs; i++) {
			spaces += "\t";
		}

		// displaying logo of our market
		cout <<spaces<< "\t                      ___/" << endl;
		cout <<spaces<< "\t           \\=========/    " << endl;
		cout <<spaces<< "\t            \\       /     " << endl;
		cout <<spaces<< "\t             \\-----/      " << endl;
		cout <<spaces<< "\t              o    o" << endl;
	}


	string IDchecker(Customer &customer)
	{
		/// <summary>
		///		Checks weather  inputed id exists or not
		/// </summary>
		/// <returns> Returns correct id that exists </returns>
		string id = "";
		do
		{
			eraser(id.size() * 5);
			getline(cin, id);
			if (id == "0") // "Go sBack" function
			{
				if (user_state == 'a') { adminView(); }
				else { customerView(customer); }
				break;
			}
			if ((isRecordExists(id, file_name) == 0)) // Asks input again if ID doesn`t exist
			{
				cout << "\x1b[A\t\tGiven ID doesn`t exist, try again: ";
			}
		} while (isRecordExists(id, file_name) == 0);
		id[0] = toupper(id[0]);
		return id;
	}


	string passwordVerification()
	{
		string password, repeated_password;
		cout << "\n\n\n\t\t\t\t  Enter a password: ";
		frame("            ");
		cout << "\n\n\n\t\t\t\t  Repeat a password: ";
		frame("            ");
		cout << "\x1b[9A\t\t\t\t\x1b[C";
		getline(cin, password);
		cout << "\n\n\n\n\n\n\n\n\t\t\t\t\x1b[25C"; // Adjust console cursor position
		do {// Checks if passwords matches
			cout << "\x1b[2A\x1b[24D";
			eraser(repeated_password.length() * 2);
			getline(cin, repeated_password);
			if (password != repeated_password) {
				cout << "\n\t\t\tPasswords don`t match! Try again.";
			}
		} while (password != repeated_password);
		return password;
	}


	void mainMenu()
	{
		load();
		/// <summary>
		///		Function that draws a menu and implements selection ofe one of the options
		/// </summary>
		system("CLS"); // clears screen
		name(); cout << endl;
		logo(0); // drawing logo

		cout << "\x1b[36m";
		// selection between admin account and customer account
		cout << "\n\t    " << char(201);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(203);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(187) << endl;
		cout << "\t    " << char(186) << "            " << char(186) << "            " << char(186) << endl;
		cout << "\t    " << char(186) << "  \x1b[37m[1]Admin\x1b[36m  " << char(186) << " \x1b[37m[2]Customer\x1b[36m" << char(186) << endl;
		cout << "\t    " << char(186) << "            " << char(186) << "            " << char(186) << endl;
		cout << "\t    " << char(200);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(202);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(188) << endl;
		cout << "\x1b[0m";
		cout << "\n\tWhat is the type of your account ?\n";

		// Selection logic
		cout << "\tSelect: ";
		string input,records, output; getline(cin, input);
		string answers[3] = { "1", "2"};
		output = variantChecker(input, answers, 2); // checks input
		if (output == "1")  // logins as admin
		{
			system("CLS");
			user_state = 'a'; //adminView(); 
			passwordField("Admin123", user_state, dummy);
		}
		if (output == "2") // logind or register as user 
		{
			records = getManyRecords(customer_db); // recieving list of all records
			system("CLS");
			string  user, password = "1", input, answers[3] = {"1", "2", "0"};
			frame("Select variant");
			cout << "\n\n\t\t\t       Do you have an account?\n" << endl;
			cout << "\t\t      [1] - YES\t\t [2] - NO\t [0] - Back" << endl;
			cout << "\n\t\t\t\t       Select: "; getline(cin, input);
			input = variantChecker(input, answers, 3);
			system("CLS");
			if (input == "1")
			{
				user_state = 'c'; //customerView();
				cout << "\n\n\n\t\t\t\t  Enter a login: ";
				frame("            ");
				cout << "\n\n\n\t\t\t\t  Enter a password: ";
				frame("            ");
				cout << "\x1b[8A ";
				do {//make the loop until login is not clear

					// Login checker
					cout << "\t\t\t\t\x1b[C\x1b[A";
					eraser(input.length() * 2);
					cout << "\x1b[19C\x1b[36m" << char(186) << "\x1b[0m\x1b[20D";
					getline(cin, input);
					// Asking for input again
					if (records.find(input) == string::npos || input.find('@') == string::npos) {
						cout << "\n\t\tThere is no such login. Try again. Or try to register \x1b[A\x1b[90D";
					}
				} while (records.find(input) == string::npos || input.find('@') == string::npos);
				cout << "\n";
				//gets password in order to compare
				password = findRecord(input, "Password", customer_db, 'v');
				password = password.substr(0, password.find("~"));
				// After login asks a password
				Customer customer(findRecord(input, "Name", customer_db, 'v'), stoi(findRecord(input, "Age", customer_db, 'v')), findRecord(input, "Gender", customer_db, 'v')[0], input, password, findRecord(input, "Identificator", customer_db, 'v'));
				passwordField(password, user_state, customer);
			}
			else if (input == "2")
			{
				// Prints out interface for registering
				string name, age, mail, gender;
				frame("Registering account");
				cout << "\n\t\tEnter name: \n";
				cout << "\n\t\tEnter age: \n";
				cout << "\n\t\tEnter gender: (M/F): \n";
				cout << "\n\t\tEnter email: ";

				// Inputing and checking of variables
				cout << "\x1b[6A"; getline(cin, name);
				name = inputChecker(name, 's', 50);
				cout << "\x1b[1B\t\t\t\x1b[4C"; getline(cin, age);
				age = inputChecker(age, 'n', 3);
				cout << "\x1b[1B\t\t\t\t\x1b[5C"; getline(cin, gender);
				string genders[4] = { "M","m", "F", "f" };
				gender = variantChecker(gender, genders, 4);
				cout << "\x1b[1B\t\t\x1b[13C"; getline(cin, mail);
				if (mail.find("@") != string::npos && records.find(mail) == string::npos) {} // Check if string contains the character or not
				else{ // Checking if email contains @ and if customer is alredy exists
					do{
						string error = "Input should contain @ character! Please try again: ";
						if (records.find(mail) != string::npos) {
							error = "Customer with this email alredy exists ! Try again:";
						}
						cout << "\n\t\t\x1b[2A";  //output for wrong input
						cout << error;
						eraser(mail.length() * 2);
						getline(cin, mail);
					} while (records.find(mail) != string::npos || mail.find("@") == string::npos);
				}
				system("CLS");
				// Password setter process
				password = passwordVerification();
				Customer customer(name, stoi(age), gender[0], mail, password);
				customer.write_r();
				customerView(customer);
			}
			else if (input == "0") { // Go back to menu
				mainMenu();
			}
		}
	}


	string categorySelection(Customer &customer)
	{
		/// <summary>
		///		Prints table with selection of different categories
		/// </summary>
		/// <returns> returns selected category </returns>
		system("CLS");
		string input;
		cout << "\x1b[36m";
		cout << "\n\t" << char(201);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(203);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(203); for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(187) << endl;
		cout << "\t" << char(186) << " \x1b[37m[1]Fruits\x1b[36m  " << char(186) << "            " << char(186) << "            " << char(186) << endl;
		cout << "\t" << char(186) << "    \x1b[37mand\x1b[36m     " << char(186) << "  \x1b[37m[2]Meat\x1b[36m   " << char(186) << " \x1b[37m[3]Milk\x1b[36m    " << char(186) << endl;
		cout << "\t" << char(186) << " \x1b[37mVegetables\x1b[36m " << char(186) << "            " << char(186) << "            " << char(186) << endl;
		cout << "\t" << char(204);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(206);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(206); for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(185) << endl;
		cout << "\t" << char(186) << "  \x1b[37m[4]Home\x1b[36m   " << char(186) << "            " << char(186) << "            " << char(186) << endl;
		cout << "\t" << char(186) << "  \x1b[37mSupplies\x1b[36m  " << char(186) << "  \x1b[37m[5]Bread\x1b[36m  " << char(186) << " \x1b[37m[6]Sweets\x1b[36m  " << char(186) << endl;
		cout << "\t" << char(186) << "            " << char(186) << "            " << char(186) << "            " << char(186) << endl;
		cout << "\t" << char(200);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(202);  for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(202); for (int i = 0; i < 12; i++) { cout << char(205); }  cout << char(188) << endl;
		cout << "\x1b[0m";
		cout << "\t\tTo go back - enter [0]" << endl;
		cout << "\n\tWhat do you want to buy? Select: ";

		string answers[7] = {"0", "1", "2", "3", "4", "5", "6"};
		getline(cin, input);
		int choice = stoi(variantChecker(input, answers, 7));

		switch (choice)
		{
		case 1:
			cout << "\nVegetables and fruits " << endl;;//should show fruits and vegetables that market has now
			return "Fruits&Vegetables";
			break;
		case 2:
			cout << "\nMeat" << endl;//should show kinds of meat that market has now
			return "Meat";
			break;
		case 3:
			cout << "\nMilk" << endl;//should show sorts of milk that market has now
			return "Milky";
			break;
		case 4:
			cout << "\nHome supplies" << endl;//should show home supplies that market has now
			return "Home.Supplies";
			break;
		case 5:
			cout << "\nBread" << endl;//should show kinds of bread that market has now
			return "Bread";
			break;
		case 6:
			cout << "\nSweets" << endl;//should show kinds of candies that market has now
			return "Sweets";
			break;
		case 0:
			if (user_state == 'a') { adminView(); }
			else { customerView(customer); }
		}
	}


	void adminView()
	{
		/// <summary>
		///		Function for sidplaying admin menu and implementing selection functions
		/// </summary>
		//writes a menu for admin view
		string buttons[5] = { "Show Products","Add Product","Change Product","Show Customers","Delete product"};
		multipleFrames("ADMIN", buttons, 5);

		// Selection logic
		Customer customer("Admin", 18, 'M', "admin@mail.com", "Admin123");
		cout << "\n\t\tSelect: ";
		string input; getline(cin, input);
		int output;
		string answers[6] = { "1", "2", "3", "4", "5", "6"}; // correct oprions for a menu 
		output = stoi(variantChecker(input, answers, 6)); // checks input

		switch(output)
		{
		case 1: // See all records from a particular category
		{
			system("CLS");
			string output, category = categorySelection(customer); // User selects category
			system("CLS");
			frame("Market`s products");
			line();
			cout << "\n" << getManyRecords(file_name, "Category", category);
			line();
			back(customer);

			break;
		}
		case 2: // Procedure of adding new product
		{
			string name = "", unit, amount, price, category;
			string records = getManyRecords(file_name);
			system("CLS");
			category = categorySelection(customer);
			Category category_obj(category);
			system("CLS");
			frame("Add product");
			line();
			// Printing interface
			cout << "\n\t\tEnter product name: " << endl;
			cout << "\n\t\tEnter measurement units: " << endl;;
			cout << "\n\t\tEnter quantity: " << endl;
			cout << "\n\t\tEnter price: " << endl;
			line();
			
			cout << "\x1b[9A\t\x1b[28C"; // Go to the position of interface
			do// Checks if record exists otherwise - ask for an input again
			{
				eraser(name.size()*10);
				getline(cin, name); 
				name = inputChecker(name, 's', 45);
				if (isRecordExists(name, file_name))
				{
					cout << "\x1b[A\t\tRecord already exists, try again: ";
				}
			} while (isRecordExists(name, file_name));
			// Assigning inputed values to variables
			cout << "\t\x1b[B\t\x1b[25C";
			getline(cin, unit); 
			unit = inputChecker(unit, 's', 15);
			cout << "\t\x1b[B\t\x1b[16C";
			getline(cin, amount);
			amount = inputChecker(amount, 'n', 6);
			cout << "\t\x1b[B\t\x1b[14C";
			getline(cin, price);
			price = inputChecker(price, 'n', 5);
			Product product(name, stod(price), stoi(amount), unit, category_obj);
			product.write_r();
			cout << "\n\n\t\tProduct has been added with id: " << product.getID() << endl;
			back(customer);
			break;
		}
		case 3: // Changing parameters of a product
		{
			system("CLS");
			//interface of changing menu
			frame("Change product");
			line();
			string id, item, new_value, answers[2] = {"Amount", "Price"};
			// Prints interface for inputing
			cout << "\n\t\tEnter ID of the item: ";
			cout << "\n\t\t\t{Put [0] for exit}";
			cout << "\n\n\t\tWhat do you want to change(Amount/Price): "; 
			cout << "\n\n\t\tEnter new value: \n";
			line();
			cout << "\x1b[8A\t\x1b[30C"; // Moves cursore to appropriate location

			id = IDchecker(customer); // checks if ID exists
			cout << "\x1b[2B\t\x1b[50C";
			getline(cin, item); item = variantChecker(item, answers, 2);
			cout << "\x1b[B\t\x1b[25C"; // moves cursor down to fit position
			getline(cin, new_value); inputChecker(new_value, 'n', 15);

			updateRecord(id, item, new_value, file_name);
			back(customer);
			break;
		}
		case 4: // Shows customers:
		{
			system("CLS");
			frame("Customers");
			cout << endl;
			// Objects of files
			ifstream show_customers(customer_db, ios::in); int counter = 1;

			line(); cout << endl;
			while (!show_customers.eof())//Shows customers of the shop
			{
				string temp, id;
				getline(show_customers, temp);
				if(temp.find("ID:") != string::npos){
					id = temp.substr(temp.find("ID:") + 4);
					id = id.substr(0,id.find(" "));
					// creating customer object
					Customer cust(findRecord(id, "Name", customer_db, 'v'), stoi(findRecord(id, "Age", customer_db, 'v')), findRecord(id, "Gender", customer_db, 'v')[0], id, findRecord(id, "Password", customer_db, 'v'));
					// Showing customer deatils
					cout << "\n\tCustomer \x1b[36m[" << counter << "]\x1b[0m";
					cout << cust;
					++counter;
				}

			}
			cout << endl;
			line();
			back(customer);
		}
		case 5: // Deletes product from a DB
		{
			system("CLS");
			string ID;
			frame("Delete Product");
			line();
			cout << "\n\t\tEnter product`s ID to delete: ";
			cout << "\n\t\t\tEnter [0] to go back\n";
			line();
			cout << "\x1b[4A\x1b[47C";
			ID = IDchecker(customer);
			deleteRecord(ID, file_name);
			cout << "\x1b[A";
			cout << "\t\tRecord " << ID << " has been deleted successfully\n";
			eraser(100); // erases garbadge
			back(customer);
			break;
		}
		case 6: // Go back to a menu
			mainMenu();
			break;
		}
	}


	void customerView(Customer &customer)
	{
		/// <summary>
		///		Function that draws menu for a customer
		/// </summary>
		
		// Displays client`s menu
		string buttons[4] = { "My Cart","Select Products","Show Cashback","Change Password" };
		multipleFrames("CLIENT", buttons, 4);
		
		// Selection logic
		cout << "\n\t\tSelect: ";
		string input; getline(cin, input);
		int output;
		string answers[5] = { "1", "2", "3", "4", "5"};
		output = stoi(variantChecker(input, answers, 5)); // checks input
		switch (output)
		{
		case 1: // Displaying user`s cart
		{
			system("CLS");
			frame("Your cart");
			line();
			cout << "\n";
			string path = cartPath(customer);
			cout << getManyRecords(path);
			line();
			cartFunctionality(customer);
			break;
		}
		case 2: // Add products to the cart
		{
			system("CLS");
			string id_input, amount = "", category = categorySelection(customer); // User selects category
			system("CLS");
			frame("Select product");
			// displaying list of records
			line();
			cout << "\n";
			string path = "products_db.nto";
			cout << getManyRecords(path, "Category", category);
			line();

			cout << "\t\t\tEnter item name to add to cart:  \n\t\t\t\tInput [0] to go back\x1b[A\x1b[6C"; 
			id_input = IDchecker(customer);
			do
			{
				cout << "\n\t\t\tEnter needed amount: "; eraser(amount.length()*2); getline(cin, amount);
				amount = inputChecker(amount, 'n', 2);
				if (stoi(amount) > stoi(findRecord(id_input, "Amount", file_name, 'v'))) {
					eraser(100);
					cout << "\t\t    We don`t have such amount! Please, try again.\x1b[2A";
					eraser(20);
				}
			} while (stoi(amount) > stoi(findRecord(id_input,"Amount",file_name, 'v')));
			
			addToCart(id_input, amount, customer);
			break;
		}
		case 3: // Shows user`s cashback
		{
			string id = customer.getID(); id = id.substr(0, id.find("~")); // getting user id
			system("CLS");
			frame("Your Cashback");
			line();
			cout << "\n\t\t\tYour saved cashback is: " << findRecord(customer.getEmail(), "Cashback", customer_db, 'v')<<"\x1b[1D$" << endl;;
			line();
			back(customer);
			break;
		}
		case 4: // Changing password
		{
			system("CLS");
			frame("Changing password");
			line();
			string id = customer.getEmail(),password = passwordVerification();
			updateRecord(id, "Password", password, customer_db);
			customerView(customer); // return to main page
			break;
		}
		case 5: // Going back to the menu
			mainMenu();
			break;
		}
	}


	void back(Customer &customer)
	{
		/// <summary>
		///		Function that go back to a customer or admin menu, depend on a type of user
		/// </summary>
		string selection, answers[1] = { "0" };
		cout << "\t\t\tTo go back - enter [0]: "; getline(cin, selection);
		if (selection != "0"){
			variantChecker(selection, answers, 1);
		}
		if (user_state == 'a') { adminView(); }
		else { customerView(customer); }
	}

	//##################################################### Cart operations for interface

	string cartPath(Customer &customer)
	{
		/// <summary>
		///		Function that gives a name to a cart
		/// </summary>
		/// <param name="customer"> Customer object for its id </param>
		/// <returns></returns>
		return "Carts/Cart_" + customer.getEmail()  + ".npo";
	}


	void addToCart(string ID,string amount, Customer &customer)
	{
		/// <summary>
		///		This function adds a product to a cart file of a user
		/// </summary>
		/// <param name="ID"> ID of a product to be added</param>
		/// <param name="customer"> object of a customer </param>
		
		// creating objects with recieved data
		Category category(findRecord(ID, "Category", file_name, 'v'));
		Product product(findRecord(ID, "Name", file_name, 'v'),  stod(findRecord(ID, "Price", file_name, 'v')), stod(findRecord(ID, "Amount", file_name, 'v')), findRecord(ID, "Measurement", file_name, 'v'), category, ID);
		// Adding producrs
		customer.addCart(product);
		product.setAmount(stoi(amount));
		writeRecording(product.getStrProduct(), cartPath(customer));
		eraser(100);
		cout << "\t\t\t" << product.getItemName() << " has been successfully added to a cart !\n";
		eraser(20);
		back(customer);
	}


	void cartFunctionality(Customer &customer)
	{
		/// <summary>
		///		This gunction provide an functionality of a cart
		/// </summary>
		/// <param name="customer"> Customer object </param>
		string selection, answers[3] = { "0", "1", "2" }, cart_address = cartPath(customer);
		cout << "\t\t\t\tTo go back - enter [0] \n\n" << "\t\t\tTo delete a Product from the cart - enter [1] \n" << "\t\t\t      To order the cart - enter [2]"<<endl<<"\t\t\t\t     Select: "; getline(cin, selection);
		variantChecker(selection, answers, 3);
		// According to user`s output choose what is need to be done
		if (selection == "0") { customerView(customer); }
		else if (selection == "1") // Deletion
		{
			// Here
			string delSelection, answers[2] = { "p", "a" };
			cout << "\n\n\t\t\tDo you want delete a particular product [p] from the cart \n\t\t\t\tor clear it all [a]? \t\t"; getline(cin, delSelection);
			variantChecker(delSelection, answers, 2);
			if (delSelection == "p") // Point deletion(one product)
			{
				cartPointDelete(customer);
			}
			else if (delSelection == "a") // Delete whole cart
			{
				cartTotalDelete(cart_address, customer);
				customerView(customer);
			}
		}
		else if (selection == "2") // Proceed order
		{
			string ordSelection, answers[2] = { "y", "n" };
			cout << "\n\t\t\t\x1b[36mAre you sure that it is your final order? [y/n]\x1b[0m"<<endl<<"\t\t\t\t\tSelect: "; getline(cin, ordSelection);
			variantChecker(ordSelection, answers, 2);
			if (ordSelection == "y")
			{
				cartOrder(cart_address, customer);
			}
			else
			{
				customerView(customer);
			}
		}
	}


	void cartPointDelete(Customer customer)
	{
		/// <summary>
		///		This function deletes only one recording from the cart
		/// </summary>
		/// <param name="customer"></param>
		string cart_address = cartPath(customer);
		system("CLS");
		frame("Here is your cart: ");
		line();
		cout << "\n\n" << getManyRecords(cart_address);
		line();
		string IDprod;
		// Visual interpritation
		cout << "\n\t\t\tEnter ID code of the product you want to delete: ";
		cout << "\n\t\t\tEnter [0] to go back\n";
		line();
		cout << "\x1b[4A\x1b[72C";
		IDprod = IDchecker(customer);
		
		deleteRecord(IDprod, cart_address);
		cout << "\x1b[A";
		cout << "\t\tRecord " << IDprod << " has been deleted successfully\n"; eraser(30);
		eraser(100); // erases garbadge
		back(customer);
	}

	
	void cartTotalDelete(string cart_address, Customer &customer)
	{
		/// <summary>
		///		This function clears whole cart
		/// </summary>
		/// <param name="cart_address"> address of a cart </param>
		/// <param name="customer"> Customer object </param>
		ofstream totDel(cart_address);
		totDel.write("", 0);
		totDel.close();
	}

	
	void cartOrder(string cart_address, Customer &customer)
	{
		/// <summary>
		///		Function that proceeds  order of a cutomer and then creates a cheque file
		/// </summary>
		/// <param name="cart_address"> Address of user`s cart </param>
		/// <param name="customer"> customerobject </param>
		system("CLS");
		string records = getManyRecords(cart_address), cheque_counter = "counters/cheque_counter.txt";
		// Drawing visual part 
		frame("Order status");
		cout << "\t\t\tYou order succesefully accepted! :)";
		line();
		cout << endl; logo(3);
		cout << "\n\t\t\t\t\t     Customer:"; cout << customer;
		line();
		cout << "\n" << records;

		// increases counter to give a promer name to a file
		int number = stoi(findRecord("cc3", "Value", cheque_counter, 'v'));
		double total_price = 0;
		updateRecord("cc3", "Value", to_string(number + 1), cheque_counter); // updating counter at file
		string cheque_address = "cheques/cheque_" + to_string(number)+".txt";

		// creating objects which work with files
		ofstream cheque_writer(cheque_address, ios::binary | ios::app | ios::out);
		cheque_writer.write(&records[0], records.length());
		ifstream cart_reader(cart_address, ios::binary | ios::in);
		while (!cart_reader.eof())
		{
			string temp, temp_id;
			getline(cart_reader, temp);
			if (temp.find("ID:") != string::npos)
			{
				// Reducing amount of bought products
				temp_id = temp.substr(temp.find("ID:") + 4, 8);
				total_price += stoi(findRecord(temp_id, "Amount", cart_address, 'v'))*stod(findRecord(temp_id, "Price", cart_address, 'v'));
				double new_amount = stoi(findRecord(temp_id, "Amount", file_name, 'v')) - stoi(findRecord(temp_id, "Amount", cart_address, 'v'));
				updateRecord(temp_id, "Amount", to_string(new_amount), file_name);
			}
		}
		total_price -= giveCashback(customer.getEmail());
		// Displaying other details
		cout << "\t\t\t\t Your cashback: " << giveCashback(customer.getEmail());
		cout << "\n\t\t\t\t Total price: " << "\x1b[36m" <<total_price << "\x1b[0m" <<"$";
		line();

		time_t t = time(0);
		tm* now = localtime(&t);

		// Recording info to the cheque
		string date = "Date of order: " + to_string(now->tm_mday) + '.' + "0" + to_string(now->tm_mon + 1) + '.' + to_string(now->tm_year + 1900) + "\n";
		string time = "Time of order: " + to_string(now->tm_hour) + ":" + to_string(now->tm_min) + ":" + to_string(now->tm_sec) + "\n";
		string customerInfo = "Name:" + customer.getName() + " | Age:" + to_string(customer.getAge()) + " | Gender:" + customer.getGender() + " | Email:" + customer.getEmail() + " | Cashback from the order:" + to_string(customer.getCashback()) + "\n";
		string divider = "\n\nPRODUCTS:\n\n";
		string price = "Total price: " + to_string(total_price) + "\n";

		// save new cheque
		writeRecording(date, cheque_address);
		writeRecording(time, cheque_address);
		writeRecording(customerInfo, cheque_address);
		writeRecording(price, cheque_address);
		writeRecording(divider, cheque_address);


		cashbackSetter(total_price, customer.getEmail());
		cartTotalDelete(cart_address, customer);
		// closing objects
		cheque_writer.close();
		cart_reader.close();
		back(customer);
	}
}
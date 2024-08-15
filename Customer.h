#pragma once
/*
* Header for customer functionality of the system
*/

#include<iostream>
#include<string>
#include"Cart.h"
#include<fstream>
using namespace std;
using namespace CART;

namespace CUSTOMER
{
	string c_counter_path = "counters/user_counter.txt";
	string customer_db = "customers_db.nto";
	class Customer // customer class implementation
	{
	private: // private data of costumer
		string name;
		int age;
		char gender;
		double cashback;
		static int counter;
		string id;
		string email;
		string password;
		Cart cart;
	public:
		Customer() { name = "default"; age = 0; gender = 'u'; password = "0"; id = "none"; } // default constructor
		Customer(string name, int age, char gender,string email, string password, string id = "none") // paramethrized constructor
		{
			this->name = name;
			this->age = age;
			this->gender = gender;
			this->email = email;
			if (id == "none" && customer_db.find(email) == string::npos) {
				this->id = name[0]; 
				this->id += gender;
				this->id += "-" + zero_placer(counter + 1) + to_string(counter + 1);
			}
			else {
				this->id = id;
			}
			this->password = password;

			//increase counter if person is already in a list
			if (getManyRecords(customer_db).find(email) == std::string::npos)
			{
				counter++;
				updateRecord("cc2", "Value", to_string(counter), c_counter_path);
			}
			cart.create();
		}

		// setter functions for data
		void setName(string name) { this->name = name; }
		void setAge(int age) { this->age = age; }
		void setGender(char gender) { this->gender = gender; }
		void setEmail(string email) { this->email = email; }
		void setCashback(double cashback) { this->cashback = cashback; }

		// getter functions for data
		string getName() { return name; }
		int getAge() { return age; }
		char getGender() { return gender; }
		string getID() { return id; }
		string getEmail() { return email; }
		double getCashback() { return cashback; }

		// cart operations
		void displayCart() {
			if (cart.getWholePrice(cart) > 0) {
				cout << cart;
			}
			else {
				cout << "\n\t\t\t Your cart is empty :( Fill it with something !\n";
			}
		}
		void addCart(Product p) { cart.add(p); } // adds product to a cart
		void delCart(int index) { cart.del(index); } // deletes product from a cart
		double getCartPrice() { return cart.getWholePrice(cart); }

		// methods for writing to file
		void write_r() // method to customer product to to the file
		{
			string record = "\nID: " + email + " | Identificator: " + id  +
				" | Name:" + name + " | Gender:" + getGender() + " | Age:" + to_string(getAge())
				+" | Password:" + password + "  | Cashback:" + to_string(getCashback()) + "~";
			writeRecording(record, customer_db);
		}


		//overloading operators for class
		friend void operator <<(ostream& output, Customer& c); // output operator
	};

	int Customer::counter = stoi(findRecord("cc2", "Value", c_counter_path, 'v'));; // initializing static variable

	void operator <<(ostream& output, Customer& c) // output operator
	{
		output << "\n\t\tName: " << c.getName() << " | E-mail: " << c.getEmail()
			<< " | Age: " << c.getAge() << " | Gender: " << c.getGender() <<" | " << endl;
	}
}
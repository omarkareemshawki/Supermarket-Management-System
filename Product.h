#pragma once
/*
  Header for product functionality of the project
*/

#include<iostream>
#include<string>
#include<stdlib.h>
#include<fstream>
#include"Functions.h"
using namespace std;
using namespace FUNCTIONS;

namespace PRODUCT 
{
	string file_name = "products_db.nto";
	string p_counter_path = "counters/product_counter.txt";

	class Item // item class inplementation
	{
	protected: //data members
		string item_name;
		int amount;
		double price_per_one;
		string measurement_unit;
	public:
		Item() // default constructor
		{
			item_name = "default"; 
			amount = 0; 
			price_per_one = 0; 
			measurement_unit = "default";
		}
		Item(string item_name, double price_per_one, int amount, string measurement) // paramethrized constructor
		{
			this->item_name = item_name;
			this->amount = amount;
			this->price_per_one = price_per_one;
			this->measurement_unit = measurement;
		}

		// setter functions
		void setItemName(string item_name) { this->item_name = item_name; }
		void setAmount(int amount) { this->amount = amount; }
		void setPrice(double rice_per_one) { this->price_per_one = price_per_one; }
		void setMeasurement(string measurement_unit) { this->measurement_unit = measurement_unit; }

		// getter functions
		string getItemName() { return item_name; }
		int getAmount() { return amount; }
		double getPrice() { return price_per_one; }
		string getMeasurement() { return measurement_unit; }
	};


	class Category // implementation of category for a product
	{
	protected:
		string category_name;
		char sign_letter; // letter, that emphasize sign of the category
	public:
		Category() // default constructor
		{ 
			category_name = "default";
			sign_letter = category_name[0];
		}
		Category(string category_name) // paramethrized constructor
		{
			this->category_name = category_name;
			sign_letter = category_name[0];
		}

		// setter function
		void setData(string category_name)
		{
			this->category_name = category_name;
			this->sign_letter = category_name[0];
		}

		// getter function
		string getCategoryName() { return category_name; }
		char getSignLetter() { return sign_letter; }
	};



	class Product : public Item // Derrived class from item
	{
	private:
		static int counter;
		string id;
		Category category;

	public:
		Product() { id = "0"; } // Default constructor
		Product(string item_name, int amount, double price, string measurement, Category category, string id = "0")
		:Item(item_name, amount, price, measurement) //constructor for a product
		{
			this->category = category;
			//logic to generate and set ID
			if (id == "0")
			{
				this->id = category.getSignLetter();
				this->id += "-" + zero_placer(counter) + to_string(counter);
			}
			else {
				this->id = id;
			}

			//if product is already in a DB, it will not affet counter
			if (getManyRecords(file_name).find(item_name) == std::string::npos)
			{
				counter++;
				updateRecord("pc1", "Value", to_string(counter), p_counter_path);
			}
		}

		~Product() {} // distructor

		// getter methods
		string getID() { return id; }
		string getStrProduct() {
			return "\nID: " + id + " | Category:" + category.getCategoryName() +
				" | Name:" + item_name + " | Measurement:" + measurement_unit +
				" | Price:" + to_string(price_per_one) + " | Amount:" + to_string(amount) + "~";
		}

		//overloading operators for class
		friend void operator << (ostream& output, Product& p); // output operator definition


		// methods for writing to file
		void write_r() // method to add product to to the file
		{
			writeRecording(getStrProduct(), file_name);
		}

		void delete_r() // method to delete product object from the file
		{
			deleteRecord(id, file_name);
		}

		void update_r(string item, string value) // edit product in the file
		{
			updateRecord(id, item, value, file_name);
		}
	};
	int Product::counter = stoi(findRecord("pc1", "Value", p_counter_path, 'v'));

	void operator << (ostream& output, Product& p) // output friend operator functionality
	{
		//printing output
		output << "ID: " << p.getID() << " | Category: " << p.category.getCategoryName();
		output << " | Name: " << p.getItemName() << " | Unit: " << p.getMeasurement()
			<< " | Price: " << p.getPrice() << " | Amount: " << p.getAmount() << endl;
	}	
}
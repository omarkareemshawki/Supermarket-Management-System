#pragma once
/*
* Implementation of shopping cart
*/

#include<iostream>
#include<string>
#include"Product.h"
using namespace std;
using namespace PRODUCT;

namespace CART
{
	class Cart
	{
	private: // data  
		int size;
		Product* items;
	public:
		void create() // creation of the new cart
		{
			size = 1;
			items = new Product[size];
		}

		void add(Product p) // addition to the cart
		{
			++size;
			Product* temp = new Product[size]; // temporary variable
			for (int i = 0; i < size - 1; i++)
			{
				temp[i] = items[i];
			}
			items = temp;
			items[size - 1] = p;
		}

		void del(int index) // deletion from the cart
		{
			Product* temp = new Product[size - 1]; // temporary variable
			int k = 0;
			for (int i = 0; i < size; i++)
			{
				if (i != index)
				{
					temp[k] = items[i];
					++k;
				}
			}
			--size;
			items = temp;
		}

		double getWholePrice(Cart& c) // return total price from the cart
		{
			double price = 0;
			for (int i = 0; i < c.size; i++)
			{
				price += c.items[i].getPrice();
			}
			return price;
		}
		friend void operator << (ostream& output, Cart& c); // output operator definition

	};
	void operator <<(ostream& output, Cart& c) // definition of overloadong operator
	{
		for (int i = 1; i < c.size; i++)
		{
			cout << "\n\t\t\t\t[Item #" << i << "]" << endl;
			cout << c.items[i];
		}
	}
}
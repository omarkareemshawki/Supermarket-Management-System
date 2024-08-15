#pragma once
/*
* Different functions that are used a lot
*/

#include<algorithm>
#include<iterator>
#include<iostream>
#include<string>
#include<Windows.h>
#include<fstream>
using namespace std;

namespace FUNCTIONS
{
	void eraser(int length); // declaration of a functions

	//########################## Functions which checks input or format informations
	string inputChecker(string &input, char type, int size = 100)
	{
		/// <summary>
		///		This functiom checks user`s input and ask for a new input till moment when input
		///		isecrted correctly
		/// </summary>	
		/// <param name="input"> User`s input </param>
		/// <param name="type"> 
		///		Weather it requiers number or string
		///		n - for number
		///		s - for string
		/// </param>
		/// <param name="size"> Size limit of the input </param>
		/// <returns> Appropriate output</returns>
		string error;
		bool checker = true;
		int length = input.length();
		do
		{
			checker = true;
			for (int i = 0; i < length; i++)
			{
				// checking which kind of error is  it
				if (isalpha(input[i]) && type == 'n') { error = "\x1b[A\tInput should contatin only numbers! Please, try again: "; }
				if (isdigit(input[i]) && type == 's') { error = "\x1b[A\tInput should contain only letters! Please, try again: "; }
				if (size < length) { error = "\x1b[A\tInput is too long! Please, try again: "; }
				// if there is not appropriate character  sets checker to false 
				if ((isalpha(input[i]) && type == 'n') || (isdigit(input[i]) && type == 's') || size < length){
					checker = false;
				}
			}
			if (checker == false){
				cout << error;
				eraser(length + error.size() / 2);
				// asking for an input again
				getline(cin, input);
				length = input.length();
			}
		} while (checker == false);
		return input;
	}
	string variantChecker(string input, string answers[], int arr_size = 0)
	{
		/// <summary>
		///		This function checks if given input exists in an array of possible
		///		variants of answer
		/// </summary>
		/// <param name="input"> User`s input</param>
		/// <param name="answers"> Array of possible answers </param>
		/// <param name="arr_size"> Size of an array </param>
		/// <returns> Returns correct user`s input</returns>
		string error = "\x1b[A\tNo such option! Please, try again: ";
		bool checker = false;
		do
		{
			for (int i = 0; i < arr_size; i++){
				if (answers[i] == input) { checker = true; }
			}
			if (checker == false){
				cout << error;
				// clears wrong user`s weong output
				eraser(input.size()*4);
				eraser(input.size()*4);
				getline(cin, input);
			}
		} while (checker == false);
		return input;
	}
	//######################### Functions for operation with files(reading writing)
	void writeRecording(string item, string location)
	{
		/// <summary>
		/// This function writes record into a specific file
		/// </summary>
		/// <param name="item"> Object to write into the file </param>
		/// <param name="location"> File in which </param>
		size_t size = item.size();
		fstream wr(location, ios::out | ios::app); // wr - write record
		wr.seekg(0, ios::end);
		wr.write(&item[0], item.length());
		wr.close();
	}


	string findRecord(string id, string item, string& location, char type)
	{
		/// <summary>
		///		This functions finds a record with particular id and then
		///		seek for a value or adress of it 
		/// </summary>
		/// <param name="id"> Record id number </param>
		/// <param name="item"> Demanded value to return </param>
		/// <param name="location"> File name </param>
		/// <param name="type">
		///		v - for value;
		///		p - for position; 
		/// </param>
		/// <returns> returns record or its address </returns>

		char buffer = 1024; // buffer for proceeding temp data
		string temp, result;
		int read_data = 0; // counts how muchdata was read
		ifstream rr(location, ios::out | ios::in); // rr - read record
		while (rr)
		{
			getline(rr, temp);
			if (temp.find(id) != std::string::npos){  // algorithm for extracting asked part of a record
				int position = temp.find(item);
				result = temp.substr((position + item.length() + 1), temp.find("~"));
				if (type == 'p') { return to_string(temp.find(result) + read_data); }
				if (item == "Amount"){ result = result.substr(0, result.find("~")); }
				else { result = result.substr(0, result.find(" ")); }
				break;
			}
			else { result = "\tWe didn`t find anything :("; }
			read_data += temp.length() + 1;
		}
		rr.close();
		if (type == 'v') { return result; }
	}


	string getlineRecord(string id, string& file)
	{
		/// <summary>
		///		Function find a record with particular ID and returns it
		/// </summary>
		/// <param name="id"> ID number of a record to be returned </param>
		/// <param name="file"> File name </param>
		/// <returns> 1 full record </returns>
		string temp;
		ifstream rr(file, ios::out | ios::in); // rr - read record
		while (rr){
			getline(rr, temp);
			if (temp.find(id) != std::string::npos){
				return temp;
			}
		}
		return "Nothing was found :(";
	}


	string getManyRecords(string& file, string field = "none", string value = "none")
	{
		/// <summary>
		///		This function collects all recordings and returns them as 1 string to be displayed
		/// </summary>
		/// <param name="file"> File name </param>
		/// <param name="field"> 
		///		Optional variable if user wants record with same value in a field in common 
		/// </param>
		/// <param name="value"> Value to be same for all records </param>
		/// <returns> string of many records </returns>
		string result = "", temp;
		ifstream rr(file); // rr - read record
		if (field != "none" && value != "none"){
			while (rr){
				getline(rr, temp);
				// checks if record`s value equals to user`s input and add it to result
				temp = temp.substr(0, temp.find("~"));
				if (temp.find(field) != std::string::npos){
					if (temp.substr(temp.find(field) + field.length() + 1, value.length()) == value && result.find(temp) == std::string::npos){
						result += temp + "\n\n";
					}
				}
			}
		}
		else{
			while (rr){
				int counter = 0;
				getline(rr, temp);
				// counts number of spaces
				for (int i = 0; i < temp.length(); i++) {
					if (temp[i] == ' ') { ++counter; }
				}				// don`t include blank lines into result
				temp = temp.substr(0, temp.find("~")); // deletes ~ sign from an output(it need to mark the end of a product)
				if (temp.find("ID:") != string::npos && result.find(temp) == string::npos) {
					result += temp.substr(0, temp.find("~")) + "\n\n";
				}
			}

		}
		// in case if there is no records
		if (result.length() <= 7) { result = "\t\tThere is no any record for your request, sorry :(\n"; }
		rr.close();
		return result;
	}


	void deleteRecord(string id, string& file)
	{
		/// <summary>
		///		Function deletes record with particular ID from a file 
		/// </summary>
		/// <param name="id"> ID of a record to be deleted</param>
		/// <param name="file"> File name </param>
		string blank = "";
		//creating number of whitespaces neded
		for (int i = 0; i < getlineRecord(id, file).length(); i++) { blank += " "; }
		int position = stoi(findRecord(id, "ID", file, 'p')) - 3;

		size_t size = blank.size();
		fstream dr(file, ios::out | ios::in); // dr - delete record
		dr.seekp(position, ios::beg); // go to position of element to delete
		dr.write(&blank[0], size);  // writing space on a place of a recording
		dr.close();
	}


	void updateRecord(string id, string item, string new_value, string& file)
	{
		/// <summary>
		///		This function updates the value of particular parameter in a recording
		///		with given ID
		/// </summary>
		/// <param name="id"> ID number of a record</param>
		/// <param name="item"> Item to be updated </param>
		/// <param name="new_value"> New value to change a parameter </param>
		/// <param name="file"> File name </param>F
		string record = getlineRecord(id, file), value = findRecord(id, item, file, 'v');

		string sand = record.substr(0, record.find(item) + item.length() + 1);
		string wich = record.substr(record.find(value) + value.length(), record.find("~")+1);

		string sandwich = "\n" + sand + new_value + wich + "\n";

		deleteRecord(id, file);

		writeRecording(sandwich, file);
	}


	bool isRecordExists(string &reference, string file)
	{
		/// <summary>
		///		This function checks if user`s inputed values is already esists in a DataBase
		/// </summary>
		/// <param name="reference"> Value to be checked</param>
		/// <param name="file"> File name </param>
		/// <returns> True - in case if it exists, otherwise - false </returns>
		string temp = getManyRecords(file);
		bool answer;
		reference[0] = toupper(reference[0]);
		if (temp.find(reference) == std::string::npos) { answer = false; }
		else
		{
			int pos = temp.find(reference);
			int size = reference.size();
			string value = temp.substr(pos);

			value = temp.substr(pos, size);
			// makes both value and reference to lowercase in order to compare more exactly
			for_each(value.begin(), value.end(), [](char& c) {
				c = ::tolower(c); });
			for_each(reference.begin(), reference.end(), [](char& c) {
				c = ::tolower(c); });

			if (value == reference) { answer = true; }
		}
		return answer;
	}
	
	//#################################################### Calculation functions
	void cashbackSetter(double price, string id)
	{
		/// <summary>
		///		Function returns amount of discoun depending 
		/// </summary>
		/// <param name="price"> total price from a cart </param>
		/// <returns> discount amount</returns>
		string customers = "customers_db.nto";
		double cashback = 0;
		if (price >= 300) { cashback = price * 10 / 100; }
		else if (price >= 100) { cashback = price * 5 / 100; }
		else { cashback = 0; }
		updateRecord(id, "Cashback", to_string(cashback), customers);
	}

	double giveCashback(string id) { // function that returs user`s cashback
		string path = "customers_db.nto";
		return stod(findRecord(id, "Cashback", path, 'v'));
	}
	
	//#################################################### Functions which formats output
	string zero_placer(int reference)
	{
		string zeros = "";
		// caluclates number of zeros to add to id
		for (int i = 0; i < 6 - to_string(reference).length(); i++){
			zeros += "0";
		}
		return zeros;
	}

	void eraser(int length)
	{
		/// <summary>
		///		Function, that erases incorrect output of a user
		/// </summary>
		/// <param name="length">length of an input</param>
		for (int n = length / 2; n > 0; n--) { cout << " "; }
		for (int n = length / 2; n > 0; n--) { cout << "\b"; }
	}


	void gotoxy(int x, int y) {
		//specifies the cursor position
		COORD d;
		d.X = x;
		d.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), d);
	}


	string blank_adder(string& item, int max_border)
	{
		/// <summary>
		///		This function adds spaces on voth vorder of a text in a frames
		/// </summary>
		/// <param name="item"> Item to be formated </param>
		/// <param name="max_border"> Maximum size inside border </param>
		/// <returns> Formated text </returns>
		int blank_needed = (max_border - item.size()) / 2;
		string blank = "";
		for (int i = 0; i < blank_needed; i++) { blank += " "; } // filling with spaces
		item = blank + item + blank;

		// if input id odd - change distrvution of spacesl;
		int size = item.size();
		if (size % max_border != 0)
		{
			if (size < 19) { item += " "; }
			else { item = item.substr(0, -2); }
		}
		return item;
	}


	void frame(string name)
	{
		/// <summary>
		///		This function prints a frame with given content
		/// </summary>
		/// <param name="name"> Content that should be inside the frame </param>
		// number of spaces needed
		blank_adder(name, 19);
		// Printing frame with content in it
		cout << "\x1b[36m";
		cout << "\n\t\t\t\t" << char(201);  for (int i = 0; i < 19; i++) { cout << char(205); }  cout << char(187) << endl;
		cout << "\t\t\t\t" << char(186); cout << "\x1b[37m" << name << "\x1b[0m\x1b[36m" << char(186) << endl;
		cout << "\t\t\t\t" << char(200);  for (int i = 0; i < 19; i++) { cout << char(205); }  cout << char(188) << endl;
		cout << "\x1b[0m";
	}


	void load() {
		system("CLS");
		char a = 219; //from ASCII code
		gotoxy(25, 8); //position of the horizontal and vertical lines
		cout <<"Loading...\n";
		gotoxy(20, 10); //for the space between "loading" and bars
		for (int r = 1; r <= 20; r++)//number of the loading bars
		{
			for (int q = 0; q <= 100000000; q++);//loop for controling the speed
			cout << a;
		}
	}
}

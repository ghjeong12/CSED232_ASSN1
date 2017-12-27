#include "Topping.h"

// Initialize an instance of Topping class.
Topping::Topping()
{
	this->name = "";
	this->price=0;
	this->sell_count=0;
	this->comment="";
	this->next = 0;

	for(int i =0 ;i < 10; i++)
	{
		this->ingredient[i] ="";
	}
}

void Topping::set_name(string name)
{
	this->name = name;
}

string Topping::get_name()
{
	return this->name;
}

void Topping::set_price(int price)
{
	this->price = price;
}

int Topping::get_price()
{
	return this->price;
}

void Topping::add_ingredient(string ingred)
{
	for(int i =0 ; i < 10; i++)
	{
		if(this->ingredient[i] == "")
		{
			(this->ingredient)[i] = ingred;
			return;
		}
	}
}
string* Topping::get_ingredient()
{
	return this->ingredient;
}

void Topping::set_comment(string com)
{
	this->comment = com;
}

string Topping::get_comment()
{
	return this->comment;
}

/* sell_count functions */
void Topping::inc_sellcount()
{
	this->sell_count++;
}

int Topping::get_sellcount()
{
	return this->sell_count;
}

/* Added for linked list */
void Topping::set_next_topping(Topping *top)
{
	this->next = top;
}

Topping* Topping::get_next_topping()
{
	return this->next;
}

/* Check whether ingredent of this topping has ingred_name or not */
bool Topping::has_ingredient(string ingred_name)
{
	string iter = (this->get_ingredient())[0];
	int i =1;
	while(iter!="")
	{
		if(iter == ingred_name)
			return true;

		if(i == 9)
			return false;	// There are at most 10 ingredients
		iter = (this->get_ingredient())[i++];
	}
	return false;
}

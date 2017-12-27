#include "Dough.h"

/* Initialize member variables for Dough class */
Dough::Dough()
{
	this->name = "";
	this->extra_cost=0;
	this->sell_count=0;
	this->comment="";
	this->next = 0;
	
	this->thickness=0.0;
}

void Dough::set_name(string name)
{
	this->name = name;
}

string Dough::get_name()
{
	return this->name;
}

void Dough::set_extra_cost(int cost)
{
	this->extra_cost = cost;
}

int Dough::get_extra_cost()
{
	return this->extra_cost;
}

void Dough::set_thickness(float thickness)
{
	this->thickness = thickness;
}

float Dough::get_thickness()
{
	return this->thickness;
}

void Dough::set_comment(string com)
{
	this->comment = com;
}

string Dough::get_comment()
{
	return this->comment;
}

void Dough::inc_sellcount()
{
	this->sell_count++;
}

int Dough::get_sellcount()
{
	return this->sell_count;
}

/* Added for linked list */
void Dough::set_next_dough(Dough* dou)
{
	this->next = dou;
}

Dough* Dough::get_next_dough()
{
	return this->next;
}

#include "Edge.h"

Edge::Edge()
{
	this->name = "";
	this->extra_cost=0;
	this->sell_count=0;
	this->comment="";
	this->next = 0;

	for(int i =0 ;i < 3; i++)
	{
		this->mousse[i] ="";
	}
}

void Edge::set_name(string name)
{
	this->name = name;
}

string Edge::get_name()
{
	return this->name;
}

void Edge::set_extra_cost(int cost)
{
	this->extra_cost = cost;
}

int Edge::get_extra_cost()
{
	return this->extra_cost;
}

void Edge::add_mousse(string mou)
{
	for(int i =0 ; i < 3; i++)
	{
		if(this->mousse[i] == "")
		{
			(this->mousse)[i] = mou;
			return;
		}
	}
}
string* Edge::get_mousse()
{
	return this->mousse;
}

void Edge::set_comment(string com)
{
	this->comment = com;
}

string Edge::get_comment()
{
	return this->comment;
}

/* Functions for sell_count */
void Edge::inc_sellcount()
{
	this->sell_count++;
}

int Edge::get_sellcount()
{
	return this->sell_count;
}
/* Added for linked list */
void Edge::set_next_edge(Edge *edge)
{
	this->next = edge;
}

Edge* Edge::get_next_edge()
{
	return this->next;
}

/* Check whether mousse of this edge has mousse_name or not */
bool Edge::has_mousse(string mousse_name)
{
	string iter = (this->get_mousse())[0];
	int i = 1;
	while(iter!="")
	{
		if(iter == mousse_name)
			return true;
		if(i == 2)
			return false; //There are at most 3 mousse

		iter = (this->get_mousse())[i++];
	}
	return false;
}

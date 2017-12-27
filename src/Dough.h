#include <iostream>
#include <string>
using namespace std;

class Dough
{
	private:
		string name;
		float thickness;
		int extra_cost;		
		int sell_count;
		string comment;
		Dough* next; // Added for list
	
	public:
		Dough();

		void set_name(string name);
		string get_name();
	
		void set_extra_cost(int cost);
		int get_extra_cost();
		
		void set_thickness(float thickness);
		float get_thickness();

		void inc_sellcount();
		int get_sellcount();

		void set_comment(string com);
		string get_comment();

		/* Added for linked list */
		void set_next_dough(Dough* dou);
		Dough* get_next_dough();
};

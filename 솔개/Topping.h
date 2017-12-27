#include <iostream>
#include <string>
using namespace std;

class Topping
{
	private:
		string name;
		string ingredient[10];
		int price;
		int sell_count;	// Shows how many orders were made with this topping
		string comment;
		Topping* next;	// Added for list

	public:
		Topping();			// Constructor without any parameter

		void set_name(string name);
		string get_name();
		
		void set_price(int price);
		int get_price();
		void add_ingredient(string ingred);
		string* get_ingredient();
		void set_comment(string comment);
		string get_comment();

		void inc_sellcount();
		int get_sellcount();

		void set_next_topping(Topping *top);	// Sets next topping as given parameter.
		Topping* get_next_topping();					// Return the member variable next.

		// Examine whether this topping has inged_name in its member variable ingredient.
		bool has_ingredient(string inged_name);
};

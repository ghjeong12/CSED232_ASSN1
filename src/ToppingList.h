#include "Topping.h"
#include <fstream>
class ToppingList
{
	private:
		Topping* head;	// If there is no element in the list, head will be set as 0.
		int size;				
	public:
		/* Constructor for ToppingList */
		ToppingList();

		void add(Topping* top);
		bool del(string top_name);

		Topping* pick(string top_name);	//Return Topping* whose name is top_name in the list.

		void show_all_menu();
		void show_most_popular();

		void search_by_ingred(string ing);
		
		/* Prints all Toppings whose price is higher or equal to low 
			 and lower or equal to high*/
		void search_by_price(int low, int high);	

		void save_topping();
};

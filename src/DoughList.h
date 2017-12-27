#include "Dough.h"

class DoughList
{
	private:
		Dough* head;
		int size;
	public:
		/* Constructor for DoughList */
		DoughList();

		void add(Dough* dou);
		bool del(string dou_name);

		Dough* pick(string dough_name);

		void show_all_menu();
		void show_most_popular();

		void search_by_thick(float low, float high);
		void save_dough();
};

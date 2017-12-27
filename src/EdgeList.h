#include "Edge.h"

class EdgeList
{
	private:
		Edge* head;
		int size;
	public:
		/* Constructor for EdgeList */
		EdgeList();

		void add(Edge* edge);
		bool del(string edge_name);

		Edge* pick(string edge_name);

		void show_all_menu();
		void show_most_popular();

		void search_by_mousse(string mou);
		
		void save_edge(); // Added for option 7
};

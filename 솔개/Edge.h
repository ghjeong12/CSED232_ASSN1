#include <iostream>
#include <string>
using namespace std;

class Edge
{
	private:
		string name;
		string mousse[3];
		int extra_cost;		
		int sell_count;
		string comment;
		Edge* next; // Added for list
	
	public:
		Edge();

		void set_name(string name);
		string get_name();
	
		void set_extra_cost(int cost);
		int get_extra_cost();
		
		void add_mousse(string mou);
		string* get_mousse();

		void inc_sellcount();
		int get_sellcount();

		void set_comment(string com);
		string get_comment();

		/* Added for linked list */
		void set_next_edge(Edge* edge);
		Edge* get_next_edge();

		/* Added to check whether mousse has mousse_name or not*/
		bool has_mousse(string mousse_name);
};

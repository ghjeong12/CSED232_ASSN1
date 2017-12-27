#include "EdgeList.h"
#include <fstream>
EdgeList::EdgeList()
{
	this->head = 0;
	this->size = 0;
}

// This function adds the given edge at the end of this list.
void EdgeList::add(Edge* edge)
{
	this->size++;

	if(this->head==0)
		this->head = edge;
	else
	{
		Edge* iter = head;
		while(iter->get_next_edge() != 0)
			iter = iter->get_next_edge();
		iter->set_next_edge(edge);
	}
}

bool EdgeList::del(string edge_name)
{
	if(this->size ==0)
		return false;
	else
	{
		Edge* prev =0 ;
		Edge* iter = this->head;
		while(iter!=0)
		{
			if(iter->get_name() == edge_name)
			{
				if(prev==0)
				{
					this->head=iter->get_next_edge();
					this->size--;
				}
				else
				{
					prev->set_next_edge(iter->get_next_edge());
					delete(iter);
					this->size--;
				}
				// If deletion is succesful, return true. Otherwise, return false.
				return true;
			}
			prev=iter;
			iter=iter->get_next_edge();
		}
		cout << "[ERROR] 해당 에지 이름을 가진 에지가 없습니다." << endl;
		return false;
	}
}

Edge* EdgeList::pick(string edge_name)
{
	if(this->size ==0)
		return 0;
	else
	{
		Edge* iter = this->head;
		while(iter != 0)
		{
			if(iter->get_name() == edge_name)
			{
				return iter;
			}
			iter = iter->get_next_edge();
		}
		return 0;	// There is no edge with such name.
	}
}

void EdgeList::show_all_menu()
{
	cout << "-EDGE <" << this->size << ">" << endl;
	if(this->size == 0)
	{
		cout<<"\n";
		return;
	}
	Edge* iter = head;
	while(iter != 0)
	{
		cout << "[이름:" << iter->get_name() << "]" ;
		cout << "[무스:";
		if((iter->get_mousse())[0]!="")
			cout << (iter->get_mousse())[0];
		// Should seperate each mousse using ','
		for(int i =1 ; (iter->get_mousse())[i] != ""; i++)
			cout << "," << (iter->get_mousse())[i];
		cout << "]";
		cout << "[추가비용:" << iter->get_extra_cost() << "원]";
		cout << "[소개말:" << iter->get_comment() << "]" << endl;

		iter = iter->get_next_edge();
	}
}
void EdgeList::show_most_popular(){
	cout <<"-EDGE 인기메뉴" <<endl;
	if(this->size==0)
	{
		cout <<"에지 메뉴가 하나도 없습니다." << endl;
		return ;
	}
	Edge* edge_top = this->head;

	Edge* iter = this->head->get_next_edge();
	while(iter!=0)
	{
		if(iter->get_sellcount() > edge_top->get_sellcount())
			edge_top = iter;
		iter = iter->get_next_edge();
	}
	cout << "[이름:" << edge_top->get_name() << "]" ;
	cout << "[무스:";
	if((edge_top->get_mousse())[0]!="")
		cout << (edge_top->get_mousse())[0];
	for(int i =1 ; (edge_top->get_mousse())[i] != ""; i++)
		cout << "," << (edge_top->get_mousse())[i];
	cout << "]";
	cout << "[추가비용:" << edge_top->get_extra_cost() << "원]";
	cout << "[소개말:" << edge_top->get_comment() << "]" << endl;


}

void EdgeList::search_by_mousse(string mou)
{
	int num = 0;
	if(this->size == 0)
	{
		cout<<"이상 총 0개가 검색되었습니다.";
		return;
	}
	Edge* iter = head;
	while(iter != 0)
	{
		if(iter->has_mousse(mou))
		{
			cout << "[이름:" << iter->get_name() << "]" ;
			cout << "[무스:";
			if((iter->get_mousse())[0]!="")
				cout << (iter->get_mousse())[0];
			for(int i =1 ; (iter->get_mousse())[i] != ""; i++)
				cout << "," << (iter->get_mousse())[i];
			cout << "]";
			cout << "[추가비용:" << iter->get_extra_cost() << "원]";
			cout << "[소개말:" << iter->get_comment() << "]" << endl;
			num++;
		}
		iter = iter->get_next_edge();
	}
	cout <<"이상 총 " << num << "개가 검색되었습니다." << endl;

}

// This function saves all the edges in this list.
void EdgeList::save_edge()
{
	ofstream outFile("save_menu.txt", ios::app);

	Edge* iter = this -> head;
	while(iter != 0)
	{
		if(iter != this -> head)
			outFile << "\r\n" ;
		outFile << iter->get_name() << "\t";
		if((iter->get_mousse())[0]!="")
			outFile << (iter->get_mousse())[0];
		for(int i =1 ; (iter->get_mousse())[i] != ""; i++)
			outFile << "," << (iter->get_mousse())[i];
		outFile << "\t" << iter->get_extra_cost() << "\t";
		outFile << iter->get_comment();
		iter=iter->get_next_edge();		
	}
}

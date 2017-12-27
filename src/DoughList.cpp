#include "DoughList.h"
#include <fstream>
DoughList::DoughList()
{
	this->head = 0;
	this->size = 0;
}

void DoughList::add(Dough* dough)
{
	this->size++;

	if(this->head==0) // if this list is empty
		this->head = dough;
	else	//if this list is not empty, add dough at the end of the list.
	{
		Dough* iter = head;
		while(iter->get_next_dough() != 0)
			iter = iter->get_next_dough();
		iter->set_next_dough(dough);
	}
}

bool DoughList::del(string dou_name)
{
	if(this->size==0) // If this list is empty, nothing can be deleted.
		return false; 
	else
	{
		Dough* prev = 0;
		Dough* iter = this->head;
		while(iter!=0)
		{
			if(iter->get_name() == dou_name)
			{
				// If dough with dou_name is found, delete the dough.
				if(prev==0)
				{
					this->head =iter->get_next_dough();
					delete(iter);
					this->size--;
				}
				else
				{
					prev->set_next_dough(iter->get_next_dough());
					delete(iter);
					this->size--;
				}
				return true;
			}
			prev = iter;
			iter=iter->get_next_dough();
		}
		return false;
	}

}

// Finds a Dough with dough_name and return its address.
Dough* DoughList::pick(string dough_name)
{
	if(this->size == 0)
		return 0;
	else
	{
		Dough* iter = this->head;
		while(iter != 0)
		{
			if(iter->get_name() == dough_name)
			{
				return iter;
			}
			iter = iter->get_next_dough();
		}
		return 0;	// There is no dough with such name.
	}
}

void DoughList::show_all_menu()
{
	cout << "-DOUGH <" << this->size << ">" << endl;
	if(this->size == 0)
	{	
		cout<<"\n";
		return;
	}
	Dough* iter = head;
	while(iter != 0)
	{
		cout << "[�̸�:" << iter->get_name() << "]" ;
		cout << "[�β�:";
		cout << iter->get_thickness() << "mm]";
		cout << "[�߰����:" << iter->get_extra_cost() << "��]";
		cout << "[�Ұ���:" << iter->get_comment() << "]" << endl;

		iter = iter->get_next_dough();
	}
}

void DoughList::show_most_popular(){
	cout << "-DOUGH �α�޴�" << endl;
	if(this->size == 0)
	{
		cout<<"���� �޴��� �ϳ��� �����ϴ�." << endl;
		return;
	}
	Dough* dough_top = this->head;
	Dough* iter = this->head->get_next_dough();
	// Finds the dough with highest sell_count
	while(iter != 0)
	{
		if(iter->get_sellcount() > dough_top->get_sellcount())
			dough_top = iter;
		iter = iter->get_next_dough();
	}
	cout << "[�̸�:" << dough_top->get_name() << "]" ;
	cout << "[�β�:";
	cout << dough_top->get_thickness() << "mm]";
	cout << "[�߰����:" << dough_top->get_extra_cost() << "��]";
	cout << "[�Ұ���:" << dough_top->get_comment() << "]" << endl;
}

void DoughList::search_by_thick(float low, float high)
{
	int num = 0;
	if(this->size ==0)
	{
		cout <<"�̻� �� 0���� �˻��Ǿ����ϴ�." <<endl;
		return ;
	}
	Dough* iter = this->head;
	
	// From head to tail of this list, print the object if it satisfies condition.
	while(iter != 0)
	{
		if(iter->get_thickness() >= low && iter->get_thickness() <= high)
		{
			cout << "[�̸�:" << iter->get_name() << "]" ;
			cout << "[�β�:";
			cout << iter->get_thickness() << "mm]";
			cout << "[�߰����:" << iter->get_extra_cost() << "��]";
			cout << "[�Ұ���:" << iter->get_comment() << "]" << endl;
			num++;
		}
		iter = iter->get_next_dough();
	}
	cout << "�̻� �� "<<num <<"���� �˻��Ǿ����ϴ�." << endl;
}
void DoughList::save_dough()
{
	ofstream outFile("save_menu.txt", ios::app);
	Dough* iter = this->head;

	while(iter!= 0)
	{
		outFile << iter->get_name() << "\t" << iter->get_thickness() << "\t";
		outFile << iter->get_extra_cost() << "\t" << iter->get_comment() << "\r\n";
		iter = iter->get_next_dough();
	}
}

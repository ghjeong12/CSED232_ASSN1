#include "ToppingList.h"

ToppingList::ToppingList()
{
	this->head = 0;
	this->size = 0;
}

void ToppingList::add(Topping* topping)
{
	this->size++;

	if(this->head==0)
		this->head = topping;
	else
	{
		Topping* iter = head;
		while(iter->get_next_topping() != 0)
			iter = iter->get_next_topping();
		iter->set_next_topping(topping);
	}
}

/*	This function deletes a topping from the list with top_name.
		Returns true if successs.
*/
bool ToppingList::del(string top_name)
{
	if(this->size==0) //There is no element in this list.
	{
		return false;
	}
	else
	{
		Topping* prev = 0;
		Topping* iter = this->head;
		while(iter != 0)
		{
			if(iter->get_name() == top_name)
			{
				if(prev == 0) //This topping is the head of the list.
				{
					this->head = iter->get_next_topping();
					this->size--;
				}
				else
				{
					prev->set_next_topping(iter->get_next_topping());
					delete(iter);
					this->size--;
				}
				return true;
			}
			prev = iter;
			iter=iter->get_next_topping();
		}
		return false; // There is no element with top_name.
	}
}

Topping* ToppingList::pick(string top_name)
{
	if(this->size==0) //There is no element in this list.
	{
		return 0;
	}
	else
	{
		Topping* iter = this->head;
		while(iter != 0)
		{
			if(iter->get_name() == top_name)
			{
				return iter;
			}
			iter=iter->get_next_topping();
		}
		return 0; // There is no element with top_name.
	}
}

void ToppingList::show_all_menu()
{
	cout << "-TOPPING <" << this->size << ">" << endl;
	if(this->size == 0)
	{
		cout<<"\n";
		return;
	}
	Topping* iter = head;
	while(iter != 0)
	{
		cout << "[이름:" << iter->get_name() << "]" ;
		cout << "[재료:";
		if((iter->get_ingredient())[0]!="")
			cout << (iter->get_ingredient())[0];
		for(int i =1 ; (iter->get_ingredient())[i] != ""; i++)
			cout << "," << (iter->get_ingredient())[i];
		cout << "]";
		cout << "[가격:" << iter->get_price() << "원]";
		cout << "[소개말:" << iter->get_comment() << "]" << endl;

		iter = iter->get_next_topping();
	}
}

// This function prints the information about the most famous topping.
void ToppingList::show_most_popular(){
	cout <<"-TOPPING 인기메뉴"<<endl;
	if(this->size==0)
	{
		cout <<"토핑 메뉴가 하나도 없습니다." <<endl;
		return;
	}
	Topping* topping_top = this->head;
	
	Topping* iter = this->head->get_next_topping();
	while(iter != 0)
	{
		if(iter->get_sellcount() > topping_top->get_sellcount())
			topping_top = iter;
		iter = iter->get_next_topping();
	}

	cout << "[이름:" << topping_top->get_name() << "]" ;
	cout << "[재료:";
	if((topping_top->get_ingredient())[0]!="")
		cout << (topping_top->get_ingredient())[0];
	for(int i =1 ; (topping_top->get_ingredient())[i] != ""; i++)
		cout << "," << (topping_top->get_ingredient())[i];
	cout << "]";
	cout << "[가격:" << topping_top->get_price() << "원]";
	cout << "[소개말:" << topping_top->get_comment() << "]" << endl;


}

void ToppingList::search_by_ingred(string ingred_name)
{
	int num = 0;
	if(this->size == 0)
	{
		cout<<"이상 총 0개가 검색되었습니다." << endl;;
		return;
	}
	Topping* iter = this->head;
	while(iter != 0)
	{
		if(iter->has_ingredient(ingred_name))
		{
			cout << "[이름:" << iter->get_name() << "]" ;
			cout << "[재료:";
			if((iter->get_ingredient())[0]!="")
				cout << (iter->get_ingredient())[0];
			for(int i =1 ; (iter->get_ingredient())[i] != ""; i++)
				cout << "," << (iter->get_ingredient())[i];
			cout << "]";
			cout << "[가격:" << iter->get_price() << "원]";
			cout << "[소개말:" << iter->get_comment() << "]" << endl;
			num++;	
		}
		iter = iter->get_next_topping();
	}
	cout <<"이상 총 " << num << "개가 검색되었습니다." << endl;

}
void ToppingList::search_by_price(int low, int high)
{
	int num = 0;
	if(this->size == 0)
	{
		cout<<"이상 총 0개가 검색되었습니다" << endl;;
		return;
	}
	Topping* iter = this->head;
	while(iter != 0)
	{
		// Check whether the price satisfies the condition.
		if(iter->get_price() >= low && iter->get_price() <= high)
		{
			cout << "[이름:" << iter->get_name() << "]" ;
			cout << "[재료:";
			if((iter->get_ingredient())[0]!="")
				cout << (iter->get_ingredient())[0];
			for(int i =1 ; (iter->get_ingredient())[i] != ""; i++)
				cout << "," << (iter->get_ingredient())[i];
			cout << "]";
			cout << "[가격:" << iter->get_price() << "원]";
			cout << "[소개말:" << iter->get_comment() << "]" << endl;
			num++;	
		}
		iter = iter->get_next_topping();
	}
	cout <<"이상 총 " << num << "개가 검색되었습니다." << endl;


	return;
}

// This function saves all the toppings in this list.
void ToppingList::save_topping()
{
	ofstream outFile("save_menu.txt", ios::app);
	Topping* iter = this->head;
	while(iter != 0)
	{
		outFile << iter->get_name() << "\t";
		if(iter->get_ingredient()[0]!="")
			outFile<< (iter->get_ingredient())[0];
		for(int i = 1; (iter->get_ingredient())[i] != ""; i++)
		{
			outFile<<"," << (iter->get_ingredient())[i];
		}
		outFile << "\t" << iter->get_price() << "\t" << iter->get_comment();
		outFile << "\r\n";
		iter = iter->get_next_topping();
	}
	outFile.close();
	return ;
}

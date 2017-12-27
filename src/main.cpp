#include <iostream>
#include "ToppingList.h"
#include "DoughList.h"
#include "EdgeList.h"
//���� 
void read_pizzas(ToppingList* t, DoughList* d, EdgeList* e);
void order_pizza(ToppingList* t, DoughList* d, EdgeList* e);
void add_menu(ToppingList* t, DoughList* d, EdgeList* e);
void del_menu(ToppingList* t, DoughList* d, EdgeList* e);
void search_menu(ToppingList* t, DoughList* d, EdgeList* e);
int print_options();
int read_int();
void save_file(ToppingList* t, DoughList* d, EdgeList* e);

int main()
{
	int option=-1;
	ToppingList* topping_list = new ToppingList();
	DoughList* dough_list = new DoughList();
	EdgeList* edge_list = new EdgeList();
	read_pizzas(topping_list, dough_list, edge_list);

	/* select menu and run */
	while(option!=6)
	{
		option = print_options();
		switch(option)
		{
			case 0:
			{
				topping_list->show_all_menu();
				cout << "\n";
				dough_list->show_all_menu();
				cout << "\n";
				edge_list->show_all_menu();
				break;
			}
			case 1:
			{
				order_pizza(topping_list, dough_list, edge_list);	
				break;
			}
			case 2:
			{
				add_menu(topping_list, dough_list, edge_list);
				break;
			}
			case 3:
			{
				del_menu(topping_list, dough_list, edge_list);
				break;
			}
			case 4:
			{
				search_menu(topping_list, dough_list, edge_list);
				break;
			}
			case 5:
			{
				topping_list->show_most_popular();
				dough_list->show_most_popular();
				edge_list->show_most_popular();
				break;
			}
			case 6: 
				return 0; // Terminate this program
			case 7:
			{
				save_file(topping_list, dough_list, edge_list);
				break;
			}
			default:
				cout << "[ERROR} This program shouldn't reach here." << endl;
		}		
	}
	cout << "[ERROR] This program shouldn't reach here." << endl;
	return 0;
}

/* This funtion reads informations about toppings, doughs and edges from init_menu.txt and save it to the lists */

void read_pizzas(ToppingList* topping_list, DoughList* dough_list, EdgeList* edge_list)
{
	ifstream read_file("init_menu.txt");
	if(!(read_file))
	{
		cout << "[FATAL INPUT ERROR] init_menu�� �ش��ϴ� ������ �����ϴ�." << endl;
		return ;
	}
	string name;
	read_file >> name;
	if(name!="-����")
	{
		// �־��� ���Ŀ� ���� -���� �±װ� �־���Ѵ�.
		cout << "[FATAL INPUT ERROR]" << endl;
		return ;
	}
	Topping* new_topping;
	while(!read_file.eof())
	{
		new_topping = new Topping();
		string top_name;
		read_file >> top_name;

		string top_ingreds;
		read_file >> top_ingreds;
		//','�� ingredient �� ���е� ��� �Ľ��ؼ� �־��ش�.
		while(top_ingreds.find(',') != -1)
		{
			new_topping->add_ingredient( top_ingreds.substr(0, top_ingreds.find(',')) );
			top_ingreds = top_ingreds.substr(top_ingreds.find(',')+1, top_ingreds.length());
		}
		new_topping->add_ingredient(top_ingreds);

		int top_price;
		read_file >> top_price;
		
		read_file.get();

		string top_comment;
		getline(read_file, top_comment, '\n');
		
		if(top_comment.at(top_comment.length()-1) == 13)
			top_comment=top_comment.substr(0, top_comment.length()-1);
		
		new_topping->set_name(top_name);
		new_topping->set_price(top_price);
		new_topping->set_comment(top_comment);
		topping_list->add(new_topping);
		if(read_file.peek() == '-')
		{	
			break;
		}
	}

	read_file >> name;
	Dough* new_dough;
	while(!read_file.eof())
	{
		new_dough = new Dough();
		string dough_name;
		read_file >> dough_name;

		float dough_thickness;
		read_file >> dough_thickness;

		int dough_extra_cost;
		read_file >> dough_extra_cost;
		
		read_file.get();

		string dough_comment;
		// ������ ��� ������ �Է��� �� �����Ƿ� getline �Լ��� �̿��Ѵ�.
		getline(read_file, dough_comment, '\n');
		if(dough_comment.at(dough_comment.length()-1)==13)
			dough_comment=dough_comment.substr(0, dough_comment.length()-1);
		
		new_dough->set_name(dough_name);
		new_dough->set_extra_cost(dough_extra_cost);
		new_dough->set_thickness(dough_thickness);
		new_dough->set_comment(dough_comment);
		dough_list->add(new_dough);
		if(read_file.peek() == '-')
		{	
			break;
		}

	}
	// ���� �Է� ����
	read_file >> name;
	Edge* new_edge;
	int count = 0;
	while(!read_file.eof())
	{
		new_edge = new Edge();
		string edge_name;
		read_file >> edge_name;
		
		read_file.get();
		if(read_file.peek()!=' ')
		{
			string edge_mousse;
			read_file >> edge_mousse;
			// �Ѱ� �̻��� ������ �����Ͽ� , �� ���е� ��� �Ľ��Ͽ� �־��ش�.
			while(edge_mousse.find(',') != -1)
			{
				new_edge->add_mousse( edge_mousse.substr(0, edge_mousse.find(',')) );
				edge_mousse = edge_mousse.substr(edge_mousse.find(',')+1, edge_mousse.length());
			}
			new_edge->add_mousse(edge_mousse);
		}
		else
			new_edge->add_mousse(" ");
		int edge_extra_cost;
		read_file >> edge_extra_cost;
		
		read_file.get();

		string edge_comment;
		getline(read_file, edge_comment, '\n');
		if(!read_file.eof() && (edge_comment.at(edge_comment.length()-1)==13))
			edge_comment=edge_comment.substr(0, edge_comment.length()-1);
		
		new_edge->set_name(edge_name);
		new_edge->set_extra_cost(edge_extra_cost);
		new_edge->set_comment(edge_comment);
		edge_list->add(new_edge);
	}
}
void order_pizza(ToppingList* topping_list, DoughList* dough_list, EdgeList* edge_list)
{
	int pizza_price = 0;
	string pizza_name="";
	string order_topping_name;
	string order_dough_name;
	string order_edge_name;

	topping_list->show_all_menu();
	cout << "\n";
	cout << "���Ͻô� ���� �̸��� �Է��ϼ���." << endl;
	cout << ">> ";
	cin >> order_topping_name;
	if(topping_list->pick(order_topping_name) == 0)
	{
		cout << "[ERROR] �ش��ϴ� ���� �̸��� ���� ������ �����ϴ�." << endl;
		cin.ignore();
		return;
	}

	Topping* order_topping = topping_list->pick(order_topping_name);
	pizza_price += order_topping->get_price();
	pizza_name = order_topping->get_name();
	
	dough_list->show_all_menu();
	cout << "\n";
	cout << "���Ͻô� ���� �̸��� �Է��ϼ���." << endl;
	cout <<">> ";
	cin >> order_dough_name;
	if(dough_list->pick(order_dough_name) == 0)
	{
		cout << "[ERROR] �ش��ϴ� ���� �̸��� ���� ���찡 �����ϴ�." << endl;
		cin.ignore();
		return;
	}
	Dough* order_dough = dough_list->pick(order_dough_name);
	pizza_price += order_dough->get_extra_cost();

	edge_list->show_all_menu();
	cout << "\n";
	cout << "���Ͻô� ���� �̸��� �Է��ϼ���." << endl;
	cout <<">> ";
	cin >> order_edge_name;
	if(edge_list->pick(order_edge_name)==0)
	{
		cout<<"[ERROR] �ش��ϴ� ���� �̸��� ���� ������ �����ϴ�." << endl;
		cin.ignore();
		return;
	}
	Edge* order_edge = edge_list->pick(order_edge_name);
	// ���� ���ݿ� �߰� ����� ���Ѵ�.
	pizza_price += order_edge->get_extra_cost();
	// ���� �̸��� ���� ������ ���� ���Ŀ� �°� �����.
	pizza_name = order_dough->get_name() + " " + order_edge->get_name() + " " + pizza_name;

	cout << "\n�ֹ��Ͻ� ���ڴ� \"" << pizza_name << "\" �Դϴ�." << endl;
	cout << "������ \"" << pizza_price << "\"�� �Դϴ�." << endl;
	// sellcount �� �������Ѽ� ���߿� �α� �޴��� Ȯ���� �� �ݿ��ǵ��� �Ѵ�.
	order_topping->inc_sellcount();
	order_dough->inc_sellcount();
	order_edge->inc_sellcount();
	cin.ignore();
}

void add_menu(ToppingList* topping_list, DoughList* dough_list, EdgeList* edge_list)
{
	cout << "�߰��ϰ��� �ϴ� �޴��� ������ �����ϼ���." << endl;
	cout << "1: ����\n2: ����\n3: ����"<< endl;
	cout << ">> " ;
	int type_add;
	cin >> type_add;
	switch(type_add)
	{
		case 1:
		{
			Topping* new_topping = new Topping();
			string top_name;
			cout <<"�̸�\n>> ";
			cin >> top_name;
						
			cout <<"���\n>> ";
			string top_ingreds;
			cin >> top_ingreds;
			// �ϳ� �̻��� ��Ḧ �Է��� ��� ',' ������ �Ľ��Ͽ� �־��ش�.
			while(top_ingreds.find(',') != -1)
			{
				new_topping->add_ingredient( top_ingreds.substr(0, top_ingreds.find(',')) );
				top_ingreds = top_ingreds.substr(top_ingreds.find(',')+1, top_ingreds.length());
			}
			new_topping->add_ingredient(top_ingreds);
						
			cout <<"����\n>> ";
			int top_price;
			cin >> top_price;
			if(cin.fail())
			{
				cin.clear();
				cout << "[ERROR] ���� �Է��� �߸��Ǿ����ϴ�." << endl;
				cin.ignore(100,'\n');
				return;
			}
		
			cout<<"�Ұ���\n>> ";
			string top_comment;
			cin.ignore();
			getline(cin, top_comment);
		
			new_topping->set_name(top_name);
			new_topping->set_price(top_price);
			new_topping->set_comment(top_comment);
			topping_list->add(new_topping);
			cout <<"�޴� �߰��� �Ϸ�Ǿ����ϴ�.\n" << endl;

			topping_list->show_all_menu();
			break;	
		}
		case 2:
		{
			string name;
			float thickness;
			int extra_cost;
			string comment;
			cout << "�̸�\n>> ";
			cin >> name;
			cout << "�β�\n>> ";
			if(cin.fail())
			{
				cin.clear();
				cout << "[ERROR] �β� �Է��� �߸��Ǿ����ϴ�." << endl;
				cin.ignore(100,'\n');
				return;
			}

			cin >> thickness;
			cout << "�߰����\n>> ";
			cin >> extra_cost;
			if(cin.fail())
			{
				cin.clear();
				cout << "[ERROR] �߰���� �Է��� �߸��Ǿ����ϴ�." << endl;
				cin.ignore(100,'\n');
				return;
			}
			cout << "�Ұ���\n>> ";
			cin.ignore();
			getline(cin, comment);
			Dough* dough = new Dough();
			dough->set_name(name);
			dough->set_extra_cost(extra_cost);
			dough->set_thickness(thickness);
			dough->set_comment(comment);
			dough_list->add(dough);
			cout << "�޴� �߰��� �Ϸ�Ǿ����ϴ�.\n" << endl;

			dough_list->show_all_menu();
			break;
		}
		case 3:
		{
			Edge* new_edge = new Edge();
			string edge_name;
			cout <<"�̸�\n>> ";
			cin >> edge_name;
			
			string edge_mousse;
			cout <<"����\n>> ";
			cin >> edge_mousse;
			// �ϳ� �̻��� ������ �Է��� ��� ',' ������ �Ľ��Ͽ� �־��ش�.
			while(edge_mousse.find(',') != -1)
			{
				new_edge->add_mousse( edge_mousse.substr(0, edge_mousse.find(',')) );
				edge_mousse = edge_mousse.substr(edge_mousse.find(',')+1, edge_mousse.length());
			}
			new_edge->add_mousse(edge_mousse);
						
			cout << "�߰����\n>> ";

			int edge_extra_cost;
			cin >> edge_extra_cost;
			if(cin.fail())
			{
				cin.clear();
				cout << "[ERROR] �߰���� �Է��� �߸��Ǿ����ϴ�." << endl;
				cin.ignore(100,'\n');
				return;
			}
	
			//read_file.get();
			cout<<"�Ұ���\n>> ";
			string edge_comment;
			cin.ignore();
			getline(cin, edge_comment, '\n');

			new_edge->set_name(edge_name);
			new_edge->set_extra_cost(edge_extra_cost);
			new_edge->set_comment(edge_comment);
			edge_list->add(new_edge);
			cout <<"�޴� �߰��� �Ϸ�Ǿ����ϴ�.\n" << endl;
			edge_list->show_all_menu();
			break;
		}
		default:
			break;
	}
}

void del_menu(ToppingList* topping_list, DoughList* dough_list, EdgeList* edge_list)
{
	cout << "�����ϰ��� �ϴ� �޴��� ������ �����ϼ���." << endl;
	cout << "1: ����\n2: ����\n3: ����"<< endl;
	cout << ">> " ;
	int type_del = read_int();
	string name_del;
	if(type_del < 0 || type_del > 3)
	{
		cout <<"[ERROR] 1~3 �� �ϳ��� �Է����� �ʾҽ��ϴ�. " << endl;
		return;
	}

	// type_del �� ���� ���� ����,����,���� �� �ϳ��� �����ؾ� �Ѵ�.
	switch(type_del)
	{
		case 1:
			topping_list->show_all_menu();
			cout << "�����ϰ��� �ϴ� �޴� �̸��� �Է��ϼ���.\n>> " ;
			cin >> name_del;
			if(topping_list->del(name_del))
				cout << "�޴� ������ �Ϸ�Ǿ����ϴ�.\n" << endl;
			else
				cout << "[ERROR] �ش��ϴ� �̸��� ���� ������ �����ϴ�." << endl;
			topping_list->show_all_menu();
			break;
				
		case 2:
			dough_list->show_all_menu();
			cout << "�����ϰ��� �ϴ� �޴� �̸��� �Է��ϼ���.\n>> " ;
			cin >> name_del;
			if(dough_list->del(name_del))
				cout << "�޴� ������ �Ϸ�Ǿ����ϴ�.\n" << endl;
			else
				cout << "[ERROR] �ش��ϴ� �̸��� ���� ���찡 �����ϴ�." << endl;
			dough_list->show_all_menu();
			break;

		case 3:
			edge_list->show_all_menu();
			cout << "\n�����ϰ��� �ϴ� �޴� �̸��� �Է��ϼ���.\n>> " ;
			cin >> name_del;
			if(edge_list->del(name_del))
				cout << "�޴� ������ �Ϸ�Ǿ����ϴ�." << endl;
			else
				cout << "[ERROR] �ش��ϴ� �̸��� ���� ������ �����ϴ�." << endl;
			cout << "\n";
			edge_list->show_all_menu();
			break;
		default:
			cout << "[ERROR] 1~3 �� �ϳ��� �Է����� �ʾҽ��ϴ�. " << endl;
			break;
	}
	cin.ignore();
}

void search_menu(ToppingList* topping_list, DoughList* dough_list, EdgeList* edge_list)
{
	cout << "�˻��ϰ��� �ϴ� �޴��� ������ �����ϼ���." << endl;
	cout << "1: ����\n2: ����\n3: ����"<< endl;
	cout << ">> " ;
	int type_search;
	int standard_search;
	string name_search;
	cin >> type_search;
	if(type_search < 0 || type_search > 3)
	{
		cout <<"[ERROR] 1~3 �� �ϳ��� �Է����� �ʾҽ��ϴ�. " << endl;
		return;
	}

	// type_search�� ���� ���� ����,����,���� �� �ϳ��� �˻��ؾ��Ѵ�.
	switch(type_search)
	{
		case 1:
			cout <<"�˻� ������ �����ϼ���" << endl;
			cout <<"1: ���� �˻�\n2: �������� �˻�\n>> ";
			cin >> standard_search;
			if(standard_search == 1)
			{
				string ingred_name;
				cout <<"��� �̸��� �Է����ּ���.\n>> ";
				cin >> ingred_name;
				topping_list->search_by_ingred(ingred_name);
			}
			else if(standard_search == 2)
			{
				int low, high;
				cout <<"���� ���� �� ������ �Է����ּ���.\n>> ";
				cin >> low;
				cout <<"���� ���� �� ������ �Է����ּ���.\n>> ";
				cin >> high;
				topping_list->search_by_price(low,high);
			}
			else
			{
				cout << "[ERROR] 1~2 �� �ϳ��� �Է����� �ʾҽ��ϴ�." << endl;
			}
			break;
		case 2:
			cout <<"�˻� ������ �����ϼ���" << endl;
			cout <<"1: �β��� �˻�\n>> ";
			cin >> standard_search;
			if(standard_search == 1)
			{
				float low, high;
				cout <<"�β� ���� �� ������ �Է����ּ���.\n>> ";
				cin >> low;
				cout <<"�β� ���� �� ������ �Է����ּ���.\n>> ";
				cin >> high;
				dough_list->search_by_thick(low,high);
			}
			else
			{
				cout << "[ERROR] 1 �ܿ� �ٸ� ������ �������� �ʽ��ϴ�." << endl;
			}
			break;
		case 3:
			cout <<"�˻� ������ �����ϼ���" << endl;
			cout <<"1: ������ �˻�\n>> ";
			cin >> standard_search;
			if(standard_search == 1)
			{
				string mousse_name;
				cout <<"���� �̸��� �Է����ּ���.\n>> ";
				cin >> mousse_name;
				edge_list->search_by_mousse(mousse_name);
			}
			else
			{
				cout << "[ERROR] 1 �ܿ� �ٸ� ������ �������� �ʽ��ϴ�." << endl;
			}
			break;
		default:
			cout << "[ERROR] 1~3 �� �ϳ��� �Է����� �ʾҽ��ϴ�. " << endl;
			break;
	}
	cin.ignore();	
}

/* This function reads string from cin and check whether it is a number from 0 to 9. If it is, return the number. Otherwise, return -1 */
int read_int()
{
	string input;
	getline(cin,input);
	if(input.length() != 1) // If this is not 1, it's wrong.
	{
		cout<< "[ERROR] ���� �ϳ��� �Է��ؾ� �մϴ�." <<endl;
		return -1;
	}

	if(input.at(0) < '0' || input.at(0) > '9')
	{
		cout << "[ERROR] ���ڸ� �Է����� �ʾҽ��ϴ�." << endl;
		return -1;
	}
	return ((int)(input.at(0))-48);
}
int print_options()
{
	cout << "=================" << endl;
	cout << "0: ��� �޴� ����" << endl;
	cout << "1: �ֹ��ϱ�" << endl;
	cout << "2: �޴� �߰�" << endl;
	cout << "3: �޴� ����" << endl;
	cout << "4: �޴� �˻�" << endl;
	cout << "5: �α�޴� ��õ" << endl;
	cout << "6: ���α׷� ����" << endl;
	cout << "7: ���� �޴� ����" << endl;
	cout << "=================" << endl;
	cout << ">> " ;
	int option;
	// read_int �Լ��� �̿��� ����� �Է��� �޴´�.
	option = read_int();
	while(option == -1)
	{
		cout << ">> " ;
		option=read_int();
	}
	while(option < 0 || option > 7)
	{
		cout <<"[ERROR] 0~7 �� �ϳ��� �Է����� �ʾҽ��ϴ�.\n>> ";
		option =read_int();
		while(option== -1)
		{
			cout << ">> ";
			option=read_int();
		}
	}
	return option;
}

/* This function saves the all of toppings,doughs, and edges to save_menu.txt */
void save_file(ToppingList* topping_list, DoughList* dough_list, EdgeList* edge_list)
{
	ofstream outFile;
	outFile.open("save_menu.txt");
	outFile << "-����\r\n";
	outFile.close();	
	topping_list->save_topping();
	
	outFile.open("save_menu.txt", ios::app);
	outFile << "-����\r\n";
	outFile.close();	
	dough_list->save_dough();

	outFile.open("save_menu.txt", ios::app);
	outFile << "-����\r\n";
	outFile.close();	
	edge_list->save_edge();
	cout << "���� �޴��� �����Ͽ����ϴ�." << endl;
}

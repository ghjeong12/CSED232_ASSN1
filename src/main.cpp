#include <iostream>
#include "ToppingList.h"
#include "DoughList.h"
#include "EdgeList.h"
//옜옜 
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
		cout << "[FATAL INPUT ERROR] init_menu에 해당하는 파일이 없습니다." << endl;
		return ;
	}
	string name;
	read_file >> name;
	if(name!="-토핑")
	{
		// 주어진 형식에 따라 -토핑 태그가 있어야한다.
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
		//','로 ingredient 가 구분된 경우 파싱해서 넣어준다.
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
		// 설명의 경우 공백을 입력할 수 있으므로 getline 함수를 이용한다.
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
	// 에지 입력 시작
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
			// 한개 이상의 무스가 존재하여 , 로 구분된 경우 파싱하여 넣어준다.
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
	cout << "원하시는 토핑 이름을 입력하세요." << endl;
	cout << ">> ";
	cin >> order_topping_name;
	if(topping_list->pick(order_topping_name) == 0)
	{
		cout << "[ERROR] 해당하는 토핑 이름을 가진 토핑이 없습니다." << endl;
		cin.ignore();
		return;
	}

	Topping* order_topping = topping_list->pick(order_topping_name);
	pizza_price += order_topping->get_price();
	pizza_name = order_topping->get_name();
	
	dough_list->show_all_menu();
	cout << "\n";
	cout << "원하시는 도우 이름을 입력하세요." << endl;
	cout <<">> ";
	cin >> order_dough_name;
	if(dough_list->pick(order_dough_name) == 0)
	{
		cout << "[ERROR] 해당하는 도우 이름을 가진 도우가 없습니다." << endl;
		cin.ignore();
		return;
	}
	Dough* order_dough = dough_list->pick(order_dough_name);
	pizza_price += order_dough->get_extra_cost();

	edge_list->show_all_menu();
	cout << "\n";
	cout << "원하시는 에지 이름을 입력하세요." << endl;
	cout <<">> ";
	cin >> order_edge_name;
	if(edge_list->pick(order_edge_name)==0)
	{
		cout<<"[ERROR] 해당하는 에지 이름을 가진 에지가 없습니다." << endl;
		cin.ignore();
		return;
	}
	Edge* order_edge = edge_list->pick(order_edge_name);
	// 피자 가격에 추가 비용을 더한다.
	pizza_price += order_edge->get_extra_cost();
	// 피자 이름을 과제 문서에 적힌 형식에 맞게 만든다.
	pizza_name = order_dough->get_name() + " " + order_edge->get_name() + " " + pizza_name;

	cout << "\n주문하신 피자는 \"" << pizza_name << "\" 입니다." << endl;
	cout << "가격은 \"" << pizza_price << "\"원 입니다." << endl;
	// sellcount 를 증가시켜서 나중에 인기 메뉴를 확인할 때 반영되도록 한다.
	order_topping->inc_sellcount();
	order_dough->inc_sellcount();
	order_edge->inc_sellcount();
	cin.ignore();
}

void add_menu(ToppingList* topping_list, DoughList* dough_list, EdgeList* edge_list)
{
	cout << "추가하고자 하는 메뉴의 종류를 선택하세요." << endl;
	cout << "1: 토핑\n2: 도우\n3: 에지"<< endl;
	cout << ">> " ;
	int type_add;
	cin >> type_add;
	switch(type_add)
	{
		case 1:
		{
			Topping* new_topping = new Topping();
			string top_name;
			cout <<"이름\n>> ";
			cin >> top_name;
						
			cout <<"재료\n>> ";
			string top_ingreds;
			cin >> top_ingreds;
			// 하나 이상의 재료를 입력한 경우 ',' 단위로 파싱하여 넣어준다.
			while(top_ingreds.find(',') != -1)
			{
				new_topping->add_ingredient( top_ingreds.substr(0, top_ingreds.find(',')) );
				top_ingreds = top_ingreds.substr(top_ingreds.find(',')+1, top_ingreds.length());
			}
			new_topping->add_ingredient(top_ingreds);
						
			cout <<"가격\n>> ";
			int top_price;
			cin >> top_price;
			if(cin.fail())
			{
				cin.clear();
				cout << "[ERROR] 가격 입력이 잘못되었습니다." << endl;
				cin.ignore(100,'\n');
				return;
			}
		
			cout<<"소개말\n>> ";
			string top_comment;
			cin.ignore();
			getline(cin, top_comment);
		
			new_topping->set_name(top_name);
			new_topping->set_price(top_price);
			new_topping->set_comment(top_comment);
			topping_list->add(new_topping);
			cout <<"메뉴 추가가 완료되었습니다.\n" << endl;

			topping_list->show_all_menu();
			break;	
		}
		case 2:
		{
			string name;
			float thickness;
			int extra_cost;
			string comment;
			cout << "이름\n>> ";
			cin >> name;
			cout << "두께\n>> ";
			if(cin.fail())
			{
				cin.clear();
				cout << "[ERROR] 두께 입력이 잘못되었습니다." << endl;
				cin.ignore(100,'\n');
				return;
			}

			cin >> thickness;
			cout << "추가비용\n>> ";
			cin >> extra_cost;
			if(cin.fail())
			{
				cin.clear();
				cout << "[ERROR] 추가비용 입력이 잘못되었습니다." << endl;
				cin.ignore(100,'\n');
				return;
			}
			cout << "소개말\n>> ";
			cin.ignore();
			getline(cin, comment);
			Dough* dough = new Dough();
			dough->set_name(name);
			dough->set_extra_cost(extra_cost);
			dough->set_thickness(thickness);
			dough->set_comment(comment);
			dough_list->add(dough);
			cout << "메뉴 추가가 완료되었습니다.\n" << endl;

			dough_list->show_all_menu();
			break;
		}
		case 3:
		{
			Edge* new_edge = new Edge();
			string edge_name;
			cout <<"이름\n>> ";
			cin >> edge_name;
			
			string edge_mousse;
			cout <<"무스\n>> ";
			cin >> edge_mousse;
			// 하나 이상의 무스를 입력한 경우 ',' 단위로 파싱하여 넣어준다.
			while(edge_mousse.find(',') != -1)
			{
				new_edge->add_mousse( edge_mousse.substr(0, edge_mousse.find(',')) );
				edge_mousse = edge_mousse.substr(edge_mousse.find(',')+1, edge_mousse.length());
			}
			new_edge->add_mousse(edge_mousse);
						
			cout << "추가비용\n>> ";

			int edge_extra_cost;
			cin >> edge_extra_cost;
			if(cin.fail())
			{
				cin.clear();
				cout << "[ERROR] 추가비용 입력이 잘못되었습니다." << endl;
				cin.ignore(100,'\n');
				return;
			}
	
			//read_file.get();
			cout<<"소개말\n>> ";
			string edge_comment;
			cin.ignore();
			getline(cin, edge_comment, '\n');

			new_edge->set_name(edge_name);
			new_edge->set_extra_cost(edge_extra_cost);
			new_edge->set_comment(edge_comment);
			edge_list->add(new_edge);
			cout <<"메뉴 추가가 완료되었습니다.\n" << endl;
			edge_list->show_all_menu();
			break;
		}
		default:
			break;
	}
}

void del_menu(ToppingList* topping_list, DoughList* dough_list, EdgeList* edge_list)
{
	cout << "삭제하고자 하는 메뉴의 종류를 선택하세요." << endl;
	cout << "1: 토핑\n2: 도우\n3: 에지"<< endl;
	cout << ">> " ;
	int type_del = read_int();
	string name_del;
	if(type_del < 0 || type_del > 3)
	{
		cout <<"[ERROR] 1~3 중 하나를 입력하지 않았습니다. " << endl;
		return;
	}

	// type_del 의 값에 따라 토핑,도우,에지 중 하나를 삭제해야 한다.
	switch(type_del)
	{
		case 1:
			topping_list->show_all_menu();
			cout << "삭제하고자 하는 메뉴 이름을 입력하세요.\n>> " ;
			cin >> name_del;
			if(topping_list->del(name_del))
				cout << "메뉴 삭제가 완료되었습니다.\n" << endl;
			else
				cout << "[ERROR] 해당하는 이름을 가진 토핑이 없습니다." << endl;
			topping_list->show_all_menu();
			break;
				
		case 2:
			dough_list->show_all_menu();
			cout << "삭제하고자 하는 메뉴 이름을 입력하세요.\n>> " ;
			cin >> name_del;
			if(dough_list->del(name_del))
				cout << "메뉴 삭제가 완료되었습니다.\n" << endl;
			else
				cout << "[ERROR] 해당하는 이름을 가진 도우가 없습니다." << endl;
			dough_list->show_all_menu();
			break;

		case 3:
			edge_list->show_all_menu();
			cout << "\n삭제하고자 하는 메뉴 이름을 입력하세요.\n>> " ;
			cin >> name_del;
			if(edge_list->del(name_del))
				cout << "메뉴 삭제가 완료되었습니다." << endl;
			else
				cout << "[ERROR] 해당하는 이름을 가진 에지가 없습니다." << endl;
			cout << "\n";
			edge_list->show_all_menu();
			break;
		default:
			cout << "[ERROR] 1~3 중 하나를 입력하지 않았습니다. " << endl;
			break;
	}
	cin.ignore();
}

void search_menu(ToppingList* topping_list, DoughList* dough_list, EdgeList* edge_list)
{
	cout << "검색하고자 하는 메뉴의 종류를 선택하세요." << endl;
	cout << "1: 토핑\n2: 도우\n3: 에지"<< endl;
	cout << ">> " ;
	int type_search;
	int standard_search;
	string name_search;
	cin >> type_search;
	if(type_search < 0 || type_search > 3)
	{
		cout <<"[ERROR] 1~3 중 하나를 입력하지 않았습니다. " << endl;
		return;
	}

	// type_search의 값에 따라 토핑,도우,에지 중 하나를 검색해야한다.
	switch(type_search)
	{
		case 1:
			cout <<"검색 기준을 선택하세요" << endl;
			cout <<"1: 재료로 검색\n2: 가격으로 검색\n>> ";
			cin >> standard_search;
			if(standard_search == 1)
			{
				string ingred_name;
				cout <<"재료 이름을 입력해주세요.\n>> ";
				cin >> ingred_name;
				topping_list->search_by_ingred(ingred_name);
			}
			else if(standard_search == 2)
			{
				int low, high;
				cout <<"가격 범위 중 하한을 입력해주세요.\n>> ";
				cin >> low;
				cout <<"가격 범위 중 상한을 입력해주세요.\n>> ";
				cin >> high;
				topping_list->search_by_price(low,high);
			}
			else
			{
				cout << "[ERROR] 1~2 중 하나를 입력하지 않았습니다." << endl;
			}
			break;
		case 2:
			cout <<"검색 기준을 선택하세요" << endl;
			cout <<"1: 두께로 검색\n>> ";
			cin >> standard_search;
			if(standard_search == 1)
			{
				float low, high;
				cout <<"두께 범위 중 하한을 입력해주세요.\n>> ";
				cin >> low;
				cout <<"두께 범위 중 상한을 입력해주세요.\n>> ";
				cin >> high;
				dough_list->search_by_thick(low,high);
			}
			else
			{
				cout << "[ERROR] 1 외에 다른 기준은 제공하지 않습니다." << endl;
			}
			break;
		case 3:
			cout <<"검색 기준을 선택하세요" << endl;
			cout <<"1: 무스로 검색\n>> ";
			cin >> standard_search;
			if(standard_search == 1)
			{
				string mousse_name;
				cout <<"무스 이름을 입력해주세요.\n>> ";
				cin >> mousse_name;
				edge_list->search_by_mousse(mousse_name);
			}
			else
			{
				cout << "[ERROR] 1 외에 다른 기준은 제공하지 않습니다." << endl;
			}
			break;
		default:
			cout << "[ERROR] 1~3 중 하나를 입력하지 않았습니다. " << endl;
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
		cout<< "[ERROR] 숫자 하나만 입력해야 합니다." <<endl;
		return -1;
	}

	if(input.at(0) < '0' || input.at(0) > '9')
	{
		cout << "[ERROR] 숫자를 입력하지 않았습니다." << endl;
		return -1;
	}
	return ((int)(input.at(0))-48);
}
int print_options()
{
	cout << "=================" << endl;
	cout << "0: 모든 메뉴 보기" << endl;
	cout << "1: 주문하기" << endl;
	cout << "2: 메뉴 추가" << endl;
	cout << "3: 메뉴 삭제" << endl;
	cout << "4: 메뉴 검색" << endl;
	cout << "5: 인기메뉴 추천" << endl;
	cout << "6: 프로그램 종료" << endl;
	cout << "7: 현재 메뉴 저장" << endl;
	cout << "=================" << endl;
	cout << ">> " ;
	int option;
	// read_int 함수를 이용해 사용자 입력을 받는다.
	option = read_int();
	while(option == -1)
	{
		cout << ">> " ;
		option=read_int();
	}
	while(option < 0 || option > 7)
	{
		cout <<"[ERROR] 0~7 중 하나를 입력하지 않았습니다.\n>> ";
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
	outFile << "-토핑\r\n";
	outFile.close();	
	topping_list->save_topping();
	
	outFile.open("save_menu.txt", ios::app);
	outFile << "-도우\r\n";
	outFile.close();	
	dough_list->save_dough();

	outFile.open("save_menu.txt", ios::app);
	outFile << "-에지\r\n";
	outFile.close();	
	edge_list->save_edge();
	cout << "현재 메뉴를 저장하였습니다." << endl;
}

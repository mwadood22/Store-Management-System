#include<iostream>
#include<windows.h>
#include<fstream>
#include<string>
#include<conio.h>
using namespace std;
//class Stock_Manager{};
//struct report {
//	string name;
//	int quantity;
//	float price;
//};
class Admin{
	int Item_Id, Cost_Price, Sale_Price, Quantity ;
	string Name  , FoodCategory , blank ; char Option;
	int Choice;
public:
	void Admin_Menu();
	void Add_New_Stock();
	bool  Search_Any_Item(int Item_Id);
	void  Genrate_Stock_Report();
	bool Update_Any_Item(int Search_Item, string name, int quantity);
	bool  Remove_Any_Item(int Search_Item);
	bool  Delete_Any_Item(int Search_Item);
	bool Check_Item(int id);
	void  Add_Employee();
	bool  Employee_Update(long id);
	bool  Delete_Employee(long id);
	void Employee_Display();
	//void Add_New_Stock();
	bool search_Item(int id, int& price, string& name, int quantity);
};
class Employee: public Admin{

	string  Employee_Name, CNIC_No, Address, Employee_Type, Contact_No;
	long   Employee_ID, Employee_Password;
	int Salary;
public:
	void Add_New_Employee();
	bool Update_Employee(long id);
	bool Check_Employee(long id, long password);
	bool  Remove_Employee(long id);
	void EmployeeDisplay();
};
class  Cashier: public Employee{
	
	int quantity, id = 0, choice, price, option, discount, i = 0; 
	string name, str;
	bool check;
	double amount = 0.0, receiving_amount = 0.0;
public:
	void Generate_bill();
	void Cashier_Search();
};
void Cashier::Cashier_Search() {

}
void Cashier::Generate_bill()
{
	ifstream  fin;
	ofstream  fout, out;
	do
	{
		cout << "How do you want to search the product(1- By ID, 2- By name): ";
		cin >> choice;
		if (choice == 1)
		{
			cout << "Enter product ID: ";
			cin >> id;
		}
		else if(choice == 2)
		{
			cout << "Enter product name: ";
			cin >> name;
		}
		fout.open("Reciept.txt");
		out.open("Sold_Items.txt", ios::app);
		cout << "Enter quantity of the product: ";
		cin >> quantity;
		check = search_Item(id, price, name, quantity);
		if (check == true)
		{
			Update_Any_Item(id, name, quantity);
			amount += price * quantity; 
			fout << "Item name: " << name << "Item Price: " << price << "Item Quantity: " << quantity << endl;
			out << "Item name: " << name << "Item Price: " << price << "Item Quantity: " << quantity << endl;
			cout << "Item name: " << name << "Item Price: " << price << "Item Quantity: " << quantity << endl;
			i++;
		}
		cout << "Do you want to buy another item(1- Yes, 0- No): ";
		cin >> option;
		name = "";
	} while (option != 0);
	fout.close();
	out.close();
	if (i > 0)
	{
		if (amount > 5000)
		{
			if (amount > 10000)
			{
				if (amount > 20000)
				{
					amount = amount - (amount * 0.15);
				}
				else
					amount = amount - (amount * 0.10);
			}
			else
				amount = amount - (amount * 0.05);
		}		
		cout << "Total discounted amount = " << amount << endl;
		cout << "Enter amount received: ";
		cin >> receiving_amount;
		while (receiving_amount < amount)
		{
			cout << "Your amount is less than total bill" << endl;
			cout << "Enter receiving amount again: ";
			cin >> receiving_amount;
		}
		cout << "Change due: " << receiving_amount - amount << endl;
	}
	fin.open("Reciept.txt");
	while (getline(fin, str))
	{
		cout << str << endl;
	}
	fin.close();
}

bool Admin::search_Item(int id, int &price, string& name, int quantity)
{
	ifstream fin;
	ofstream fout;
	fin.open("Data.txt", ios::in);
	string str; price = 0;
	int temp;
	bool Tell = false, check = false;
	while (fin >> Item_Id >> Name >> Quantity >> Cost_Price >> Sale_Price)
	{
		if (id == Item_Id || name == Name)
		{
			if (quantity < Quantity)
			{
				temp = Quantity - quantity;
				Tell = true;
				break;
			}
			else
			{
				Tell = false;
				check = true;
				cout << "Entered quantity is greater than available quantity" << endl;
			}
			break;
		}
	}
	fin.close();
	if (Tell == true)
	{
		name = Name;
		price = Sale_Price / Quantity;
	}
	if (check == false)
	{
		if (Tell == false)
			{
				system("CLS");
				cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|      Sorry  No   Record  Against  This  Id  Or   Name   Exists          | " << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;

			}
	}
	
	return Tell;
}
//class Stock_Manager {
//	int item_ID, quantity, Average_price, Sales_Price;
//	string name;
//public:
//	friend void Add_New_Stock();
//	bool Check_Item(Admin &a,int id);
//};
void Admin::Employee_Display()
{
	Employee obj;
	obj.EmployeeDisplay();
}
void Employee::EmployeeDisplay()
{
	system("CLS");
	ifstream fin;
	ofstream fout;
	fin.open("EmployeeH.txt", ios::in);
	string str;
	while (getline(fin, str))
	{
		cout << str << endl;
	}
	fin.close();
	fin.open("EmployeeData.txt",ios::in);
	while (getline(fin, str))
	{
		cout << str << endl;
	}
	fin.close();
}
bool Employee::Update_Employee(long id )
{

	ifstream fin;
	ofstream fout;
	fin.open("EmployeeData.txt", ios::in);
	string str; int  Size = 0, count = 0;
	bool Tell = false;
	Employee *Data = new Employee[100];
	while (fin >> Employee_ID >>Employee_Name >> Employee_Type >> Salary >> Contact_No >> CNIC_No >> Address)
	{
		if (Employee_ID == id)
		{
			Data[count].Employee_ID = id;
			cout << "\t" << "\t" << "__________________________________________________________________________ " << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|         Item Id No  : ";  cout << "     " << Data[count].Employee_ID << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Employee Name   : ";    cin >> Data[count].Employee_Name;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Employee Type  : ";    cin >> Data[count].Employee_Type;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Employee Salary : ";     cin >> Data[count].Salary;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Contact No  : ";      cin >> Data[count].Contact_No;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  CNIC No : ";     cin >> Data[count].CNIC_No;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Employee Adress : ";      cin >> Data[count].Address;
			cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
			system("CLS");
			Tell = true;
			count++;
		}
		else
		{

			Data[count].Employee_ID = Employee_ID;
			Data[count].Employee_Name = Employee_Name;
			Data[count].Employee_Type = Employee_Type;
			Data[count].Salary = Salary;
			Data[count].Contact_No = Contact_No;
			Data[count].CNIC_No = CNIC_No;
			Data[count].Address = Address;		
			count++;
		}
	}
	fin.close();
	cout << count << endl;
	fout.open("EmployeeData.txt");
	for (int i = 0; i <count; i++)
	{
		fout << endl;
		fout << "        " << Data[i].Employee_ID << "        " << Data[i].Employee_Name << "               " << Data[i].Employee_Type << "               " << Data[i].Salary << "               " << Data[i].Contact_No << "               " << Data[i].CNIC_No << "               " << Data[i].Address;
	}
	fout.close();
	if (Tell == false)
	{
		system("CLS");
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|             Sorry  No   Record  Against  This  Id  Exists               | " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		
	}
	return Tell;
}
bool Admin:: Employee_Update(long id)
{
	Employee obj;
	if (obj.Update_Employee(id) == 1)
	{
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|          Succcessfuly           Updated        Record                   | " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		return true;
	}
	return false;
}
void  Employee::Add_New_Employee()
{

		ifstream fin;
		ofstream fout;
		cout << "\t" << "\t" << "__________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|       Enter Employee_Id_No  : ";  cin >> Employee_ID;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|       Enter  Password  : ";  cin >> Employee_Password;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		if (Check_Employee(Employee_ID, Employee_Password) == 1)
		{
			system("CLS");
			cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|          Against   This    Id     Already  Record  Exist                |" << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
			Add_New_Employee();
		}
		else
		{
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Employee Name   : ";    cin >> Employee_Name;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Employee Type  : ";    cin >> Employee_Type;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Employee Salary : ";     cin >> Salary;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Contact No  : ";      cin >>Contact_No  ;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  CNIC No : ";     cin >> CNIC_No;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Employee Adress : ";      cin >> Address;
			cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
			system("CLS");
			fout.open("EmployeeData.txt", ios::app);
			fout << endl;
			fout << "        " << Employee_ID << "        " << Employee_Name << "               " << Employee_Type << "               " << Salary << "               " << Contact_No << "               " << CNIC_No << "               " << Address;
			fout.close();
		}
	
}
bool Employee::Check_Employee(long ID, long password)
{
	ifstream fin;
	ofstream fout;
	fin.open("EmployeeData.txt", ios::app);
	bool match = false;
	while (fin >> Employee_ID >>Employee_Name >> Employee_Type >> Salary >> Contact_No >> CNIC_No >> Address)
	{
		//if (Item_Id == id)
		//{
			//match = true;
			//break;
		//}
	}
	fin.close();
	return match;
}
void Admin::Admin_Menu()
{
	int id, quantity = 0;
	string name = "";
	cout << "\t" << "\t" << "__________________________________________________________________________ " << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|                      Admin       ( Control )                            |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (1)            Add New Item InStock                  |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (2)            Update   Stock                        |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (3)            Remove   Stock                        |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (4)            Generate Stock Report                 |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (5)            Search Any Item                       |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (6)            Add New Employee                      |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (7)            Update Employee Information           |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (8)            Remove Any Employee                   |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (9)           Display  Employee   Record             |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (10)            Genrate Sale Report                  |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (11)           Display Highest Selling Item          |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (12)           See  Stock Value Statistics           |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|              Press (0)            For GoTo Main Menu                    |" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
	cout << "\t" << "\t" << "|                                                                         |" << endl;
	cout << "\t" << "\t" << "|           What Is Your Choice : ";  cin >>Option;
	cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
	int Size;
	switch (Option)
	{
		   
	case '0': 
		break;
	case '1': 
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|        How Many Item you Want Enter : "; cin >> Size;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		for (int i = 0; i < Size; i++)
		    Add_New_Stock();
			system("CLS");
			cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|              Press (0)            For GoTo Main Menu                    |" << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|           What Is Your Choice : ";  cin >> Choice;
			cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
			if (Choice == 0)
			{
				system("CLS");
				Admin_Menu();
			}
			
			break;
	case '2':
		        cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		        cout << "\t" << "\t" << "|                                                                         |" << endl;
		        cout << "\t" << "\t" << "|      Enter Id Number For ( Update ) Stock : ";  cin >> Item_Id;
		        cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		        Update_Any_Item( Item_Id,name, quantity);
				system("CLS");
				cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|              Press (0)            For GoTo Main Menu                    |" << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|           What Is Your Choice : ";  cin >> Choice;
				cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
				if (Choice == 0)
				{
					system("CLS");
					Admin_Menu();
				}
		break;
	case '3':
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|      Enter Id Number For ( Delete ) Stock : ";  cin >> Item_Id;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		Delete_Any_Item(Item_Id);
		system("CLS");
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|              Press (0)            For GoTo Main Menu                    |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|           What Is Your Choice : ";  cin >> Choice;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		if (Choice == 0)
		{
			system("CLS");
			Admin_Menu();
		}
		break;
	case '4':
		         
		        Genrate_Stock_Report();
		         cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		         cout << "\t" << "\t" << "|                                                                         |" << endl;
				 cout << "\t" << "\t" << "|                                                                         |" << endl;
		         cout << "\t" << "\t" << "|              Press (0)            For GoTo Main Menu                    |" << endl;
		         cout << "\t" << "\t" << "|                                                                         |" << endl;
		         cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		         cout << "\t" << "\t" << "|                                                                         |" << endl;
		         cout << "\t" << "\t" << "|           What Is Your Choice : ";  cin >> Choice;
		         cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		if (Choice == 0)
		    {
			   system("CLS");
			   Admin_Menu();
		     }
		break;
	case '5' :
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|      Enter Id Number For ( Search ) Stock : ";  cin >> Item_Id;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		Search_Any_Item(Item_Id);
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|              Press (0)            For GoTo Main Menu                    |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|           What Is Your Choice : ";  cin >> Choice;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		if (Choice == 0)
		{
			system("CLS");
			Admin_Menu();
		}
		break;
	case '6':
		        Add_Employee();
				cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|              Press (0)            For GoTo Main Menu                    |" << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|           What Is Your Choice : ";  cin >> Choice;
				cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
				if (Choice == 0)
				{
					system("CLS");
					Admin_Menu();
				}
				break;
	case  '7': 
		           cout << "\t" << "\t" << "__________________________________________________________________________ " << endl;
		           cout << "\t" << "\t" << "|                                                                         |" << endl;
		           cout << "\t" << "\t" << "|                                                                         |" << endl;
		           cout << "\t" << "\t" << "|       Enter Employee_Id_No ( Update ) : ";  cin >> id;
		           cout << "\t" << "\t" << "|                                                                         |" << endl;
		           cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
				   Employee_Update(id);
				   cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
				   cout << "\t" << "\t" << "|                                                                         |" << endl;
				   cout << "\t" << "\t" << "|              Press (0)            For GoTo Main Menu                    |" << endl;
				   cout << "\t" << "\t" << "|                                                                         |" << endl;
				   cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
				   cout << "\t" << "\t" << "|                                                                         |" << endl;
				   cout << "\t" << "\t" << "|           What Is Your Choice : ";  cin >> Choice;
				   cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
				   if (Choice == 0)
				   {
					   system("CLS");
					   Admin_Menu();
				   }
				   break;
	case  '8' :
		
		cout << "\t" << "\t" << "__________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|       Enter Employee_Id_No (Delete)  : ";  cin >> id;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		Delete_Employee(id);
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|              Press (0)            For GoTo Main Menu                    |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|           What Is Your Choice : ";  cin >> Choice;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		if (Choice == 0)
		{
			system("CLS");
			Admin_Menu();
		}
		break;
	case '9' :
		            Employee_Display();
					cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
					cout << "\t" << "\t" << "|                                                                         |" << endl;
					cout << "\t" << "\t" << "|              Press (0)            For GoTo Main Menu                    |" << endl;
					cout << "\t" << "\t" << "|                                                                         |" << endl;
					cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
					cout << "\t" << "\t" << "|                                                                         |" << endl;
					cout << "\t" << "\t" << "|           What Is Your Choice : ";  cin >> Choice;
					cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
					if (Choice == 0)
					{
						system("CLS");
						Admin_Menu();
					}
					break;
	default : cout << " Invalid Input " << endl;
		break;
	}

}
void  Admin::Add_New_Stock()
{
	ifstream fin;
	ofstream fout;
	int Item_no;
		cout << "\t" << "\t" << "__________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|       Enter  Item Id No  : ";  cin >> Item_no; 
		if (Check_Item(Item_no) ==1 )
		{
			system("CLS");
			cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|          Against   This    Id     Already  Record  Exist                |" << endl;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
			Add_New_Stock();
		}
		else
		{
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Item Name(10)  : ";    cin >> Name;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Item Quantity  : ";    cin >> Quantity;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Cost Price : ";     cin >> Cost_Price;
			cout << "\t" << "\t" << "|                                                                         |" << endl;
			cout << "\t" << "\t" << "|       Enter  Sale Price : ";      cin >> Sale_Price;
			cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
			system("CLS");
			fout.open("Data.txt", ios::app);
			fout << "        " << Item_no << "               " << Name << "               " << Quantity << "               " << Cost_Price << "               " << Sale_Price ;
			fout.close();
		}	
}
bool Admin :: Check_Item(int id)
{
	ifstream fin;
	ofstream fout;
	fin.open("Data.txt", ios::app);
	bool match = false;
	while (fin >>  Item_Id >> Name >> Quantity >> Cost_Price >> Sale_Price)
	{
		if (Item_Id == id)
		{
			match = true;
			break;
		}			
	}	
	fin.close( );
	return match;

}
bool Admin::Search_Any_Item(int Search_Item)
{
	ifstream fin;
	ofstream fout;
	fin.open("Data.txt", ios::in);
	string str; int count = 0;
	bool Tell = false;
	while (fin >> Item_Id >> Name >> Quantity >> Cost_Price >> Sale_Price)
	{
		if (Search_Item == Item_Id)
		{
			Tell = true;
			break;
		}
	}
	fin.close();
	if (Tell == true)
	{
		system("CLS");
		fin.open("Heading.txt", ios::in);
		while (getline(fin, str))
		{
			cout << str << endl;
		}
		fin.close();
		cout << endl << endl;
		cout << "        " << Item_Id << "               " << Name << "               " << Quantity << "               " << Cost_Price << "               " << Sale_Price << endl;
		cout << endl << endl;
	}
	else
	{
		system("CLS");
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|        Sorry   No    Such   Id   No   Record   Is   Exist               | " <<endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
	}
	return Tell;
}
bool Admin::Update_Any_Item(int Search_Item,string name, int quantity)
{
	ifstream fin;
	ofstream fout;
	fin.open("Data.txt", ios::in);
	string str; int  Size=0 , count=0;
	bool Tell = false;
	Admin *Data = new Admin[100];
	while (fin >> Item_Id >> Name >> Quantity >> Cost_Price >> Sale_Price)
	{
		if (Search_Item == Item_Id)
		{
			if (quantity > 0)
			{
				Data[count].Item_Id = Search_Item;
				Data[count].Name = Name;
				Data[count].Quantity = Quantity - quantity;
				Data[count].Cost_Price = Cost_Price;
				Data[count].Sale_Price = Sale_Price;
				count++;
			}
			else
			{
				Data[count].Item_Id = Search_Item;
				cout << "\t" << "\t" << "__________________________________________________________________________ " << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|         Item Id No  : ";  cout << "     " << Data[count].Item_Id << endl;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|       Enter  Item Name(10)  : ";    cin >> Data[count].Name;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|       Enter  Item Quantity  : ";    cin >> Data[count].Quantity;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|       Enter  Cost Price : ";     cin >> Data[count].Cost_Price;
				cout << "\t" << "\t" << "|                                                                         |" << endl;
				cout << "\t" << "\t" << "|       Enter  Sale Price : ";      cin >> Data[count].Sale_Price;
				cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
				Tell = true;
				count++;
			}
		}
		else
		{
			Data[count].Item_Id = Item_Id;
			Data[count].Name = Name;
			Data[count].Quantity = Quantity;
			Data[count].Cost_Price = Cost_Price;
			Data[count].Sale_Price = Sale_Price;
			count++;
		}
	}
	fin.close();
	cout << count << endl;
	fout.open("Data.txt");
		for (int i = 0; i <count; i++)
		{
			fout << endl;
			fout << "        " << Data[i].Item_Id<< "               " << Data[i].Name << "               " << Data[i].Quantity << "               " << Data[i].Cost_Price << "               " << Data[i].Sale_Price << endl;
	    }
		fout.close();		
		if (Tell=false)
	   {
		system("CLS");
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|        Sorry   No    Such   Id   No   Record   Is   Exist               | " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
	}
		return Tell;
}
bool Admin::Delete_Employee(long id)
{
	Employee obj;
	if (obj.Remove_Employee(id) == 1)
	{
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|          Successfully      Record      Is       Deleted                 | " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
		return true;
	}
	else
		return false;
}
bool  Employee::Remove_Employee(long id)
{
	ifstream fin;
	ofstream fout;
	fout.open("CopyData.txt");
	fin.open("EmployeeData.txt", ios::in);
	bool Tell = false;
	while (fin>>Employee_ID >> Employee_Name >> Employee_Type >> Salary >> Contact_No >> CNIC_No >> Address)
	{
		if (Employee_ID != id)
		{

			fout << endl;
			fout << "        " << Employee_ID << "        " << Employee_Name << "               " << Employee_Type << "               " << Salary << "               " << Contact_No << "               " << CNIC_No << "               " << Address;
		}
		else
			Tell = true;
	}
	fin.close();
	fout.close();
	string str;
	fout.open("EmployeeData.txt");
	fin.open("Copydata.txt");
	while (getline(fin, str))
	{
		fout << str << endl;
	}
	fout.close();
	fin.close();
	if (Tell == false)
	{
		system("CLS");
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|        Sorry   No    Such   Id   No   Record   Is   Exist               | " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
	}
	return Tell;
}
bool Admin::Delete_Any_Item(int Search_Item)
{
	ifstream fin;
	ofstream fout;
	fout.open("CopyData.txt");
	fin.open("Data.txt",ios::app);
	bool Tell = false;
	while (fin >> Item_Id >> Name >> Quantity >> Cost_Price >> Sale_Price)
	{
		if (Search_Item != Item_Id)
		{
			fout << endl;
			fout << "        " << Item_Id << "               " << Name << "               " << Quantity << "               " << Cost_Price << "               " << Sale_Price << endl;
		}
		else
			Tell = true;
	}
	fin.close();
	fout.close();
	string str;
	fout.open("Data.txt");
	fin.open("Copydata.txt");
	while (getline(fin , str))
	{
	    fout<< str << endl;
	}
	fout.close();
	fin.close();
	if (Tell == false)
	{
		system("CLS");
		cout << "\t" << "\t" << " _________________________________________________________________________ " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|        Sorry   No    Such   Id   No   Record   Is   Exist               | " << endl;
		cout << "\t" << "\t" << "|                                                                         |" << endl;
		cout << "\t" << "\t" << "|_________________________________________________________________________|" << endl;
	}
	return Tell;
}

void  Admin::Genrate_Stock_Report()
{
	ifstream fin;
	ofstream fout;
	string str;
	system("CLS");
	fin.open("Heading.txt", ios::in);
	while (getline(fin, str))
	{
		cout << str << endl;
	}
	fin.close();
	fin.open("Data.txt", ios::in);
	while (getline(fin, str))
	{
		cout <<  str << endl ;
	}
	fin.close();
	cout << endl << endl;
}
void Admin::Add_Employee()
{
	Employee obj;
	obj.Add_New_Employee();
}
int main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	Admin Obj;
	Employee Obj1;
	Cashier c;
	c.Generate_bill();
	Obj.Admin_Menu();
	system("pause");
}
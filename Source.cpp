#include<iostream>
#include<vector>
using namespace std;

enum class Status { no_status, processed, paid, is_formed, shipped, delivered };
class Users
{
	string Name;
	string surName;
	int age;
	string telephoneNumber;
public:

	Users(string Name, string surName, int age, string telephoneNumber)
	{
		this->Name = Name;
		this->surName = surName;
		this->age = age;
		this->telephoneNumber = telephoneNumber;
	}
	Users() : Name("Default Name"), surName("Default surName"), age(18), telephoneNumber("+380689999999") {}
	~Users() {}
	void infoUser()
	{
		cout << "���: " << Name << "\n"
			<< "�������: " << surName << "\n"
			<< "�������: " << age << "\n"
			<< "�������: +380" << telephoneNumber << "\n\n";
	}
};
class Product
{
protected:
	string name;
	string description;
	float price;
	int quantity;
public:
	Product(string name, string description, float price, int quantity)
	{
		this->name = name;
		this->description = description;
		this->price = price;
		this->quantity = quantity;
	}
	string getName()
	{
		return name;
	}
	string getDescription()
	{
		return description;
	}
	float getPrice()
	{
		return price;
	}
	int getQuantity()
	{
		return quantity;
	}
	~Product() {}
	virtual void infoProduct()
	{
		cout << "��������: " << name << "\n"
			<< "��������: " << description << "\n"
			<< "���� ���: " << price << "\n";

		if (quantity < 1)
		{
			cout << "������������ " << name << " �� ������ ��� ������.\n";
		}
		else
		{
			cout << "������� �� ������: " << quantity << "\n";
		}
	}
};
class BasketShop : public Product
{
	vector<Product> products;
	Users* user;
	Status orderStatus = Status::no_status;
	float totalCost = 0.0;
	bool pay = false;
	bool stat = false;
	string Adress;

public:
	BasketShop(Users* user, string name, string description, float price, int quantity)
		: Product(name, description, price, quantity)
	{
		this->user = user;
	}

	~BasketShop() {}

	void addProduct(const Product& product)
	{
		products.push_back(product);
	}

	void infoProduct() override
	{
		Product::infoProduct();
	}
	float getTotalCost()
	{
		return totalCost;
	}
	void infoDisplay()
	{
		if (products.empty())
		{
			cout << "� ��� ���� ��� ������� � �������\n";
			return;
		}
		cout << "���� �������:\n";
		totalCost = 0;
		for (int i = 0; i < products.size(); i++)
		{
			products[i].infoProduct();
			totalCost += products[i].getPrice();
			cout << "\n";
		}
		cout << "������� � ������� �� ����� - " << getTotalCost() << " ���.\n";
	}
	Status getStatus()
	{
		return orderStatus;
	}

	void setStatus(Status newStatus)
	{
		orderStatus = newStatus;
	}
	void orStatus()
	{
		cout << "������ ������: ";
		if (getStatus() == Status::processed)
			cout << "��������.\n";
		else if (getStatus() == Status::paid)
			cout << "�������.\n";
		else if (getStatus() == Status::is_formed)
			cout << "�����������.\n";
		else if (getStatus() == Status::shipped)
			cout << "���������.\n";
		else if (getStatus() == Status::delivered)
			cout << "���������.\n";
		else if (getStatus() == Status::no_status)
			cout << "� ������ ���� ��� �������.\n";
	}
	void checkout()
	{
		stat = true;
		totalCost = 0;
		if (products.empty())
		{
			cout << "���� ������� �����. �������� ������ ����� ����������� ������.\n";
			return;
		}
		for (int i = 0; i < products.size(); i++)
		{
			if (products[i].getQuantity() > 0)
			{
				cout << "�������� �����: " << products[i].getName() << "\n";
				totalCost += products[i].getPrice();
			}
			else
			{
				cout << "\n����� " << products[i].getName() << " ����������� �� ������.\n\n";
			}
		}
		cout << "����� ������ - " << totalCost << " ���.\n\n";
		orderStatus = Status::processed;
		cout << "������ ������: ";
		if (getStatus() == Status::processed)
			cout << "��������\n";
		else if (getStatus() == Status::paid)
			cout << "�������\n";
		else if (getStatus() == Status::is_formed)
			cout << "�����������\n";
		else if (getStatus() == Status::shipped)
			cout << "���������\n";
		else if (getStatus() == Status::delivered)
			cout << "���������\n";
	}
	void payment()
	{
		if (products.empty())
		{
			cout << "���� ������� �����. �������� ������ ����� ������� ������.\n";
			return;
		}
		if (stat == false)
		{
			cout << "����� ������� ���������� �������� ����� (4 � ���� ������).\n";
			return;
		}
		else
		{
			int a;
			cout << "�������� ��������: \n";
			cout << "1 - �������� �����\n" << "2 - ���������� �������������� ������\n";
			cin >> a;
			switch (a)
			{
			case(1):
				cout << "����� �� ����� - " << getTotalCost() << " �������\n";
				pay = true;
				orderStatus = Status::paid;
				break;
			case(2):
				cout << "���������� �������������� ������\n";
				break;
			default:
				cout << "����� �������\n";
				break;
			}
			if (pay)
			{
				int b;
				cout << "�������� ��������: \n";
				cout << "1 - �������� �������� (+100 ���. � ��������� ������)\n" << "2 - ���������\n";
				cin >> b;
				switch (b)
				{
				case(1):
					totalCost += 100;
					cout << "������� ����� ��������: \n\n";
					cin >> Adress;
					cout << "� ������� ���� ����� ��� ����� ����� ����������� � ��������, " <<
						"������ �������� � ����.\n" << "����� � ������ - " << totalCost << " ���\n";
					orderStatus = Status::is_formed;
					break;
				case(2):
					cout << "� ������� ���� ����� ������ ������� ����� �� ������ ������ �������."
						<< "����� � ������ - " << totalCost << " ���\n";
					orderStatus = Status::is_formed;
					break;
				default:
					cout << "�������� ��������\n";
					break;
				}
			}
		}
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	string a;
	string b;
	int c;
	string q;
	Product product1("����� ���������", "����������� �������", 165, 122);
	Product product2("������ ������", "����������� �������", 365, 0);
	Product product3("���� ���������", "����������� �������", 125, 25);
	Product product4("Pepsi", "�������������� �������", 46, 250);
	cout << "���������� ������ �����������.\n\n";
	cout << "������� ���� ������: \n";
	cout << "���\n";
	cin >> a;
	cout << "�������\n";
	cin >> b;
	do
	{
		cout << "�������\n";
		if (!(cin >> c))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cerr << "������: ������� ���������� �������.\n";
		}
		else if (c < 1 || c > 100)
		{
			cerr << "������: ������� ���������� ������� � ��������� 1-100.\n";
		}

	} while (c < 1 || c > 150);
	cout << "����� �������� +380-";
	cin >> q;
	Users user1(a, b, c, q);
	BasketShop one(&user1, "������� ������������ ", "�������� �������", 0, 0);
	int choice = -1;
	int choice1 = -1;
	do {
		try
		{
			cout << "\n�������� ��������:\n"
				<< "1 - �������� ������ ������������\n"
				<< "2 - �������� ����� � �������\n"
				<< "3 - ����������� �������\n"
				<< "4 - �������� �����\n"
				<< "5 - �������� �����\n"
				<< "6 - ����������� ������ ������\n"
				<< "0 - �����\n";
			while (!(cin >> choice))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cerr << "������: ������������ ����. ���������� �����." << "\n";
			}
			switch (choice)
			{
			case 1:
				cout << a << "\n";
				cout << b << "\n";
				cout << c << "\n";
				cout << "+380-" << q << "\n";
				break;
			case 2:
				cout << "������ ��������� � ������:\n\n";
				if (product1.getQuantity() > 0)
				{
					cout << "\n\t\t����� - 1\n";
					product1.infoProduct();
				}

				if (product2.getQuantity() > 0)
				{
					cout << "\n\t\t����� - 2\n";
					product2.infoProduct();
				}

				if (product3.getQuantity() > 0)
				{
					cout << "\n\t\t����� - 3\n";
					product3.infoProduct();
				}

				if (product4.getQuantity() > 0)
				{
					cout << "\n\t\t����� - 4\n";
					product4.infoProduct();
				}
				cout << "�������� ����� �� ������, ����� �������� � �������.\n\n";
				while (cin >> choice1 && choice1 != 99)
				{
					switch (choice1)
					{
					case 1:
						if (product1.getQuantity() > 0)
							one.addProduct(product1);
						break;
					case 2:
						if (product2.getQuantity() > 0)
							one.addProduct(product2);
						break;
					case 3:
						if (product3.getQuantity() > 0)
							one.addProduct(product3);
						break;
					case 4:
						if (product4.getQuantity() > 0)
							one.addProduct(product4);
						break;
					default:
						cout << "������������ �����. ���������� �����.\n";
						break;
					}

					cout << "�������� ��������� ����� (������� ����� ������, 99 ��� ����������): ";
				}

				break;
			case 3:
				one.infoDisplay();
				break;
			case 4:
				one.checkout();
				break;
			case 5:
				one.payment();
				break;
			case 6:
				one.orStatus();
				break;
			case 0:
				cout << "���������� ������\n";
				break;
			default:
				cout << "������������ �����\n";
				break;
			}
		}
		catch (const exception& e)
		{
			cerr << "������: " << e.what() << "\n";
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (choice != 0);
	return 0;
}
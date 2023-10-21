#include<iostream>
#include<vector>
using namespace std;




















































































































































































































































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
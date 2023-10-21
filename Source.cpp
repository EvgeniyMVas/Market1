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
	Product product1("Водка Столичная", "Алкогольный напиток", 165, 122);
	Product product2("Коньяк АРАРАТ", "Алкогольный напиток", 365, 0);
	Product product3("Вино Франческа", "Алкогольный напиток", 125, 25);
	Product product4("Pepsi", "Безалкогольный напиток", 46, 250);
	cout << "Необходимо пройти регистрацию.\n\n";
	cout << "Введите Ваши данные: \n";
	cout << "Имя\n";
	cin >> a;
	cout << "Фамилия\n";
	cin >> b;
	do
	{
		cout << "Возраст\n";
		if (!(cin >> c))
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cerr << "Ошибка: Введите корректный возраст.\n";
		}
		else if (c < 1 || c > 100)
		{
			cerr << "Ошибка: Введите корректный возраст в диапазоне 1-100.\n";
		}

	} while (c < 1 || c > 150);
	cout << "Номер телефона +380-";
	cin >> q;
	Users user1(a, b, c, q);
	BasketShop one(&user1, "Корзина пользователя ", "Описание корзины", 0, 0);
	int choice = -1;
	int choice1 = -1;
	do {
		try
		{
			cout << "\nВыберите операцию:\n"
				<< "1 - Показать данные пользователя\n"
				<< "2 - Добавить товар в корзину\n"
				<< "3 - Просмотреть корзину\n"
				<< "4 - Оформить заказ\n"
				<< "5 - Оплатить заказ\n"
				<< "6 - Просмотреть статус заказа\n"
				<< "0 - Выход\n";
			while (!(cin >> choice))
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cerr << "Ошибка: Некорректный ввод. Попробуйте снова." << "\n";
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
				cout << "Товары доступные к заказу:\n\n";
				if (product1.getQuantity() > 0)
				{
					cout << "\n\t\tТовар - 1\n";
					product1.infoProduct();
				}

				if (product2.getQuantity() > 0)
				{
					cout << "\n\t\tТовар - 2\n";
					product2.infoProduct();
				}

				if (product3.getQuantity() > 0)
				{
					cout << "\n\t\tТовар - 3\n";
					product3.infoProduct();
				}

				if (product4.getQuantity() > 0)
				{
					cout << "\n\t\tТовар - 4\n";
					product4.infoProduct();
				}
				cout << "Выберите товар по номеру, чтобы добавить в корзину.\n\n";
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
						cout << "Некорректный выбор. Попробуйте снова.\n";
						break;
					}

					cout << "Выберите следующий товар (введите номер товара, 99 для завершения): ";
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
				cout << "Завершение работы\n";
				break;
			default:
				cout << "Некорректный выбор\n";
				break;
			}
		}
		catch (const exception& e)
		{
			cerr << "Ошибка: " << e.what() << "\n";
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (choice != 0);
	return 0;
}
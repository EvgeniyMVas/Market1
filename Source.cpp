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
		cout << "Имя: " << Name << "\n"
			<< "Фамилия: " << surName << "\n"
			<< "Возраст: " << age << "\n"
			<< "Телефон: +380" << telephoneNumber << "\n\n";
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
		cout << "Название: " << name << "\n"
			<< "Описание: " << description << "\n"
			<< "Цена грн: " << price << "\n";

		if (quantity < 1)
		{
			cout << "Недостаточно " << name << " на складе для заказа.\n";
		}
		else
		{
			cout << "Остаток на складе: " << quantity << "\n";
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
			cout << "У Вас пока нет товаров в корзине\n";
			return;
		}
		cout << "Ваши покупки:\n";
		totalCost = 0;
		for (int i = 0; i < products.size(); i++)
		{
			products[i].infoProduct();
			totalCost += products[i].getPrice();
			cout << "\n";
		}
		cout << "Товаров в корзине на сумму - " << getTotalCost() << " грн.\n";
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
		cout << "Статус заказа: ";
		if (getStatus() == Status::processed)
			cout << "Оформлен.\n";
		else if (getStatus() == Status::paid)
			cout << "Оплачен.\n";
		else if (getStatus() == Status::is_formed)
			cout << "Формируется.\n";
		else if (getStatus() == Status::shipped)
			cout << "Отправлен.\n";
		else if (getStatus() == Status::delivered)
			cout << "Доставлен.\n";
		else if (getStatus() == Status::no_status)
			cout << "У заказа пока нет статуса.\n";
	}
	void checkout()
	{
		stat = true;
		totalCost = 0;
		if (products.empty())
		{
			cout << "Ваша корзина пуста. Добавьте товары перед оформлением заказа.\n";
			return;
		}
		for (int i = 0; i < products.size(); i++)
		{
			if (products[i].getQuantity() > 0)
			{
				cout << "Оформлен заказ: " << products[i].getName() << "\n";
				totalCost += products[i].getPrice();
			}
			else
			{
				cout << "\nТовар " << products[i].getName() << " отсутствует на складе.\n\n";
			}
		}
		cout << "Сумма заказа - " << totalCost << " грн.\n\n";
		orderStatus = Status::processed;
		cout << "Статус заказа: ";
		if (getStatus() == Status::processed)
			cout << "Оформлен\n";
		else if (getStatus() == Status::paid)
			cout << "Оплачен\n";
		else if (getStatus() == Status::is_formed)
			cout << "Формируется\n";
		else if (getStatus() == Status::shipped)
			cout << "Отправлен\n";
		else if (getStatus() == Status::delivered)
			cout << "Доставлен\n";
	}
	void payment()
	{
		if (products.empty())
		{
			cout << "Ваша корзина пуста. Добавьте товары перед оплатой заказа.\n";
			return;
		}
		if (stat == false)
		{
			cout << "Перед оплатой необходимо оформить заказ (4 в меню выбора).\n";
			return;
		}
		else
		{
			int a;
			cout << "Выберите операцию: \n";
			cout << "1 - Оплатить заказ\n" << "2 - Продолжить редактирование заказа\n";
			cin >> a;
			switch (a)
			{
			case(1):
				cout << "Заказ на сумму - " << getTotalCost() << " оплачен\n";
				pay = true;
				orderStatus = Status::paid;
				break;
			case(2):
				cout << "Продолжить редактирование заказа\n";
				break;
			default:
				cout << "Заказ отменен\n";
				break;
			}
			if (pay)
			{
				int b;
				cout << "Выберите операцию: \n";
				cout << "1 - Оформить доставку (+100 грн. к стоимости заказа)\n" << "2 - Самовывоз\n";
				cin >> b;
				switch (b)
				{
				case(1):
					totalCost += 100;
					cout << "Введите адрес доставки: \n\n";
					cin >> Adress;
					cout << "В течении двух часов Ваш заказ будет сформирован и отпрален, " <<
						"курьер свяжется с Вами.\n" << "Сумма к оплате - " << totalCost << " грн\n";
					orderStatus = Status::is_formed;
					break;
				case(2):
					cout << "В течении двух часов можете забрать заказ на пункте выдачи заказов."
						<< "Сумма к оплате - " << totalCost << " грн\n";
					orderStatus = Status::is_formed;
					break;
				default:
					cout << "Доставка отменена\n";
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
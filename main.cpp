#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

struct Product
{
	string name = " ";
	int price = 0;
	int amount = 0;
};

string getInput(vector <string> possible_input, string prompt)
{
	string input;
	bool status = false;
	while (!status)
	{
		cout << prompt << endl;
		getline(cin, input);
		for (size_t i = 0; i < possible_input.size(); i++)
		{
			if (input == possible_input[i])
			{
				status = true;
				break;
			}
		}
		if (!status)
		{
			cout << "Podano zla nazwe"<<endl;
		}
	}
	return input;
}

#define PRODUCT_COUNT 11

class ProductMagazine
{
private:
	Product m_database[PRODUCT_COUNT] =
	{
		{"Woda",200,10},
		{"Sok pomaranczowy",300,8},
		{"Sok jablkowy", 300,7},
		{"Sok pomidorowy",250,1},
		{"Paluszki",250,5},
		{"M&M", 250,8},
		{"Princessa",200,10},
		{"Snickers",250,9},
		{"Mars",200,8},
		{"4move",350,5},
		{"7days",250,8},
	};

public:
	vector<Product> getProductList(void)
	{
		vector<Product> product_list;
		for (size_t i = 0; i < PRODUCT_COUNT; i++)
		{
			product_list.push_back(m_database[i]);
		}
		return product_list;
	}

	vector<string> getProductNames(void)
	{
		vector <string> product_names;
		for (size_t i = 0; i < PRODUCT_COUNT; i++)
		{
			product_names.push_back(m_database[i].name);
		}
		return product_names;
	}

	Product getProductByName(string name)
	{
		for (size_t i = 0; i < PRODUCT_COUNT; i++)
		{
			if (m_database[i].name == name)
			{
				return m_database[i];
			}
		}
		return { "",0,0 };
	}

	void removeProduct(string thing)
	{
		for (size_t i = 0; i < PRODUCT_COUNT; i++)
		{
			if (thing == m_database[i].name)
			{
				m_database[i].amount = m_database[i].amount - 1;
			}
		}
	}
};

class MoneyMagazine
{
private:
	map<int, int> coins = { {10, 90}, {20, 70}, {50, 60}, {100, 40}, {200, 60}, {500, 30}, {1000,10}, {2000,10}, {5000,10}, {10000,10}, {20000,10} };

public:
	void giveChange(int change_total)
	{
		cout << "Twoja reszta to: ";
		for (auto iter = coins.rbegin(); iter != coins.rend(); ++iter) {
			while ((iter->first <= change_total) && (iter->second > 0)) {
				change_total -= iter->first;
				coins[iter->first]--;
				cout << iter->first << "gr. ";
			}
		}
		if (change_total != 0)
		{
			cout << "Brak monet na ca³kowite wydanie reszty" << endl;
		}
		cout << endl;
	}
	
	void giveCoins(vector<int> coins_vector)
	{
		for (size_t i = 0; i < coins_vector.size(); i++)
		{
			coins[coins_vector[i]] ++;
		}
	}
};

class VendingMachine
{
private:
	ProductMagazine m_product_magazine;
	MoneyMagazine m_money_magazine;

public:
	int countChars(void)
	{
		vector<Product> product_list = m_product_magazine.getProductList();
		int count = 0;
		for (size_t i = 0; i < product_list.size(); i++)
		{
			if (count < product_list[i].name.size())
			{
				count = product_list[i].name.size();
			}
		}
		return count;
	}

	string generateSpaceVector(int number)
	{
		string empty_sign = " ";
		for (size_t i = 0; i < number; i++)
		{
			empty_sign += " ";
		}
		return empty_sign;
	}

#define PRICE_LENGTH 3

	void printProductList(void)
	{
		vector<Product> product_list = m_product_magazine.getProductList();
		string column_1 = "Nazwa Produktu:";
		string column_2 = "Cena[gr]:";
		string column_3 = "Ilosc:";
		cout << column_1 << generateSpaceVector(countChars() - column_1.length())
		     << column_2 << " " << column_3 << endl;
		for (size_t i = 0; i < product_list.size(); i++)
		{
			int count = countChars() - product_list[i].name.size();
			cout  << product_list[i].name  << generateSpaceVector(count) << product_list[i].price 
			<< generateSpaceVector(column_2.length()- PRICE_LENGTH) <<  product_list[i].amount << endl;
		}
	}

	vector <string> getProductNames(void)
	{
		return m_product_magazine.getProductNames();
	}


	bool checkIfAvaliable(string product_name)
	{
		vector<Product> product_list = m_product_magazine.getProductList();
		for (size_t i = 0; i < product_list.size(); i++)
		{
			if (product_name == product_list[i].name)
			{
				if (product_list[i].amount == 0)
				{
					cout << "Brak wybranego produktu" << endl;
					return false;
				}
			}
		}
		return true;
	}

	void payment(string product_name)
	{
	Payment:
		string choice = getInput({ "Gotowka","Karta" }, "Jesli chcesz wybrac platnosc gotowka wpisz Gotowka, jesli chcesz wybrac platnosc karta wybierz Karta");
		Product product = m_product_magazine.getProductByName(product_name);
		cout << "Cena produktu to: " << product.price << "gr. " << endl << "Dokonaj platnosci"<< endl;
		if (choice == "Gotowka")
		{
			vector<int> coins_vector;
			while (product.price > 0)
			{
				string output = getInput({ "10","20","50","100","200","500","1000","2000","5000","10000","20000","Anuluj" }, "");
				if (output == "Anuluj")
				{
					cout << "Anulowano zamowienie" << endl;
					cout << "Zwrot pieniedzy: ";
					for (int i = 0; i < coins_vector.size(); i++)
					{
						cout << coins_vector[i] << "gr. " ;
						cout << endl;
					}
					return;
				}
				int coin;
				coin = strtoull(output.c_str(), 0, 10);
				coins_vector.push_back(coin);
				product.price -= coin;
				if (product.price > 0)
				{
					cout << "Musisz doplacic: " << product.price << "gr.";
				}
			}
			m_money_magazine.giveCoins(coins_vector);
			if (product.price != 0)
			{
				m_money_magazine.giveChange(-product.price);
			}
			cout << "Dziekujemy za zakup towaru" << endl;
			m_product_magazine.removeProduct(product.name);
		}
		if (choice == "Karta")
		{
			string verification = getInput({ "OK" }, "Przyloz karte do czytnika i potwierdz wpisaniem OK");
			srand(time(NULL));
			int number = rand() % 1000;
			if (number == 7)
			{
				cout << "Transakcja odrzucona" << endl;
				goto Payment;
			}
			else
			{
				cout << "Dziekujemy za zakup towaru" << endl;
				m_product_magazine.removeProduct(product.name);
			}
		}
	}
};


int main()
{
	VendingMachine vending_machine;
	while (1)
	{
		cout << endl;
		cout << "LISTA PRODUKTOW" << endl;
		vending_machine.printProductList();

		string product = getInput(vending_machine.getProductNames(), "Wybierz produkt z listy produktow");
		if (!vending_machine.checkIfAvaliable(product))
		{
			continue;
		}

		string decision = getInput({ "TAK", "NIE" }, "Czy na pewno chcesz kupic ten produkt?\nWybierz TAK lub NIE");
		
		if (decision == "TAK")
		{
			vending_machine.payment(product);
		}
		else
		{
			cout << "Anulowano zamowienie" << endl;
		}
	}
	return 0;
}

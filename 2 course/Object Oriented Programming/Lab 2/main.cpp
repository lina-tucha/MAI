/* Хренникова Ангелина, М8О-208Б-19, 19 вариант
 *
Создать класс Address для работы с адресами домов. Адрес должен состоять из строк с названием города и улицы и чисел с
номером дома и квартиры. Реализовать операции сравнения адресов, а также операции проверки принадлежности адреса к
улице и городу. В операциях не должен учитываться регистр строки. Так же необходимо сделать операцию, которая
возвращает истину если два адреса находятся по соседству (на одной улице в одном городе и дома стоят подряд).
Операцию сравнения равенства реализовать в виде перегрузки оператора. Операцию нахождения «по соседству» реализовать
в виде перегрузки оператора &.

Необходимо реализовать пользовательский литерал для работы с константами типа Address.
*/

#include <iostream>
#include <cctype>
#include <string>
#include <algorithm>

using namespace std;

class Address {
private:
	string City, Street;
	long long House, Door;
public:
	Address() : City(), Street(), House(), Door() {};
	Address(const string& city, const string& street, const long long& house, const long long& door) 
		: City(city), Street(street), House(house), Door(door) {};
	~Address() {};
	
	string GetCity() {
		return City;
	}
	
	string GetStreet() {
		return Street;
	}

	static bool CompareString(const string& lhs, const string& rhs) { //Сравнение строк
		if (lhs.size() == rhs.size()) {
			for (int i = 0; i < lhs.size(); ++i) {
				if (tolower(lhs[i]) != tolower(rhs[i])) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}
		
	static bool IsInCity(const Address& address, const string& city, const string& street) { //Принадлежность к городу и улице
		return CompareString(address.City, city) && CompareString(address.Street, street);
	}

	friend bool operator== (const Address& lhs, const Address& rhs) {
		if (CompareString(lhs.City, rhs.City) && CompareString(lhs.Street, rhs.Street)
			&& (lhs.House == rhs.House) && (lhs.Door == rhs.Door))
			return true;
		else return false;
	}

	friend bool operator& (const Address& lhs, const Address& rhs) {
		if (CompareString(lhs.City, rhs.City) && CompareString(lhs.Street, rhs.Street)
			&& (abs((int)lhs.House - (int)rhs.House) == 2 or rhs.House == lhs.House) == true)
			return true;
		else return false;
	}
};

const Address operator"" _address(const char* str, size_t size) { //Пользовательский литерал, который разбивает строку с адресом на отдельные поля
	int position = 0;
	string city;
	while (str[position] != ',') {
		city += str[position];
		position += 1;
	}
	position += 1;
	string street;
	while (str[position] != ',') {
		street += str[position];
		position += 1;
	}
	position += 1;
	string houseStr;
	while (str[position] != ',') {
		houseStr += str[position];
		position += 1;
	}
	int house = stoi(houseStr);
	position += 1;
	string doorStr;
	while (position != size) {
		doorStr += str[position];
		position += 1;
	}
	int door = stoi(doorStr);
	Address result(city, street, house, door);
	cout << "City: " << city << "\nStreet: " << street << "\nHouse: " << house << "\nDoor: " << door << "\n";
	return result;
}

void menu() { //Меню
	cout << "Menu:\n";
	cout << "1. Check if addresses are equal.\n"; 
	cout << "2. Check if the address belongs to the street and city.\n";
	cout << "3. Check if two addresses are in the neighborhood.\n";
	cout << "4. Test user-defined literal.\n";
	cout << "5. Exit.\n";
}

signed main() {
	string city, street;
	long long house = 0, door = 0;
	cout << "Input first address city: "; //Ввод первого адреса
	cin >> city;
	cout << "Input first address street: ";
	cin >> street;
	cout << "Input first address house number: ";
	cin >> house;
	cout << "Input first address door number: ";
	cin >> door;
	Address a = Address(city, street, house, door);
	house = 0, door = 0;
	cout << "Input second address city: "; //Ввод второго адреса
	cin >> city;
	cout << "Input second address street: ";
	cin >> street;
	cout << "Input second address house number: ";
	cin >> house;
	cout << "Input second address door number: ";
	cin >> door;
	Address b = Address(city, street, house, door);
	cout << endl;
	if (house <= 0 || door <= 0) { //Ошибка при попытке ввода отрицательного или нулевого номера
		cout << "Invalid input! Programm terminates with exit code -1\n";
		return -1;
	}
	menu(); //Вывод меню
	int op;
	cout << "Select menu item:\n"; //Выбор пункта меню
	cin >> op;
	while (op >= 1 && op <= 4) {
		if (op == 1) {  //Равенство
			cout << "Equal? " << (a == b ? "YES" : "NO") << "\n";
		}
		else if (op == 2) {  //Принадлежность к городу и улице
			cout << "Same city and street? " << (Address::IsInCity(a, b.GetCity(), b.GetStreet()) ? "YES" : "NO") << "\n";
		}
		else if (op == 3) {  //Соседи
			cout << "Neighbors? " << (a & b ? "YES" : "NO") << "\n";
		}
		else if (op == 4) {  //Пользовательский литерал
			cout << "Checking the work of the user-defined literal for the address written in one line.\n";
			cout << "The literal must split the string into multiple class fields.\n";
			cout << "String format: \"City,Street,House,Door\".\n";
			cout << "String: " << "Moscow,Arbat,1,1\n";
			"Moscow,Arbat,1,1"_address;
		}
		else if (op == 5)
			break;
		else
			cout << "Error!";
		cout << "Select menu item:\n";
		cin >> op;
	}
	return 0;
}


#include <iostream>
#include "Node.h"
#include <Windows.h>
#include <regex>
using namespace std;
int main() {
	Node* head = nullptr;
	if (!loadListFromFile(head, "list.txt")) {
		return 1;}
	else cout << "Данные загружены" << endl;
	string input;
	regex valid_input("[1-5]"), valid_field("[1-5]");
	do {
		do {
			printFunctionsList();
			getline(cin, input);
		} while (!regex_match(input, valid_input));
		cout << endl;
		if (input == "1") {
			string search_field, search_content;
			int count {0};
			do {
				selectFieldForCounting();
				getline(cin, search_field);
			} while (!regex_match(search_field, valid_field));
			cout << "Введите содержимое поле: ";
			getline(cin, search_content);
			count = countElementsWithContent(head, search_content, search_field);
            cout << "Количество элементов: " << count << '\n';
			cout << endl;}
		else if (input == "2") printSortedList(head);
		else if (input == "3") {
			setDefaultValues(head, constants::fullName, constants::age, constants::status);
			saveListToFile(head, "list.txt");}
		else if (input == "4") setList(head, "list.txt");
	} while (input != "5");
	clearList(head);
	cout << "До свидания!" << endl;
	return 0;}

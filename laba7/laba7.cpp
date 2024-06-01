#include <iostream>
#include "Node.h"
#include <Windows.h>
#include <regex>
using namespace std;
int main() {
	Node* head = nullptr;
	if (!loadListFromFile(head, "list.txt")) {
		return 1;}
	else cout << "����� ����㦥��" << endl;
	string input;
	regex valid_input("[1-4]"), valid_field("[1-5]");
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
			cout << "������ ᮤ�ন��� ����: ";
			getline(cin, search_content);
			count = countElementsWithContent(head, search_content, search_field);
            cout << "������⢮ ������⮢: " << count << '\n';
			cout << endl;
		}
		else if (input == "2") printSortedList(head);
		else if (input == "3") {
			setDefaultValues(head, constants::fullName, constants::age, constants::status);
			saveListToFile(head, "list.txt");}
		else if (input == "3") setList(head, "list.txt");
	} while (input != "4");
	clearList(head);
	cout << "�� ᢨ�����!" << endl;
	return 0;
}
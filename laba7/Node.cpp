#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <iomanip>
#include <limits>
#include <iterator>
#include <algorithm>
using namespace std;
void addElement(Node*& head, const string& fullName, int age, const string& maritalStatus) {
	Node* newNode = new Node{ fullName, age, maritalStatus, nullptr, nullptr };
	if (!newNode) {
		throw runtime_error("Memory allocation failed");}
	if (!head) {
		head = newNode;
		head->next = head;
		head->prev = head;}
	else {
		Node* tail = head->prev;
		tail->next = newNode;
		newNode->prev = tail;
		newNode->next = head;
		head->prev = newNode;}}
void printList(Node* head) {
	if (!head) {
		cout << "Список пуст" << endl;
		return;}
	Node* current = head;
	cout << "Список" << endl;
	do {
		cout << "ФИО: " << current->fullName << ", Возраст: " << current->age << ", Семейное положение: " << current->maritalStatus << endl;
		current = current->next;
	} while (current != head);
	cout << endl;}
void saveListToFile(Node* head, const string& filename) {
	ofstream outFile(filename);
	if (!outFile) {
		cerr << "Ошибка открытия файла для записи" << endl;
		return;}
	if (!head) {
		outFile << "";
		return;}
	Node* current = head;
	do {
		outFile << current->fullName << "; " << current->age << "; " << current->maritalStatus << "\n";
		current = current->next;
	} while (current != head);}
bool loadListFromFile(Node*& head, const string& filename) {
	ifstream inFile(filename);
	if (!inFile) {
		cerr << "Ошибка открытия файла для чтения" << endl;
		return false;}
	string line;
	regex valid_fio("^[A-Za-zА-Яа-я]+? [A-Za-zА-Яа-я]+? [A-Za-zА-Яа-я]+?$");
	while (getline(inFile, line)) {
		istringstream ss(line);
		string fullName, maritalStatus;
		int age;
		char delimiter;
		getline(ss, fullName, ';');
		ss >> age >> delimiter;
		getline(ss, maritalStatus);
		if (!regex_match(fullName, valid_fio)) {
			cerr << "Ошибка при чтении данных.\n";
			cerr << "Некорректное ФИО. (пример: Янов Ян Янович)\n";
			cerr << "Пожалуйста, исправьте содержимое файла.\n";
			return false;}
		if(!(fullName.length() && bool(age) && maritalStatus.length())) {
			cerr << "Ошибка при чтении данных.\n";
			cerr << "Пропущено одно из полей.\n";
			cerr << "Пожалуйста, исправьте содержимое файла.\n";
			return false;}
		if (fullName.length() > 35) {
			cerr << "Ошибка при чтении данных.\n";
			cerr << "Поле ФИО должно содержать не более 35 символов для корректности работы программы.\n";
			cerr << "Пожалуйста, исправьте содержимое файла.\n";
			return false;}
		if (maritalStatus.length() > 15) {
			cerr << "Ошибка при чтении данных.\n";
			cerr << "Поле семейное положение должно содержать не более 15 символов для корректности работы программы.\n";
			cerr << "Пожалуйста, исправьте содержимое файла.\n";
			return false;}
		addElement(head, fullName, age, maritalStatus);}
	inFile.close();
	return true;}
void clearList(Node*& head) {
	if (!head) return;
	Node* current = head;
	do {
		Node* temp = current;
		current = current->next;
		delete temp;
	} while (current != head);
	head = nullptr;}
int getIntInput() {
	int input;
	while (!(cin >> input)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Некорректный ввод. Пожалуйста, введите целое число: ";}
	return input;}
void printFunctionsList() {
    cout << "Список доступных команд:\n";
    cout << "1) Подсчитать количество элементов c заданным содержимым одного из полей.\n";
    cout << "2) Печать всех элементов в отсортированном виде (по ФИО).\n";
    cout << "3) Присвоить всем элементам предустановленные значения.\n";
	cout << "4) Заполнить данными.\n";
    cout << "5) Выход.\n";
	cout << "Введите номер команды: ";}
void selectFieldForCounting() {
    cout << "Поле выборки:\n";
    cout << "1) по фамилии.\n2) по имени.\n";
    cout << "3) по отчеству.\n4) по возрасту.\n";
    cout << "5) по семейному положению.\n";
	cout << "Введите номер команды: ";}
int countElementsWithContent(Node* head, const string& content, const string& field) {
    int count {0};
    if (!head) return count;
    Node* temp = head;
    do {
		if (field == "4" && to_string(temp->age) == content){count++;}
		if (field == "5"){
			string str = temp->maritalStatus;
			str = regex_replace(str, regex("^ +"), "");
			if(str == content){count++;}}
		vector<string> fio;
		istringstream iss(temp->fullName);
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(fio));
		if (field == "1" && fio[0] == content){count++;}
		if (field == "2" && fio[1] == content){count++;}
		if (field == "3" && fio[2] == content){count++;}
        temp = temp->next;
    } while (temp != head);
    return count;}
void printSortedList(Node* head) {
    if (!head) {
	cerr << "Список пуст. Не могу выполнить данную операцию.\n";
	cerr << "Пожалуйста, исправьте содержимое файла.\n";
	return;}
    vector<Node*> nodes;
    Node* temp = head;
    do {
        nodes.push_back(temp);
        temp = temp->next;
    } while (temp != head);
	cout << nodes.size() << endl;
    sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
        return a->fullName < b->fullName;});
    cout << left << setw(40) << "ФИО" << setw(10) << "Возраст" << setw(20) << " Семейное положение" << endl;
    cout << "--------------------------------------------------------------------------------\n";
    for (Node* node : nodes) {
    cout << left << setw(40) << node->fullName << setw(10) << node->age << setw(20) << node->maritalStatus << endl;
    }
	cout << endl;}
void setDefaultValues(Node* head, const string& fullName, int age, const string& maritalStatus) {
	if (!head) {
	cerr << "Список пуст. Не могу выполнить данную операцию.\n";
	cerr << "Пожалуйста, исправьте содержимое файла.\n";
	return;}
	Node* current = head;
	do {
		current->fullName = fullName;
		current->age = age;
		current->maritalStatus = maritalStatus;
		current = current->next;
	} while (current != head);}
void setList(Node*& head, const string& filename) {
	clearList(head);
	addElement(head, "Иванов Святослав Игоревич", 25, "Не женат");
	addElement(head, "Ишгулов Ратмир Русланович", 18, "Не женат");
	addElement(head, "Малышев Владимир Игоревич", 19, "Не женат");
	addElement(head, "Замилова Азалия Ринатовна", 19, "Не замужем");
	addElement(head, "Наумов Денис Олегович", 31, "Женат");
	addElement(head, "Мухтаров Адель Рамилевич", 24, "Не женат");
	addElement(head, "Самойлова Анастасия Борисовна", 24, "Замужем");
	addElement(head, "Каримов Азамат Тимурович", 43, "Не женат");
	saveListToFile(head, filename);}

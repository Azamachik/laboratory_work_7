#include "Node.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <iterator>
#include <algorithm>
using namespace std;
void addElement(Node*& head, const std::string& fullName, int age, const std::string& maritalStatus) {
	Node* newNode = new Node{ fullName, age, maritalStatus, nullptr, nullptr };
	if (!newNode) {
		throw std::runtime_error("Memory allocation failed");
	}
	if (!head) {
		head = newNode;
		head->next = head;
		head->prev = head;
	}
	else {
		Node* tail = head->prev;
		tail->next = newNode;
		newNode->prev = tail;
		newNode->next = head;
		head->prev = newNode;
	}
}

void printList(Node* head) {
	if (!head) {
		std::cout << "���᮪ ����" << std::endl;
		return;
	}

	Node* current = head;
	std::cout << "���᮪" << std::endl;
	do {
		std::cout << "���: " << current->fullName << ", ������: " << current->age << ", �������� ���������: " << current->maritalStatus << std::endl;
		current = current->next;
	} while (current != head);
	std::cout << std::endl;
}

void saveListToFile(Node* head, const std::string& filename) {
	std::ofstream outFile(filename);
	if (!outFile) {
		std::cerr << "�訡�� ������ 䠩�� ��� �����" << std::endl;
		return;
	}
	if (!head) {
		outFile << "";
		return;
	}
	Node* current = head;
	do {
		outFile << current->fullName << "; " << current->age << "; " << current->maritalStatus << "\n";
		current = current->next;
	} while (current != head);
}

bool loadListFromFile(Node*& head, const std::string& filename) {
	std::ifstream inFile(filename);
	if (!inFile) {
		std::cerr << "�訡�� ������ 䠩�� ��� �⥭��" << std::endl;
		return false;
	}

	std::string line;
	while (std::getline(inFile, line)) {
		std::istringstream ss(line);
		std::string fullName, maritalStatus;
		int age;
		char delimiter;

		std::getline(ss, fullName, ';');
		ss >> age >> delimiter;
		std::getline(ss, maritalStatus);
		if(!(fullName.length() && bool(age) && maritalStatus.length())) {
			cerr << "�訡�� �� �⥭�� ������.\n";
			cerr << "�ய�饭� ���� �� �����.\n";
			cerr << "��������, ��ࠢ�� ᮤ�ন��� 䠩��.\n";
			return false;
		}
		if (fullName.length() > 35) {
			cout << fullName.length() << ' ' << fullName << endl;
			cerr << "�訡�� �� �⥭�� ������.\n";
			cerr << "���� ��� ������ ᮤ�ঠ�� �� ����� 35 ᨬ����� ��� ���४⭮�� ࠡ��� �ணࠬ��.\n";
			cerr << "��������, ��ࠢ�� ᮤ�ন��� 䠩��.\n";
			return false;
		}
		addElement(head, fullName, age, maritalStatus);
	}
	inFile.close();
	return true;
}

void clearList(Node*& head) {
	if (!head) return;

	Node* current = head;
	do {
		Node* temp = current;
		current = current->next;
		delete temp;
	} while (current != head);

	head = nullptr;
}

int getIntInput() {
	int input;
	while (!(std::cin >> input)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "�����४�� ����. ��������, ������ 楫�� �᫮: ";
	}
	return input;
}
void printFunctionsList() {
    cout << "���᮪ ����㯭�� ������:\n";
    cout << "1) �������� ������⢮ ����⮢ c ������� ᮤ�ন�� ������ �� �����.\n";
    cout << "2) ����� ��� ����⮢ � �����஢����� ���� (�� ���).\n";
    cout << "3) ��᢮��� �ᥬ ����⠬ �।��⠭������� ���祭��.\n";
    cout << "4) ��室.\n";
	cout << "������ ����� �������: ";
}
void selectFieldForCounting() {
    cout << "���� �롮ન:\n";
    cout << "1) �� 䠬����.\n2) �� �����.\n";
    cout << "3) �� ������.\n4) �� �������.\n";
    cout << "5) �� ᥬ������ ���������.\n";
	cout << "������ ����� �������: ";
}
int countElementsWithContent(Node* head, const string& content, const string& field) {
    int count {0};
    if (!head) return count;
    Node* temp = head;
    do {
		if (field == "4" && to_string(temp->age) == content){count++;}
		if (field == "5" && temp->maritalStatus == content){count++;}
		vector<string> fio;
		istringstream iss(temp->fullName);
		copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(fio));
		if (field == "1" && fio[0] == content){count++;}
		if (field == "2" && fio[1] == content){count++;}
		if (field == "3" && fio[2] == content){count++;}
        temp = temp->next;
    } while (temp != head);
    return count;
}
void printSortedList(Node* head) {
    if (!head) return;
    std::vector<Node*> nodes;
    Node* temp = head;
    do {
        nodes.push_back(temp);
        temp = temp->next;
    } while (temp != head);
    std::sort(nodes.begin(), nodes.end(), [](Node* a, Node* b) {
        return a->fullName < b->fullName;
    });
    std::cout << std::left << std::setw(40) << "���" << std::setw(10) << "������" << std::setw(20) << " �������� ���������" << std::endl;
    std::cout << "--------------------------------------------------------------------------------\n";
    for (Node* node : nodes) {
        std::cout << std::left << std::setw(40) << node->fullName << std::setw(10) << node->age << std::setw(20) << node->maritalStatus << std::endl;
    }
	cout << endl;
}
void setDefaultValues(Node* head, const std::string& fullName, int age, const std::string& maritalStatus) {
	if (!head) return;

	Node* current = head;
	do {
		current->fullName = fullName;
		current->age = age;
		current->maritalStatus = maritalStatus;
		current = current->next;
	} while (current != head);
}

void setList(Node*& head, const std::string& filename) {
	clearList(head);
	addElement(head, "������ ����᫠� ���ॢ��", 25, "�� �����");
	addElement(head, "��㫮� ��⬨� ��᫠�����", 18, "�� �����");
	addElement(head, "����襢 �������� ���ॢ��", 19, "�� �����");
	addElement(head, "�������� ������ ����⮢��", 19, "�� ���㦥�");
	addElement(head, "��㬮� ����� ��������", 31, "�����");
	addElement(head, "����஢ ����� ���������", 24, "�� �����");
	addElement(head, "��������� ������� ���ᮢ��", 24, "���㦥�");
	addElement(head, "��ਬ�� ������ ����஢��", 43, "�� �����");
	saveListToFile(head, filename);
}
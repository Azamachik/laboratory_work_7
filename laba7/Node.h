#ifndef __NODE_H__
#define __NODE_H__
#include <string>
using namespace std;
struct Node {
	std::string fullName;
	int age;
	std::string maritalStatus;
	Node* prev;
	Node* next;
};

namespace constants {
	const std::string fullName{ "Иванов Иван Иванович" };
	const std::string status{ "не женат" };
	const int age{ 20 };
}

void addElement(Node*& head, const std::string& fullName, int age, const std::string& maritalStatus);
void printList(Node* head);
void selectFieldForCounting();
bool deleteElement(Node*& head, const std::string& searchValue);
void saveListToFile(Node* head, const std::string& filename);
bool loadListFromFile(Node*& head, const std::string& filename);

void clearList(Node*& head);

int getIntInput();
void printSortedList(Node* head);
int countElementsWithContent(Node* head, const std::string& content, const string& field);
void setDefaultValues(Node* head, const std::string& fullName, int age, const std::string& maritalStatus);


void setList(Node*& head, const std::string& filename);

void printFunctionsList();
#endif
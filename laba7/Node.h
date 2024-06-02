#ifndef __NODE_H__
#define __NODE_H__
#include <string>
using namespace std;
struct Node {
	string fullName;
	int age;
	string maritalStatus;
	Node* prev;
	Node* next;};
namespace constants {
	const string fullName{ "Иванов Иван Иванович" };
	const string status{ "не женат" };
	const int age{ 20 };}
void addElement(Node*& head, const string& fullName, int age, const string& maritalStatus);
void printList(Node* head);
void selectFieldForCounting();
void saveListToFile(Node* head, const string& filename);
bool loadListFromFile(Node*& head, const string& filename);
void clearList(Node*& head);
int getIntInput();
void printSortedList(Node* head);
int countElementsWithContent(Node* head, const string& content, const string& field);
void setDefaultValues(Node* head, const string& fullName, int age, const string& maritalStatus);
void setList(Node*& head, const string& filename);
void printFunctionsList();
#endif

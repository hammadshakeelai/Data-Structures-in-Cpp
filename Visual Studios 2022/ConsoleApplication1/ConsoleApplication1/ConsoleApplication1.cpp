#include<iostream>
#include <fstream>
using namespace std;
class Node {
public:
	int data;
	Node* right_child;
	Node* left_child;
	Node(int value) : data(value), right_child(nullptr), left_child(nullptr) {}
};
class BinaryTree {
	private:
		Node* root;
	public:
		BinaryTree() : root(nullptr) {}
		~BinaryTree() {
			// Destructor logic to free memory can be added here

		}
		Node* insertRec(Node* node, int value) {
			if (node == nullptr) {
				return new Node(value);
			}
			if (value > node->data) {
				node->right_child = insertRec(node->right_child, value);
			}
			else if (value < node->data) {
				node->left_child = insertRec(node->left_child, value);
			}
			else {
				return node;
			}
		}
		void insert(int value) {
			if(root == nullptr) {
				root = new Node(value);
			}
			else {
				if (value > root->data) {
					root->right_child = insertRec(root->right_child, value);
				}
				else if (value < root->data) {
					root->left_child = insertRec(root->left_child, value);
				}
				else { return; }
			}
		
		}
		void DisplayInOrder(Node* node) {
			if (node != nullptr) {
				DisplayInOrder(node->left_child);
				cout << node->data << " ";
				DisplayInOrder(node->right_child);
			}
		}
		Node* getRoot() {
			return root;
		}
		void Display() {
			DisplayInOrder(root);
		}
};
int main() {
	//---------------------------------------------------------------
	BinaryTree tree;
	tree.insert(50);
	tree.insert(30);
	tree.insert(20);
	tree.insert(40);
	tree.insert(70);
	tree.insert(60);
	tree.insert(80);
	cout << "In-order traversal of the binary search tree is: ";
	tree.Display();
	cout << endl;

	//---------------------------------------------------------------
	return 0;
}
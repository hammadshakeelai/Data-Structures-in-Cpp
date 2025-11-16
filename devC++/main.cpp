#include<iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;
// joesephus problem circular linked list
struct Node {
	int data;
	Node* next;
	Node(int value) : data(value), next(nullptr) {}
};
class CircularSinglyLinkedList {
public:
	Node* head;
	Node* tail;

public:
	CircularSinglyLinkedList() : head(nullptr), tail(nullptr) {}
	~CircularSinglyLinkedList() {
		Node* cur = head;
		Node* temp = nullptr;
		do{
			temp = cur->next;
			delete cur;
			cur = temp;
		}while (cur != head);
	}
	void addAtEnd(int value) {//use tail // tick
		Node* node = new Node(value);
		if (head == nullptr) {
			head = node;
			tail = node;
			node->next = head;
			return;
		}
		tail->next = node;
		tail = node;
		node->next = head;
	}
	bool revoveFromHead() {// tick
		if (head == nullptr) {
			cout << "queue is empty.\n";
			return false;
		}
		Node* temp = head;
		head = temp->next;
		delete temp;
		return true;
	}
	int count() const {
		int count = 0;
		Node* cur = head;
		if (cur == nullptr) {
			return count;
		}
		do{
			count++;
			cur = cur->next;
		}while (cur != head);
		return count;
	}
	bool removePos(int pos) {
		if (head == nullptr) {
			cout << "queue is empty.\n";
			return false;
		}
		if(pos > count() || pos < 1) {
			cout << "Pos out of bounds.\n";
			return false;
		}
		Node* temp = head;
		if (pos == 1) {//start
			
			head = head->next;
			delete temp;
			return true;
		}
		for(int i = 1;i < pos-1;i++) 
		{
			/*if (temp->next == nullptr) {
				cout << "Pos out of bounds.\n";
				return false;
			}*/
			temp = temp->next;
		}
		
		Node* cur = temp->next;
		temp->next = cur->next;
		if (cur == tail) {
			tail = temp;
		}
		delete cur;
		return true;
	}
	void Display() const {// tick
		Node* cur = head;
		cout << "Displaying List:\n";
		if (cur == nullptr) {
			cout << "List is empty.\n";
			return;
		}
		 do{
			cout << cur->data << " -> ";
			cur = cur->next;
		}while (cur != head);
	}
	int josephusProblem(int k) {
		if (head == nullptr || k < 0) {
			cout << "List is empty or invalid k.\n";
			return -1;
		}
		Node* cur = head;
		Node* prev = tail;
		while (count() > 1) {
			for (int i = 1; i < k + 1 ; i++) {
				prev = cur;
				cur = cur->next;
			}
			prev->next = cur->next;
			if (cur == head) {
				head = cur->next;
			}
			if (cur == tail) {
				tail = prev;
			}
			delete cur;
			cur = prev->next;
		}
		int survivor = head->data;
		delete head;
		head = nullptr;
		tail = nullptr;
		return survivor;
	}
};
int josephusProblem(int n,int m) {
	CircularSinglyLinkedList list;
	for(int i = 1; i <= n; i++) {
		list.addAtEnd(i);
	}
	if (list.head == nullptr || m < 0) {
		cout << "List is empty or invalid k.\n";
		return -1;
	}
	else if(m==0){
		return list.tail->data;
	}
	Node* cur = list.head;
	while (list.count() > 1) {
		for (int i = 1; i < m ; i++) {
			cur = cur->next;
		}
		Node* temp = cur->next;
		cur->next = temp->next;
		if (temp == list.head) {
			list.head = temp->next;
		}
		if (temp == list.tail) {
			list.tail = cur;
		}
		delete temp;
		cur = cur->next;
		//list.Display();//dry run
	}
	return list.head->data;
}
int main() {
	auto start = high_resolution_clock::now();   // start time
	//---------------------------------------------------------------
	CircularSinglyLinkedList list;/**/
	list.addAtEnd(1);
	list.addAtEnd(2);
	list.addAtEnd(3);
	list.addAtEnd(4);
	list.addAtEnd(5);
	list.addAtEnd(6);
	list.addAtEnd(7);
	list.addAtEnd(8);
	list.addAtEnd(9);
	list.addAtEnd(10);
	cout<<"enter n: ";
	int m;
	cin >>m;
	cout << list.josephusProblem(m) << endl;/**/

//	cout << "Josephus Problem Simulation:\n";
//	int n; // number of people
//	cout << "Enter number of people (n): ";
//	cin >> n;
//	int m; // step count
//	cout << "Enter step count (m): ";
//	cin >> m;
	cout << "The position of the last remaining person is: " << josephusProblem(10, m) << endl;
	//---------------------------------------------------------------
	auto end = high_resolution_clock::now();     // end time
	auto duration = duration_cast<milliseconds>(end - start);

	cout << "\nExecution time: " << duration.count() << " ms\n";
	return 0;
}/*
public class Node {
  private int data;
  private Node left;
  private Node right;
public int getData()  {
    return data;
  }
  
  public Node getLeft()  {
    return left;
  }

    public Node getRight()  {
    return right;
  }
 
  public void setData(int x)  {
    data = x;
  }
public void setLeft(Node p)  {
    left = p;
  }

  public void setRight(Node p)  {
    right = p;
  }


}
public class Tree {
    private Node root;
    
    // tree() - The default constructor – Starts
    //          the tree as empty
    
    public Tree() {
        root = null;
    }
    
    // Tree() - An initializing constructor that
    //          creates a node and places in it
    //          the initial value
    public Tree(int x) {
        root = new Node();
        root.setData(x);
        root.setLeft(null);
        root.setRight(null);
    }
    
    public Node getRoot() {
        return root;
    }
    
    // newNode() -  Creates a new node with a
    //              zero as data by default
    public Node newNode() {
        Node p = new Node();
        p.setData(0);
        p.setLeft(null);
        p.setRight(null);
        return(p);
    }
    // newNode() -  Creates a new node with the
    //              parameter x as its value
    public Node newNode(int x)  {
        Node p = new Node();
        p.setData(x);
        p.setLeft(null);
        p.setRight(null);
        return(p);  
    }
    //travTree() – initializes recursive 
    //	traversal of tree
	  public void  travTree() {
        if (root != null)
          travSubtree(root);
        System.out.println();
    }
    //travSubtree() – recursive method used to 
	  //	traverse a binary tree (inorder)
    public void  travSubtree(Node p) {
        if (p != null)  {
            travSubtree(p.getLeft());
            System.out.print(p.getData() 
						+ "\t");
            travSubtree(p.getRight());
        } 
    }
    // addLeft() -  Inserts a new node containing
    //              x as the left child of p
    public void  addLeft(Node p, int x) {
        Node   q = newNode(x);
        p.setLeft(q);
    }
    
	 // addRight() -  Inserts a new node containing
   //                x as the right child of p
    public void  addRight(Node p, int x) {
        Node   q = newNode(x);
        p.setRight(q);
    }
}
    // insert() -	Insert value x in a new node to
    //				be inserted	after p
    public void	insert(int x)  {
        Node 	p, q;
        boolean	found = false;
        p = root;
        q = null;
        while (p != null && !found)	{
            q = p;
            if (p.getData() == x)
              found = true;
            else if (p.getData() > x)
              p = p.getLeft();
            else
              p = p.getRight();
        }
        if (found)
          error("Duplicate entry");
          
        if (q.getData() > x)
          addLeft(q, x);
        else
          addRight(q, x);
        
        //q = newNode(x);
    }
    // isXThere() -	Is there a node in the
    //                  tree containing x?
    public boolean	isXThere(int x)  {
        Node 	p;
        boolean	found = false;
        p = root;
        while (p != null && !found)	{
            if (p.getData() == x)
              found = true;
            else if (p.getData() > x)
              p = p.getLeft();
            else
              p = p.getRight();
        }
        return(found);
    }
    
    public void	error(String message) {
	    System.out.println(message);
	    System.exit(0);
    }
    // getNode() -	Get the pointer for the
    //                  node containing x
    public Node	getNode(int x) {
        Node 	p, q;
        boolean	found = false;
        
        p = root;
        q = null;
        while (p != null && !found)	{
            q = p;
            if (p.getData() == x)
			  found = true;
			else if (p.getData() > x)
			  p = p.getLeft();
			else
			  p = p.getRight();
		}
	if (found)
		  return(q);
		else
		  return(null);
    }
public class TestTree {
    public static void main(String[] args) {
        Tree	mytree = new Tree(8);
        mytree.addLeft(mytree.getRoot(), 6);
        mytree.addRight(mytree.getRoot(), 9);
        mytree.insert(4);
        mytree.insert(1);
        mytree.insert(12);
        
        if (mytree.isXThere(13))
          System.out.println("great");
        else 
		    System.out.println("not great, Bob");
        mytree.travTree();
    }
}

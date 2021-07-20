#include <iostream>
#include <unordered_map>

class Node{
public:
	int data;
	Node* prev;
	Node* next;

	Node(int d){
		this->data = d;
		prev = NULL;
		next = NULL;
	}
};


class LRUCache{
private:
	int size;
	int cap;
	Node* head;
	Node* tail;
	std::unordered_map<int, Node*> m;

	void insertHead(int val){
		Node* toadd = new Node(val);
		if(head == NULL){
			head = toadd;
			tail = head;
		}
		else if(head == tail){
			head->prev = toadd;
			head = head->prev;
			head->next = tail;
		}else{
			head->prev = toadd;
			toadd->next = head;
			head = head->prev;
		}
	}

	void removeTail(){
		if(tail == NULL){
			return;
		}
		if(head == tail){
			head = NULL;
			tail = NULL;
		}
		else{
			Node* toremove = tail;
			tail = tail->prev;
			tail->next = NULL;
			delete toremove;
		}
	}

	void moveNode(Node* tomove){
		if(tomove->prev == NULL){
			return;
		}
		if(tomove->next == NULL){
			tail = tail->prev;
			tail->next = NULL;
		}
		else{
			Node* before = tomove->prev;
			Node* after = tomove->next;
			before->next = after;
			after->prev = before;
		}
		tomove->next = head;
		head->prev = tomove;
		head = head->prev;
	}
public:
	LRUCache(int capacity){
		size = 0;
		cap = capacity;
		head = NULL;
		tail = NULL;
	}

	~LRUCache(){
		while(size > 0){
			Node* temp = head;
			head = head->next;
			delete temp;
			size--;
		}
	}

	int get(int key){
		if(m.find(key) != m.end()){
			Node* ret = m[key];
			moveNode(ret);
			return ret->data;
		}
		return -1;
	}

	void put(int key, int value){
		if(size < cap){
			insertHead(value);
			size++;	
		}
		else{
			removeTail();
			insertHead(value);
		}
		m.insert({key, head});
	}
	
	void printSelf(){
		Node* curr = head;
		std::cout << "Data: ";
		while(curr->next != NULL){
			std::cout << curr->data << " -> ";
			curr = curr->next;
		}
		std::cout << curr->data << std::endl;
	}

	void printReverse(){
		Node* curr = tail;
		std::cout << "Data reversed: ";
		while(curr->prev != NULL){
			std::cout << curr->data << " -> ";
			curr = curr->prev;
		}
		std::cout << curr->data << std::endl;
	}
};

int main(){
	LRUCache c(2);
	std::cout << "Added 1:1" << std::endl;
	c.put(1, 1);
	c.printSelf();

	std::cout << "Added 2:2" << std::endl;
	c.put(2, 2);
	c.printSelf();

	std::cout << "Got 1:1" << std::endl;
	c.get(1);
	c.printSelf();

	std::cout << "Added 3:3" << std::endl;
	c.put(3, 3);
	c.printSelf();

	std::cout << "Got 3:3" << std::endl;
	c.get(3);
	c.printSelf();
}

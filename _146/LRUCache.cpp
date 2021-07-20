#include <iostream>
#include <unordered_map>

class Node{
public:
	int k;
	int data;
	Node* prev;
	Node* next;

	Node(int d){
		k = 0;
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

	void insertHead(int k, int val){
		Node* toadd = new Node(val);
		toadd->k = k;
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
			Node* todelete = head;
			head = NULL;
			tail = NULL;
			delete todelete;
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
		tomove->prev = NULL;
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
		if(m.find(key) == m.end()){
			if(size < cap){
				insertHead(key, value);
				size++;	
			}
			else{
				int keytorem = tail->k;
				m.erase(keytorem);
				removeTail();
				insertHead(key, value);
			}
			
			m.insert({key, head});
		}
		else{
			m[key]->data = value;
			moveNode(m[key]);
		}
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
	c.put(1,1);
	c.put(2, 2);
	c.printSelf();
	c.get(1);
	c.put(3,3);
	c.printSelf();
	c.get(2);
	c.printSelf();
	c.put(4, 4);
	c.get(1);
	//case updating values
	c.put(3, 5);
	c.printSelf();
	std::cout << "value in 3 is " << c.get(3) << std::endl;
}

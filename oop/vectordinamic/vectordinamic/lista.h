#pragma once

template <typename T>
class Lista {
private:
	struct Node {
		T val;
		Node* next;

		Node(const T& v) : val{ v }, next{ nullptr } {

		}
	};
	Node* head;
	Node* tail;
	int sizeL;
public:
	Lista() : head{ nullptr }, tail{ nullptr }, sizeL{ 0 } {

	}
	Lista(const Lista& ot) : head{ nullptr }, tail{ nullptr }, sizeL{ 0 } {
		Node* p = ot.head;
		while (p != nullptr) {
			add(p->val);
			p = p->next;
		}
	}
	Lista& operator=(const Lista& ot) {
		if (this == &ot) {return *this;}

		Node* p = head; 
		while (p != nullptr) {
			Node* deSters = p;
			p = p->next;
			delete deSters;
		}

		head = nullptr;
		tail = nullptr;
		sizeL = 0;

		Node* curent = ot.head;
		while (curent != nullptr) {
			add(curent->val);
			curent = curent->next;
		}

		return *this;
	}
	/*adauga un element la finalul listei*/
	void add(const T& v) {
		Node* p = new Node { v };
		if (head == nullptr) {
			head = p;
			tail = p;
		}
		else {
			tail->next = p;
			tail = p;
		}
		sizeL++;
	}
	T& operator[](int index) {
		Node* curent = head;
		int i { 0 };
		while (curent != nullptr && i < index) {
			i++;
			curent = curent->next;
		}
		return curent->val;
	}
	const T& operator[](int index) const { 
		Node* curent = head;
		int i{ 0 };
		while (curent != nullptr && i < index) {
			i++;
			curent = curent->next;
		}
		return curent->val;
	}

	T& get(int index) {
		return (*this)[index]; 
	}
	const T& get(int index) const {
		return (*this)[index]; 
	}

	~Lista() {
		Node* p = head;
		while (p != nullptr) {
			Node* deSters = p;
			p = p->next;
			delete deSters;
		}
	}
	
	class Iterator {
	private:
		Node* curent;
	public:
		Iterator(Node* p) : curent{ p } {}

		bool operator!=(const Iterator& ot) const {
			return curent != ot.curent;
		}

		Iterator& operator++() {
			curent = curent->next;
			return *this;
		}

		T& operator*() {
			return curent->val;
		}
	};

	Iterator begin() const {
		return Iterator{ head };
	}

	Iterator end() const {
		return Iterator{ nullptr };
	}
	int size() const {
		return sizeL;
	}
	void remove(const T& valoare) {
		Node* curent = head;
		Node* anterior = nullptr;

		while (curent != nullptr) {
			if (curent->val == valoare) {
			
				if (anterior == nullptr) {
					
					head = curent->next;
					if (head == nullptr) tail = nullptr; 
				}
				else {
					
					anterior->next = curent->next;
					if (curent == tail) tail = anterior; 
				}

				delete curent;
				sizeL--;
				return;
			}
			anterior = curent;
			curent = curent->next;
		}
	}
	bool empty() {
		return sizeL == 0;
	}
	bool empty() const{
		return sizeL == 0;
	}

	
};
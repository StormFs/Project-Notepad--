#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <stack>
#include <queue>
using namespace std;
	template<typename T>
	class Doubly {
		class Node {
		public: 
			T data;
			Node* next;
			Node* prev;
			Node(T d, Node* nptr = nullptr, Node* pptr = nullptr) :data(d), next(nptr), prev(pptr) {};
		};
		Node* head;
		Node* Cursor;
		Node* select;
		int size;
		int pos;
	public:
		Doubly() {
			head = new Node('|', nullptr, nullptr);
			Cursor = head;
			select = nullptr;
			size = 0;
			pos = 0;
		}
		void insertHead(T val) {
			head = new Node(val, head, nullptr);
			Cursor = head->next;
			Cursor->prev = head;
		}
		void addchar(T val) {
			if (Cursor == head) {
				insertHead(val);
			}
			else {
				Cursor->prev = new Node(val, Cursor, Cursor->prev);
				if (size != 0) {
					Cursor->prev->prev->next = Cursor->prev;
				}
				Node* c = Cursor;
				while (c->prev != nullptr) {
					c = c->prev;
				}
				head = c;
			}
			++size;
			pos++;
		}
		void removeChar() {
			if (Cursor->prev != nullptr) {
				Node* n = Cursor->prev;
				if (Cursor->prev->prev != nullptr) {
					Cursor->prev->prev->next = Cursor;
					Cursor->prev = n->prev;
					delete n;
					--size;
					pos--;
				}
				else {
					head = Cursor;
					delete Cursor->prev;
					Cursor->prev = nullptr;
					--size;
					pos--;
				}
			}
		}
		void handledelete() {
			if (Cursor->next != nullptr) {
				Node* n = Cursor->next;
				if (Cursor->next->next != nullptr) {
					Cursor->next->next->prev = Cursor;
					Cursor->next = n->next;
					delete n;
					--size;
				}
				else {
					delete Cursor->next;
					Cursor->next = nullptr;
					--size;
				}
			}
		}
		void HandleMultipleDeleteThroughDelete() {
			if (Cursor->next == nullptr) {
				return;
			}
			if (Cursor->next->data == ' ' && Cursor->next->data != '\n') {
				handledelete();
			}
			if (Cursor->next->data == '\n') {
				handledelete();
			}
			while (Cursor->next != nullptr && Cursor->next->data != ' ' && Cursor->next->data != '\n') {
				handledelete();
			}
		}
		void HandleMultipleDeleteThroughBack() {
			if (Cursor->prev == nullptr) {
				return;
			}
			if (Cursor->prev->data == '\n') {
				removeChar();
			}
			if (Cursor->prev != nullptr && Cursor->prev->data == ' ' && Cursor->prev->data != '\n') {
				removeChar();
			}
			while (Cursor->prev != nullptr && Cursor->prev->data != ' ' && Cursor->prev->data != '\n') {
				removeChar();
			}
		}
		void moveLeft() {
			if (Cursor->prev != nullptr) {
				Cursor->data = Cursor->prev->data;
				Cursor->prev->data = '|';
				Cursor = Cursor->prev;
				pos--;
			}
		}
		void moveRight() {
			if (Cursor->next != nullptr) {
				Cursor->data = Cursor->next->data;
				Cursor->next->data = '|';
				Cursor = Cursor->next;
				pos++;
			}
		}
		void moveCursor(int val) {
			if (val == 77) {
				moveRight();
			}
			if (val == 75) {
				moveLeft();
			}
		}
		void print() {
			system("cls");
			Node* n = head;
			string s1 = "";
			while (n != nullptr) {
				s1 = s1 + n->data;
				n = n->next;
			}
			cout << s1;
		}
		int getSize() {
			return size;
		}
		bool saveFile() {
			cout << "enter the name of the save file." << endl;
			string name;
			cin >> name;
			ifstream temp;
			temp.open(name + ".txt");
			bool overwrite = 1;
			if (temp.is_open()) {
				cout << "A file of similar name already exists. Do you want to overwrite it? (y/n)" << endl;
				char ch = 'a';
				while (ch != 'y' || ch != 'n') {
					cin >> ch;
					ch = tolower(ch);
					if (ch == 'y') {
						overwrite = 1;
						break;
					}
					if (ch == 'n') {
						overwrite = 0;
						return 0;
					}
				}
			}
			if (overwrite == 1) {
				ofstream file{ name + ".txt" };
				ofstream file1;
				file1.open(name + ".txt");
				Node* n = head;
				for (int i = 0; i <= size; i++) {
					if (n->data != '|') {
						file1 << n->data;
					}
					n = n->next;
				}
				file1 << '\0';
				file.close();
				file1.close();
				return 1;
			}
			return 0;
		}
		void moveDown() {
			Node* back = Cursor;
			Node* front = Cursor;
			int backcount = 0;
			int frontcount = 0;
			while (back != nullptr && back->data != '\n') {
				back = back->prev;
				++backcount;
			}
			while (front != nullptr && front->data != '\n') {
				front = front->next;
				++frontcount;
			}
			for (int i = 0; i < frontcount; i++) {
				moveCursor(77);
			}
			for (int i = 1; i < backcount; i++) {
				if (Cursor->next == nullptr) {
					break;
				}
				if (Cursor->next->data == '\n') {
					break;
				}
				moveCursor(77);
			}
		}
		void moveUp() {
			Node* back = Cursor;
			Node* front = Cursor;
			int backcount = 0;
			int frontcount = 0;
			while (back != nullptr && back->data != '\n') {
				back = back->prev;
				++backcount;
			}
			for (int i = 0; i < backcount; i++) {
				moveCursor(75);
			}
			while (Cursor->prev != nullptr && Cursor->prev->data != '\n') {
				moveCursor(75);
			}
			for (int i = 1; i < backcount; i++) {
				if (Cursor->next->data == '\n') {
					break;
				}
				moveCursor(77);
				if (Cursor->prev == nullptr) {
					break;
				}
			}
		}
		int getpos() {
			return pos;
		}
		string savestring() {
			string str = "";
			Node* Temp = head;
			while (Temp != nullptr) {
				if (Temp->data != '|') {
					str += Temp->data;
				}
				Temp = Temp->next;
			}
			return str;
		}
		void HandleControlRight() {
			if (Cursor->next != nullptr) {
				if (Cursor->next->data == ' ' || Cursor->next->data == '\n') {
					moveCursor(77);
				}
			}
			while (Cursor->next != nullptr && Cursor->next->data != ' ' && Cursor->next->data != '\n') {
				moveCursor(77);
			}
		}
		void HandleControlLeft() {
			if(Cursor->prev != nullptr) {
				if (Cursor->prev->data == ' ' || Cursor->prev->data == '\n') {
					moveCursor(75);
				}
			}
			while (Cursor->prev != nullptr && Cursor->prev->data != ' ' && Cursor->prev->data != '\n') {
				moveCursor(75);
			}
		}
		void clearall() {
			while (true) {
				if (Cursor->prev != nullptr) {
					removeChar();
				}
				if (Cursor->next != nullptr) {
					handledelete();
				}
				if (Cursor->prev == nullptr && Cursor->next == nullptr) {
					break;
				}
			}
		}
		void copyfrontstr(string& str, int val) {
			str = "";
			Node* n = Cursor->next;
			for (int i = 0; n != nullptr && n->next != nullptr  && i < val; i++) {
				str += n->data;
				n = n->next;
			}
		}

		void copybackstr(string& str, int val) {
			str = "";
			Node* n = Cursor;
			for (int i = 0; i < val && n->prev != nullptr; i++) {
				n = n->prev;
			}
			while (n->next != nullptr && n != Cursor && n != Cursor) {
				str += n->data;
				n = n->next;
			}
		}

		~Doubly() {
			Node* n = head;
			Node* temp = head;
			while (n != nullptr) {
				n = n->next;
				delete temp;
				temp = n;
			}
		}
		Doubly<T>* clear() {
			Doubly<T>* S1 = new Doubly<T>;
			return S1;
		}
	};
	void byeTime(Doubly<char>& list) {
		system("cls");
		char ch = 'a';
		bool exit = 0;
		bool issaved = false;
		while (exit == 0 && list.getSize() != 0) {
			while (ch != 'y' || ch != 'n') {
			cout << "Do you want to save the current file? (y/n)";
				if (ch == 'n') {
					exit = 1;
				}
				cin >> ch;
				ch = tolower(ch);
				if (ch == 'y') {
					issaved = list.saveFile();
					if (issaved == 1) {
						exit = 1;
						return;
					}
				}
				if (ch == 'n') {
					return;
				}
			}
		}
	}
	string Greet() {
		cout << "Do you want to open a previously saved file ? (y/n) ";
		char ch = 'a';
		while (ch != 'y' || ch != 'n') {
			cin >> ch;
			ch = tolower(ch);
			if (ch == 'y') {
				string name;
				cout << "enter the name of the save file." << endl;
				cin >> name;
				return name;
			}
			else if (ch == 'n') {
				return "";
			}
		}
		return "";
	}
	void bootup() {
		cout << "\t\t\t\t\t\tWelcome to Notepad--" << endl;
		Sleep(1000);
	}
	void handlevk(Doubly<char> &S1) {
		if (GetAsyncKeyState(VK_BACK) & 0x8000) {
			S1.HandleMultipleDeleteThroughBack();
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_DELETE) & 0x8000) {
			S1.HandleMultipleDeleteThroughDelete();
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_LEFT)& 0x8000) {
			S1.HandleControlLeft();
			Sleep(100);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			S1.HandleControlRight();
			Sleep(100);
		}
	}
	void ClearList(Doubly<char> S1) {
		while (S1.getSize() != 0) {
			S1.handledelete();
			S1.removeChar();
		}
	}
	void load(Doubly<char> &S1) {
		string c = Greet();
		if (c != "") {
			char w = 'a';
			ifstream file;
			file.open(c + ".txt");
			if (!file) {
				cout << "wrong name entered. Opening a new text file.\n" << endl;
				Sleep(3000);
			}
			else {
					S1 = *S1.clear();
				while (w != '\0') {
					w = file.get();
					S1.addchar(w);
				}
			}
		}
	}
	int loadfile(bool s) {
		if (s == 1) {
			return 0;
		}
		else {
			cout << "Please save current file." << endl;
			return 19;
		}
		return 0;
	}
	void runapp() {
		Doubly<char> S1;
		bool selectedback = false;
		bool selectedfront = false;
		int front = 0, back = 0;
		load(S1);
		int ch;
		bool saved = 1;
		string str = "";
		while (true) {
			if (front == 0) {
				selectedfront = false;
			}
			if (back == 0)
			{
				selectedback = false;
			}
			S1.print();
			cout << "\n\n\n\n\n\n\t\t\t\t\tSize = " << S1.getSize() << " Position = " << S1.getpos() << endl;
			cout << "selected text = " << str << endl;
			ch = _getch();
			if (ch == 13) {
				ch = '\n';
			}
			else if (ch == 22) {
				for (int i = 0; i < str.length(); i++) {
					S1.addchar(str[i]);
				}
			}
			if (ch == 3) {
				if (selectedback) {
					str = "";
					S1.copybackstr(str, back);
					back = 0;
					continue;
				}
				if (selectedfront) {
					str = "";
					S1.copyfrontstr(str, front);
					front = 0;
					continue;
				}
			}
			else if (ch == 1) {
				char key = _getch();
				if (key == 3) {
					str = S1.savestring();
				}
				if (key == 8) {
					S1.clearall();
				}
				continue;
			}
			else if (ch == 8) {
				S1.removeChar();
				saved = 0;
				continue;
			}

			else if (ch == 12) {
				ch = loadfile(saved);
				if (ch == 0) {
					load(S1);
					continue;
				}
			}
			if (ch == 19) {
				saved = S1.saveFile();
				continue;
			}
			else if (ch == 27) {
				if (saved == 0) {
					byeTime(S1);
				}
				system("cls");
				break;
			}
			if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
				if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
					if (selectedfront == false) {
						back++;
						selectedback = true;
					}
					if (selectedfront == true) {
						front--;
					}
					Sleep(100);
					continue;
				}
				if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
					if (selectedback == false) {
						front++;
						selectedfront = true;
					}
					if (selectedback == true) {
						back--;
					}
					Sleep(100);
					continue;
				}
				Sleep(100);
				continue;
			}
			if (GetAsyncKeyState(VK_CONTROL) & 0x8000) {
				handlevk(S1);
				saved = 0;
				continue;
			}
			else if (ch == 224) {
				int key = _getch();
				if (key == 77) {
					S1.moveCursor(key);
					continue;
				}
				else if (key == 75) {
					S1.moveCursor(key);
					continue;
				}
				else if (key == 72) {
					S1.moveUp();
				}
				else if (key == 80) {
					S1.moveDown();
				}
				else if (key == 83) {
					S1.handledelete();
				}
				saved = 0;
				continue;
			}
			S1.addchar(ch);
			saved = 0;
		}
	}
int main() {
	bootup();
	runapp();
	return 0;
}
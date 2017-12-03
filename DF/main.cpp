#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

class STACK {
	int  *const  elems;	//申请内存用于存放栈的元素
	const  int   max;	//栈能存放的最大元素个数
	int   pos;			//栈实际已有元素个数，栈空时pos=0;
public:
	STACK(int m);		//初始化栈：最多m个元素
	STACK(const STACK&s); 			//用栈s拷贝初始化栈
	virtual int  size() const;			//返回栈的最大元素个数max
	virtual operator int() const;			//返回栈的实际元素个数pos
	virtual int operator[ ] (int x) const;	//取下标x处的栈元素
	virtual STACK& operator<<(int e); 	//将e入栈,并返回栈
	virtual STACK& operator>>(int &e);	//出栈到e,并返回栈
	virtual STACK& operator=(const STACK&s); //赋s给栈,并返回被赋值的栈
	virtual void print() const;			//打印栈
	virtual ~STACK();					//销毁栈
};

STACK::STACK(int m) :max(m), elems(new int[m]), pos(0) {}

STACK::STACK(const STACK&s) : max(s.size()), elems(new int[s.size()]), pos(s.pos) {
	for (int i = 0; i<int(s); i++) {
		*this << s[i];
	}
}

int STACK::size() const {
	return max;
}

STACK::operator int() const {
	return pos;
}

int STACK::operator[](int x) const {
	return*(elems + x);
}

STACK& STACK::operator<<(int e) {
	*(elems + pos++) = e;
	return *this;
}

STACK& STACK::operator>>(int &e) {
	e = *(elems + --pos);
	return *this;
}

STACK& STACK::operator=(const STACK&s) {///////!!!!!unfinished
	if (s.size()>max) {
		delete[]elems;
		*const_cast<int**>(&elems) = new int[s.size()];
		*const_cast<int*>(&max) = s.size();
		for (int i = 0; i<int(s); i++) {
			*this << s[i];
		}
	}
	else {
		pos = 0;
		for (int i = 0; i<int(s); i++) {
			*this << s[i];
		}
	}
	return *this;
}

void STACK::print()const {
	for (int i = 0; i < pos; i++) {
		cout << *(elems + i) << ' ';
	}
}

STACK::~STACK() {
	delete[]elems;
}

class QUEUE :public STACK {
	STACK  s2;
public:
	QUEUE(int m);		//初始化队列：每个栈最多m个元素
	QUEUE(const QUEUE&s); 		//用队列s拷贝初始化队列
	virtual operator int() const;			//返回队列的实际元素个数
	virtual int full() const;
	virtual int operator[](int x) const;
	virtual QUEUE& operator<<(int e); 		//将e入队列,并返回队列
	virtual QUEUE& operator>>(int &e);	//出队列到e,并返回队列
	virtual QUEUE& operator=(const QUEUE&s); //赋s给队列,并返回被赋值的队列
	virtual void print() const;			//打印队列
	virtual ~QUEUE();					//销毁队列
};

QUEUE::QUEUE(int m) :STACK(m), s2(m) {}

QUEUE::QUEUE(const QUEUE& s) : STACK(s.size()), s2(s.s2) {////unifinished
	for (int i = 0; i < s.STACK::operator int(); ++i) {
		STACK::operator<<(s.STACK::operator[](i));
	}
}

QUEUE::operator int() const {///////////
	return STACK::operator int() + int(s2);
}

int QUEUE::full() const {
	if (this->size() == STACK::operator int() && int(s2)>0)return 1;
	return 0;
}

int QUEUE::operator[](int x) const {//////
	if (x<s2)return s2[int(s2) - x - 1];
	else return STACK::operator[](x - int(s2));
}

QUEUE& QUEUE::operator<<(int e) {
	if (this->size() == STACK::operator int() && !int(s2)) {
		int num = STACK::operator int();
		for (int i = 0; i<num; i++) {
			int temp;
			STACK::operator>>(temp);
			s2 << temp;
		}
	}
	STACK::operator<<(e);
	return *this;
}

QUEUE& QUEUE::operator>>(int &e) {
	if (int(s2))s2 >> e;
	else {
		int num = STACK::operator int();
		for (int i = 0; i<num; i++) {
			int temp;
			STACK::operator>>(temp);
			s2 << temp;
		}
		s2 >> e;
	}
	return *this;
}

QUEUE& QUEUE::operator=(const QUEUE& s) {
	for (int i = 0; i<s.STACK::operator int(); i++) {
		STACK::operator<<(s.STACK::operator[](i));
	}
	s2 = s.s2;
	return *this;
}

void QUEUE::print()const {}

QUEUE::~QUEUE() {}

bool check(int n) {
	for (int i = 2; i<n / 2 + 1; i++) {
		if (n%i == 0) {
			return false;
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		int M, F, m, f, manNow, wmanNow, counter;
		do {
			printf("Please input data(M,F,m,f):");
			scanf("%d,%d,%d,%d", &M, &F, &m, &f);
		} while (!(check(M) && check(F) && M != F));

		QUEUE manQueue(M), wmanQueue(F);
		for (int i = 1; i <= M; i++) {
			manQueue << i;
		}
		for (int i = 1; i <= F; i++) {
			wmanQueue << i;
		}
		for (counter = 1;; ++counter) {
			manQueue >> manNow;
			wmanQueue >> wmanNow;
			if (manNow == m&&wmanNow == f)break;
			manQueue << manNow;
			wmanQueue << wmanNow;
		}
		printf("Result:%d\n", counter);
		system("pause");
		return 0;
	}
	else {
		FILE* file;
		char filename[30] = "";
		strcat(filename, argv[0]);
		filename[strlen(filename) - 4] = '\0';
		strcat(filename, ".txt");
		file = fopen(filename, "w");
		QUEUE* queue = new QUEUE(atoi(argv[2]));
		fprintf(file, "S %d", atoi(argv[2]));
		unsigned model = 0;
		for (int i = 3; i<argc; i++) {
			if (argv[i][0] == '-') {
				switch (argv[i][1]) {
				case 'I':model = 0; break;
				case 'O':model = 1; break;
				case 'A': {
					model = 3;
					QUEUE* newQueue = new QUEUE(atoi(argv[i + 1]));
					*newQueue = *queue;
					delete queue;
					queue = newQueue;

					fprintf(file, " A ");
					for (int k = 0; k<*queue; ++k) {
						fprintf(file, "%d", (*queue)[k]);
						if (k != *queue - 1)fprintf(file, " ");
					}
					break;
				}
				case 'C': {
					model = 4;
					QUEUE* newQueue = new QUEUE(*queue);
					delete queue;
					queue = newQueue;
					fprintf(file, " C ");
					for (int k = 0; k<int(*queue); k++) {
						fprintf(file, "%d", (*queue)[k]);
						if (k != *queue - 1)fprintf(file, " ");
					}
					break;
				}
				case 'N': {
					model = 5;
					fprintf(file, " N %d", int(*queue));
					break;
				}
				case 'G': {
					model = 6;
					break;

				}
				}
			}
			else if (argv[i][0] >= '0'&&argv[i][0] <= '9') {
				if (model == 1) {
					fprintf(file, " O ");
					int e;
					bool error = false;
					for (int j = 0; j<atoi(argv[i]); j++) {
						if (int(*queue)) {
							*queue >> e;
						}
						else {
							error = true;
							break;
						}
					}
					if (error) {
						fprintf(file, "E");
						break;
					}
					for (int k = 0; k<int(*queue); ++k) {
						fprintf(file, "%d", (*queue)[k]);
						if (k != *queue - 1)fprintf(file, " ");
					}
				}
				else if (model == 0) {
					fprintf(file, " I ");
					int m = 0;
					for (; m + i<argc - 1; m++) {
						if (argv[m + i + 1][0] == '-') {
							break;
						}
					}
					m++;
					for (int k = 0; k<m; ++k) {
						if (queue->full()) {
							fprintf(file, "E");
							return 0;
						}
						*queue << atoi(argv[k + i]);
					}
					for (int n = 0; n<*queue; ++n) {
						fprintf(file, "%d", (*queue)[n]);
						if (n != *queue - 1)fprintf(file, " ");
					}
					i += m - 1;
				}
				else if (model == 6) {
					fprintf(file, " G ");
					if (atoi(argv[i])<*queue) {
						fprintf(file, "%d", (*queue)[atoi(argv[i])]);
					}
					else fprintf(file, "E");
				}
			}
		}
		fclose(file);
		return 0;
	}
}
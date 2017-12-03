#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

class STACK {
	int  *const  elems;	//�����ڴ����ڴ��ջ��Ԫ��
	const  int   max;	//ջ�ܴ�ŵ����Ԫ�ظ���
	int   pos;			//ջʵ������Ԫ�ظ�����ջ��ʱpos=0;
public:
	STACK(int m);		//��ʼ��ջ�����m��Ԫ��
	STACK(const STACK&s); 			//��ջs������ʼ��ջ
	virtual int  size() const;			//����ջ�����Ԫ�ظ���max
	virtual operator int() const;			//����ջ��ʵ��Ԫ�ظ���pos
	virtual int operator[ ] (int x) const;	//ȡ�±�x����ջԪ��
	virtual STACK& operator<<(int e); 	//��e��ջ,������ջ
	virtual STACK& operator>>(int &e);	//��ջ��e,������ջ
	virtual STACK& operator=(const STACK&s); //��s��ջ,�����ر���ֵ��ջ
	virtual void print() const;			//��ӡջ
	virtual ~STACK();					//����ջ
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
	QUEUE(int m);		//��ʼ�����У�ÿ��ջ���m��Ԫ��
	QUEUE(const QUEUE&s); 		//�ö���s������ʼ������
	virtual operator int() const;			//���ض��е�ʵ��Ԫ�ظ���
	virtual int full() const;
	virtual int operator[](int x) const;
	virtual QUEUE& operator<<(int e); 		//��e�����,�����ض���
	virtual QUEUE& operator>>(int &e);	//�����е�e,�����ض���
	virtual QUEUE& operator=(const QUEUE&s); //��s������,�����ر���ֵ�Ķ���
	virtual void print() const;			//��ӡ����
	virtual ~QUEUE();					//���ٶ���
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
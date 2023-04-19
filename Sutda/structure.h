#pragma once
#include "head.h"

typedef struct {

	int num;
	int sp;

}Card;


typedef struct User{
	
	float money;
	int rank;

	int priority;
	int now_pos;

	std::string name;
	std::string winlose;
	std::string card_call;

	Card hand[2];
	float card_hight;

	void (*functionPtr)(User*&);
	bool Regame;

}User;

typedef struct rule {

	int spx;
	int spy;

	int priority;

	void (*functionPtr_n)(User*&);
	void (*functionPtr_s)(User*&);

	void (*functionPtr)(User*&);
	// �⺻ ������ �Է� �ʱ�ȭ
	rule() : priority(), spx(), spy(), functionPtr_n(nullptr), functionPtr_s(nullptr), functionPtr(nullptr) {}

	// �Լ� �ּҸ� �̸� ����
	void setFunctionPtrs(void (*n)(User*&), void (*s)(User*&)) {

		if (n != nullptr) {
			functionPtr_n = n;
		}
		if (s != nullptr) {
			functionPtr_s = s;
		}
	}
	// �Լ� ���� �� spx�� spy���� ���� �Լ��� �������ش�.
	void updateFunctionPtr() {
		if (spx == 1 && spy == 1) {
			functionPtr = functionPtr_s;
		}
		else {
			functionPtr = functionPtr_n;
		}
	}
}rule;
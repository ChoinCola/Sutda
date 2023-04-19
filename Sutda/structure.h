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
	// 기본 생성자 입력 초기화
	rule() : priority(), spx(), spy(), functionPtr_n(nullptr), functionPtr_s(nullptr), functionPtr(nullptr) {}

	// 함수 주소를 미리 저장
	void setFunctionPtrs(void (*n)(User*&), void (*s)(User*&)) {

		if (n != nullptr) {
			functionPtr_n = n;
		}
		if (s != nullptr) {
			functionPtr_s = s;
		}
	}
	// 함수 선언 시 spx와 spy값에 따라 함수를 지정해준다.
	void updateFunctionPtr() {
		if (spx == 1 && spy == 1) {
			functionPtr = functionPtr_s;
		}
		else {
			functionPtr = functionPtr_n;
		}
	}
}rule;
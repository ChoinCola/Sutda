#include "head.h"

/*
*	설계
* 
	섯다.
	구조체를 사용하여, 해당되는 인원수의 구조체를 생성.
	카드 덱을 구조체를 사용하여 생성.
	new를 사용하여, 동적 배열을 생성하고 연산시킬 수 있다.
	랜덤생성 을 사용하여 카드덱의 구조체에서 원하는 카드를 출력할 수 있다.
	카드는 1 ~ 10 까지의 숫자가 2개씩 존재한다.
	카드의 우선순위 에 따라 유저의 연산순서를 바꾸어야한다.

	
	구조체

	인원 구조체
	인원의 이름
	가지는 카드의 패 [ 카드 포인터 로 구성. ]
	만족한 승리조건의 순위
	자본

	카드 구조체
	카드의 번호
	특수 카드의 여부
	배분이 되었는지 여부


	조건부
	섯다 의 룰에 따른 순위조건을 결정한다.
	광 : 1월, 3월, 8월 에 하나씩 위치한다.

	0 순위 : 3.8광땡[ 3장의 광 중 3광과 8광을 가지고 있을 경우. ] 3:8 sp 1 1
	1 순위 :		{ 광땡 이 있을 경우, 암행어사 가 위치한다. }
	2 순위 : 광땡	[ 3장의 광 중 2개를 가지고있을 경우. ] 1:8, 1:3, sp 1 1
	3 순위 : 장떙	[ 10:10 의 카드가 있을 경우 위치한다.. ] 10:10
	4 순위 : 땡		[ 같은 월 끼리의 조합. 숫자가 클 수록 순위가 올라간다. ] X=Y 10:10은 제외.
	5 순위 : 알리	[ 1월과 2월을 가지고 있을 경우.] 1:2, 2:1
	6 순위 : 독사	[ 1월과 4월을 가지고 있을 경우.] 1:4, 4:1
	7 순위 : 구삥	[ 1월과 9월을 가지고 있을 경우.] 1:9, 9:1
	8 순위 : 장삥	[ 1월과 10월을 가지고 있을 경우.] 1:10, 10:1
	9 순위 : 장사	[ 4월과 10월을 가지고 있을 경우.] 4:10, 10:4
	10 순위 : 세륙	[ 4월과 6월을 가지고 있을 경우.] 4:6, 6:4
	11순위 : 갑오	[ 두 장의 숫자를 합한 수의 끝자리가 9 일 경우.] 1:8, 8:1, 7:2, 2:7, 3:6, 6:3, 4:5, 5:4
	12순위 : 끗		[ 첫 자리 수가 1 ~ 8 일 때 끗 이라고 한다.] 위 조건 제외 모든 칸.
	13순위 : 망통	[ 끗수가 0일때를 말한다.] 위 조건 제외 모든 칸.

	논외 : 땡잡이		[ 3월과 7월의 조합으로 1 ~ 9 땡이 있을 경우, 10땡 바로 밑으로 취급한다. ]  3:7 sp 1 1
		   암행어사		[ 4월과 7월 두개의 동물이 있는 조합으로, 광땡 이 존재하는 경우, 38광땡 바로 밑으로 취급 ] 4:7 sp 1 1
		   구사			[ 4월과 9월의 패로 모든 패 중 최고패 가 알리 이하일 경우, 판에 깔린 돈을 두고 재경기 한다. ] 9:4, 4:9
		   멍텅구리구사	[ 4월의 열자리, 9월의 열자리 로 구땡 이하의 패와 재경기를 한다. ] X4:X9 sp 1 1

	연산부
	조건부에 해당하는 순위대로 연산하고, 각 구조체의 순위 에 기록한다.
	각 순위당 점수가 같을 경우, 무승부 또는 공동순위로 기록한다.

	출력부
	각 인원수 당 카드 패 와 승리조건을 만족한 인원의 승리여부를 출력한다.

	연산과정 예측.
	1. 메인문에서 덱을 제작.
	덱은, 카드 구조체 배열로 제작한다.

	2. 덱의 카드에 숫자와 특수카드 여부를 기입한다.

	3. 인원수를 입력받는다.
	카드의 전체 수는 20장 임으로 인원은 최대 10명이다.

	4. 덱의 순서를 무작위로 섞는다.

	5. 각 인원수 에 카드를 순서대로 분배한다.

	6. 각 인원 간의 배당을 무작위로 기입한다. 해당 범위는 전체금액의 10%를 넘지 않는다.
	
	7. 특수 카드 가 있을 경우 해당 효과를 발휘한다.
	구사, 멍텅구리 구사 가 있을 경우 4로 되돌린다.

	8. 조건부 연산으로 카드에 따른 등수표기를 인원 구조체에 기입한다.

	9. 결과를 출력한다. 결과는 이름	카드	배당	순위	승리여부	를 출력한다.

	10. 유저에게 재경기 여부를 입력받는다.
	
*/
int main()
{
	// 기본변수 생성
	int max_size = DECK_MAX_SIZE / HAND_SIZE;
	float betting = 0;

	// 랜덤 변수 생성
	std::random_device rd;
	std::mt19937 messenne(rd());
	std::uniform_int_distribution<int> randmoney(1, 10);

	// 덱 생성
	Card* deck;
	Make_deck(deck);

	// 조건 표 생성
	rule* map;
	Make_map(map,max_size);
	Insult_rule(map, max_size);

	// 유저 생성
	int how_to_maney;
	while (true) {
		std::cout << "플레이어 의 수를 입력하세요\n";
		std::cin >> how_to_maney;
		std::cin.ignore(); // 입력버퍼 초기화

		if (how_to_maney > 10) {
			system("cls");
			std::cout << "최대 가능 숫자 10명 이하. 재입력 요망!\n";
			_getch();
			system("cls");
		}
		else
			break;
	}

	User* user;
	Make_User(user, how_to_maney, MONEY);

	// 동작 연산
	int count = 0;
	while (true) {

		Suffle(deck, max_size);
		printf("\n");

		// 카드 배분
		for (int i = 0; i < how_to_maney; i++) {
			(user + i)->hand[0] = *(deck + i);
			(user + i)->hand[1] = *(deck + i + 10);
		}

		// 배팅
		float def_bet = 0;
		for (int i = 0; i < how_to_maney; i++) {
			if ((user + i)->money < def_bet) {
				betting += (user + i)->money;
				(user + i)->money = 0;
			}
			else {
				def_bet = ceil((user + i)->money * randmoney(messenne) * 0.01);
				(user + i)->money -= def_bet;
				betting += def_bet;
			}
		}

		// 카드 주소값데이터를 유저 데이터에 삽입
		for (int i = 0; i < how_to_maney; i++) {
			User* def = user + i;
			Chack_rule_User(map , def , max_size);
		}

		// 데이터 순차 연산용 def 제작.
		User** def = new User*[how_to_maney];

		// 주소값 대입
		for (int i = 0; i < how_to_maney; i++) {
			*(def + i) = (user + i);
		}

		// 연산 우선순위에 따라 데이터를 재배열한다.
		std::sort(def, (def + how_to_maney-1), compare);

		// 데이터 연산
		for (int i = 0; i < how_to_maney; i++) {
			def[i]->functionPtr(def[i]);
		}
		
		// 승자 연산
		Winer_Chack(user);
		
		// 결과 후 정산.
		std::cout << "\n배당금 :" << betting << "\n";
		Take_My_Money(user, &betting);

		Print_ALL(user, how_to_maney);
		Reset(user);
		if (Aigo_Chack(user, &betting))
			break;
		_getch();
		free(def);
	}
	return 0;
}
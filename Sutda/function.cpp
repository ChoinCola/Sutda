#include "head.h"

auto Make_deck(Card* &deck) -> void
{
	Card* result = new Card[20] ;
	
	// µ¦ ±¸¼º
	for (int i = 0; i < 10; i++) {

		result[i].num = i;
		result[i].sp = 0;

		result[i + 10].num = i;
		result[i + 10].sp = 1;
	}

	deck = result;
}

auto Suffle(Card* &deck, int max_size) -> void
{
	std::random_device rd;
	std::mt19937 messenne(rd());
	std::uniform_int_distribution<int> randNUJm(0, 19);

	Card def;

	int c1;
	int c2;

	for (int i = 0; i < 10000; i++) {
		c1 = randNUJm(messenne);
		c2 = randNUJm(messenne);
		def = *(deck + c1);
		*(deck + c1) = *(deck + c2);
		*(deck + c2) = def;
	}
}

auto Make_User(User* &user, int max_size, int money) -> void
{
	User* def = new User[max_size+1];

	for (int i = 0; i < max_size; i++) {
		std::string name;
		std::cout << "\nÀÌ¸§ À» ÀÔ·ÂÇÏ¼¼¿ä : ";
		std::getline(std::cin, (def+i)->name);
		(def + i)->money = money;
		(def + i)->now_pos = i;
		(def + i)->Regame = false;
		(def + i)->winlose = "ÆÐ¹è";
	}
	def[max_size].priority = NULL;

	user = def;
}

auto Print_ALL(User* &user, int max_size) -> void
{
	for (int i = 0; i < max_size; i++) {
		std::cout << "\n" << (user + i)->name <<
			"\tÀÚº» : " << (user + i)->money << "¿ø" << "  ";

		std::cout << "ÆÐ: " << "\t";
		for (int j = 0; j < 2; j++) {
			std::cout << (user + i)->hand[j].num+1 << " ";
		}

		std::cout << "\t" << (user + i)->card_call;
		std::cout << "\t" << (user + i)->winlose;
	}
}
#pragma region ¿¬»êÇÔ¼ö
// ºÐ·ù ÇÔ¼ö Á¦ÀÛ.
auto three_eight(User*& user) -> void
{
	user->rank = 0;
	user->card_call = "3.8±¤¶¯";
	Card_hight(user);
}

auto Guang_Ding(User*& user) -> void
{
	user->rank = 2;
	std::string text = std::to_string(user->hand[0].num + 1) + "." + std::to_string(user->hand[1].num + 1) + "±¤¶¯";
	user->card_call = text;
	Card_hight(user);
}

auto Jang_Ding(User*& user) -> void
{
	user->rank = 3;
	std::string text = "Àå¶¯";
	user->card_call = text;
	Card_hight(user);
}

auto Ding(User*& user) -> void
{
	user->rank = 4;
	std::string text = std::to_string(user->hand[0].num + 1) + "¶¯";
	user->card_call = text;
	Card_hight(user);
}

auto Ali(User*& user) -> void
{
	user->rank = 5;
	user->card_call = "¾Ë¸®";
	Card_hight(user);
}

auto Doksa(User*& user) -> void
{
	user->rank = 6;
	user->card_call = "µ¶»ç";
	Card_hight(user);
}

auto Gu_Ping(User*& user) -> void
{
	user->rank = 7;
	user->card_call = "±¸»æ";
	Card_hight(user);
}

auto Jang_Ping(User*& user) -> void
{
	user->rank = 8;	
	user->card_call = "Àå»æ";
	Card_hight(user);
}

auto Jang_Sa(User*& user) -> void
{
	user->rank = 9;
	user->card_call = "Àå»ç";
	Card_hight(user);
}

auto Se_Ruc(User*& user) -> void
{
	user->rank = 10;
	user->card_call = "¼¼·ú";
	Card_hight(user);
}

auto Gab_O(User*& user) -> void
{
	user->rank = 11;
	user->card_call = "°©¿À";
	Card_hight(user);
}

auto KKeus(User*& user) -> void
{
	user->rank = 12;
	std::string text = std::to_string((user->hand[0].num + user->hand[1].num + 2) % 10) + "²ý";
	user->card_call = text;
	Card_hight(user);
}

auto Mang_tong(User*& user) -> void
{
	user->rank = 13;
	user->card_call = "¸ÁÅë";
	Card_hight(user);
}

auto Catcher(User*& user) -> void
{
	user->rank = 13;
	user->card_call = "¶¯ÀâÀÌ";
	user->card_hight = 0;
	int c = 0;

	User* def = user - user->now_pos;

	while ((def + c)->money != NULL)
	{
		if (Chack_Ding(def + c)) {
			user->rank = 4;
			user->card_hight = 9.1;
			break;
		}
		c++;
	}
}

auto Amhaeng_Eosa(User*& user) -> void
{
	user->rank = 12;
	user->card_call = "¾ÏÇà¾î»ç";
	user->card_hight = 1;

	int c = 0;

	User* def = user - user->now_pos;

	while ((def + c)->priority != NULL)
	{
		if (Chack_T_A_Ding(def + c)) {
			user->rank = 0;
			user->card_hight = 1;
			break;
		}
		c++;
	}
}

auto Gusa(User*& user) -> void
{
	user->rank = 12;
	user->card_call = "±¸»ç";
	Card_hight(user);
	user->Regame = true;

	int c = 0;

	User* def = user - user->now_pos;

	while ((def + c)->priority != NULL)
	{
		if (Chack_Ali(def + c)) {
			user->Regame = false;
			break;
		}
		c++;
	}
}

auto Meongteong_Guli_Gusa(User*& user) -> void
{
	user->rank = 13;
	user->card_call = "¸ÛÅÖ±¸¸® ±¸»ç";
	Card_hight(user);
	user->Regame = true;

	int c = 0;

	User* def = user - user->now_pos;

	while ((def + c)->priority != NULL)
	{
		if (Chack_Meongteong(def + c)) {
			user->Regame = false;
			break;
		}
		c++;
	}
}

auto Chack_Ding(User* user) -> int
{
	if (user->hand[0].sp == 1 && user->hand[1].sp == 1 && user->hand[0].num == user->hand[1].num)
		return 1;
	return 0;
}

auto Chack_T_A_Ding(User* user) -> int
{
	if	(user->hand[0].sp == 1 && user->hand[1].sp == 1 &&
		(user->hand[0].num == 3 || user->hand[0].num == 8) &&
		(user->hand[1].num == 3 || user->hand[1].num == 8))
		return 1;
	return 0;
}

auto Chack_Ali(User* user) -> int
{
	if (user->rank < 5)
		return 1;
	return 0;
}

auto Chack_Meongteong(User* user) -> int
{
	if (user->rank < 4)
		return 1;
	return 0;
}
#pragma endregion ¿¬»êÇÔ¼ö

auto Make_map(rule*& map, int max_size) -> void
{
	rule* def = new rule[max_size * max_size];
	map = def;
}

auto Insult_rule(rule*& map, int max_size) -> void
{
	for (int i = 0; i < max_size; i++) {
		for (int j = 0; j < max_size; j++) {
			(map + i * max_size + j)->priority = 0;
			// ²ý
			(map + i * max_size + j)->setFunctionPtrs(&KKeus, &KKeus);
			// ¸ÁÅë
			if ((i + j + 2) % 10 == 0) {
				(map + i * max_size + j)->setFunctionPtrs(&Mang_tong, &Mang_tong);
			}
			// °©¿À
			if ((i + j + 2) % 10 == 9) {
				(map + i * max_size + j)->setFunctionPtrs(&Gab_O, &Gab_O);
			}
			// ¼¼·ú
			if ((i + 1 == 6 && j + 1 == 4) || (i + 1 == 4 && j + 1 == 6)) {
				(map + i * max_size + j)->setFunctionPtrs(&Se_Ruc, &Se_Ruc);
			}
			// Àå»ç
			if ((i + 1 == 4 && j + 1 == 10) || (i + 1 == 10 && j + 1 == 4)) {
				(map + i * max_size + j)->setFunctionPtrs(&Jang_Sa, &Jang_Sa);
			}
			// Àå»æ
			if ((i + 1 == 1 && j + 1 == 10) || (i + 1 == 10 && j + 1 == 1)) {
				(map + i * max_size + j)->setFunctionPtrs(&Jang_Ping, &Jang_Ping);
			}
			// ±¸»æ
			if ((i + 1 == 1 && j + 1 == 9) || (i + 1 == 9 && j + 1 == 1)) {
				(map + i * max_size + j)->setFunctionPtrs(&Gu_Ping, &Gu_Ping);
			}
			// µ¶»ç
			if ((i + 1 == 1 && j + 1 == 4) || (i + 1 == 4 && j + 1 == 1)) {
				(map + i * max_size + j)->setFunctionPtrs(&Doksa, &Doksa);
			}
			// ¾Ë¸®
			if ((i + 1 == 1 && j + 1 == 2) || (i + 1 == 2 && j + 1 == 1)) {
				(map + i * max_size + j)->setFunctionPtrs(&Ali, &Ali);
			}
			// ¶¯
			if (i == j) {
				(map + i * max_size + j)->setFunctionPtrs(&Ding, &Ding);
			}

			// ±¤¶¯
			if ((i + 1 == 1 && j + 1 == 8) || (i + 1 == 1 && j + 1 == 3) ||
				(i + 1 == 8 && j + 1 == 1) || (i + 1 == 3 && j + 1 == 1)) {
				(map + i * max_size + j)->setFunctionPtrs(nullptr, &Guang_Ding);
			}
		}
	}
	// 3.8±¤¶¯
	(map + 2 * max_size + 7)->setFunctionPtrs(nullptr, &three_eight);
	(map + 7 * max_size + 2)->setFunctionPtrs(nullptr, &three_eight);
	// ¶¯ÀâÀÌ
	(map + 2 * max_size + 6)->setFunctionPtrs(nullptr, &Catcher);
	(map + 6 * max_size + 2)->setFunctionPtrs(nullptr, &Catcher);
	(map + 2 * max_size + 6)->priority = 2;
	(map + 2 * max_size + 6)->priority = 2;
	// ¾ÏÇà¾î»ç
	(map + 3 * max_size + 6)->setFunctionPtrs(nullptr, &Amhaeng_Eosa);
	(map + 6 * max_size + 3)->setFunctionPtrs(nullptr, &Amhaeng_Eosa);
	(map + 3 * max_size + 6)->priority = 2;
	(map + 6 * max_size + 3)->priority = 2;
	// ±¸»ç & ¸ÛÅÖ±¸¸® ±¸»ç
	(map + 3 * max_size + 8)->setFunctionPtrs(&Gusa, &Meongteong_Guli_Gusa);
	(map + 8 * max_size + 3)->setFunctionPtrs(&Gusa, &Meongteong_Guli_Gusa);
	(map + 3 * max_size + 8)->priority = 1;
	(map + 8 * max_size + 3)->priority = 1;
}

auto Chack_rule_User(rule*& map, User*& user, int max_size) -> void
{
	(map + user->hand[0].num * max_size + user->hand[1].num)->spx = user->hand[0].sp;
	(map + user->hand[0].num * max_size + user->hand[1].num)->spy = user->hand[1].sp;
	(map + user->hand[0].num * max_size + user->hand[1].num)->updateFunctionPtr();

	user->functionPtr = (map + user->hand[0].num * max_size + user->hand[1].num)->functionPtr;
}

auto compare(User* a, User* b) -> bool {
	return a->priority < b->priority;
}

auto Winer_Chack(User*& user) -> void
{
	int count = 0;
	bool draw = false;
	bool Regame = false;
	User* def = user;
	// ½ÂÀÚ È®ÀÎ
	while ((user + count)->priority != NULL) {
		if (def->rank > (user + count)->rank)
			def = (user + count);
		else if(def->rank == (user + count)->rank && def->card_hight < (user + count)->card_hight)
			def = (user + count);
		count++;
	}
	// ¹«½ÂºÎ ºñ±³
	count = 0;
	while ((user + count)->priority != NULL) {
		if (def->rank == (user + count)->rank && def->card_hight == (user + count)->card_hight && def != (user + count)) {
			def->winlose = "¹«½ÂºÎ";
			(user + count)->winlose = "¹«½ÂºÎ";
			draw = true;
		}

		if ((user + count)->Regame || def->Regame) {
			Regame = true;
			break;
		}
		count++;
	}
	if (Regame) {
		int count = 0;
		while ((user + count)->priority != NULL) {
			(user + count)->winlose = "Àç°æ±â";
			count++;
		}
	}
	else if(!draw)
		def->winlose = "½Â¸®";
}

auto Reset(User*& user) -> void
{
	int count = 0;
	while ((user + count)->priority != NULL) {
		(user + count)->winlose = "ÆÐ¹è";
		(user + count)->Regame = false;
		count++;
	}
}

auto Card_hight(User*& user) -> void
{
	user->card_hight = (user->hand[0].num + user->hand[1].num + 2) % 10;
}

auto Take_My_Money(User*& user, float* betting) -> bool
{
	int count = 0;
	int draw_count = 0;

	bool draw = false;
	bool Regame = false;

	// ÀÎ¿ø°£ÀÇ ½Â¸® ¹«½ÂºÎ Àç°æ±â¸¦ ÆÄ¾Ç
	while ((user + count)->priority != NULL) {
		if ((user + count)->winlose == "½Â¸®") {
			(user + count)->money += *betting;
			*betting = 0;
			break;
		}
		else if ((user + count)->winlose == "¹«½ÂºÎ") {
			draw = true;
			draw_count++;
		}
		else if ((user + count)->winlose == "Àç°æ±â") {
			Regame = true;
			break;
		}
		count++;
	}
	if (draw) {
		while ((user + count)->priority != NULL) {
			if ((user + count)->winlose == "¹«½ÂºÎ") {
				(user + count)->money += ceil(*betting / draw_count);
			}
		}
		*betting = 0;
	}
	return Regame;
}

auto Aigo_Chack(User*& user, float* betting) -> bool
{
	int count = 0;
	while ((user + count)->priority != NULL) {
		if ((user + count)->money == 0 && betting == 0)
			return true;
		count++;
	}
	return false;
}
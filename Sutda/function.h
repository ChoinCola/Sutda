#pragma once
// 연산부
auto Make_deck(Card*& deck) -> void;
auto Suffle(Card*& deck, int max_size) -> void;
auto Make_User(User*& user, int max_size, int money) -> void;
auto Print_ALL(User*& user, int max_size) -> void;
// 조건부
auto three_eight(User*& user) -> void;
auto Guang_Ding(User*& user) -> void;
auto Jang_Ding(User*& user) -> void;
auto Ding(User*& user) -> void;
auto Ali(User*& user) -> void;
auto Doksa(User*& user) -> void;
auto Gu_Ping(User*& user) -> void;
auto Jang_Ping(User*& user) -> void;
auto Jang_Sa(User*& user) -> void;
auto Se_Ruc(User*& user) -> void;
auto Gab_O(User*& user) -> void;
auto KKeus(User*& user) -> void;
auto Mang_tong(User*& user) -> void;
auto Catcher(User*& user) -> void;
auto Amhaeng_Eosa(User*& user) -> void;
auto Gusa(User*& user) -> void;
auto Meongteong_Guli_Gusa(User*& user) -> void;

auto Chack_Ding(User* user) -> int;
auto Chack_T_A_Ding(User* user) -> int;
auto Chack_Ali(User* user) -> int;
auto Chack_Meongteong(User* user) -> int;

auto Make_map(rule*& map, int max_size) -> void;
auto Insult_rule(rule*& map, int max_size) -> void;
auto Chack_rule_User(rule*& map, User*& user, int max_size) -> void;
auto compare(User* a, User* b) -> bool;
auto Winer_Chack(User*& user) -> void;
auto Reset(User*& user) -> void;
auto Card_hight(User*& user) -> void;
auto Take_My_Money(User*& user, float* betting) -> bool;
auto Aigo_Chack(User*& user, float* betting) -> bool;
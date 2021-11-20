#pragma once
#include <iostream>
#include <string>
#include <chrono>

enum StrategyType { RNDSTR, FIRSTSTR, SCORESTR, MINIMAXSTR, MONTECARLO, ALLTHREE, MMTREE};
enum runType { CODINGAME, ONEONONE };


constexpr int mmDEPTH = 4;
constexpr int TREETIMELIMIT = 185;

constexpr int mcDEPTH = 5;
constexpr double mcTIME = 9.0;

constexpr int EMPTY = 0;
constexpr int KRIZEC = 1;
constexpr int KROZEC = 2;
constexpr int DRAW = 3;
constexpr int TL = 2;
constexpr int TC = 4;
constexpr int TR = 6;
constexpr int CL = 8;
constexpr int CC = 10;
constexpr int CR = 12;
constexpr int BL = 14;
constexpr int BC = 16;
constexpr int BR = 18;
constexpr int HUGENUM = 1000000000;

const int  sbn[3][3] = { { 1,2,3 },{ 4,5,6 },{ 7,8,9 } };
const int posl[3][3] = { { TL,TC,TR },{ CL,CC,CR },{ BL,BC,BR } };
const int bnCols[10] = { -1,0,3,6,0,3,6,0,3,6 };
const int bnRows[10] = { -1,0,0,0,3,3,3,6,6,6 };

const int poRows[10] = { -1,0,0,0,1,1,1,2,2,2 };
const int poCols[10] = { -1,0,1,2,0,1,2,0,1,2 };

int Other(int player);

std::string prn(int state);

int RandomNumber(int N);

void FakeRead();

bool GetMyHis(int grow, int &my, int &his, int &lp);

std::ostream &operator<<(std::ostream &os, StrategyType st);
#ifndef _QIAOPAI_H_
#define _QIAOPAI_H_ 

typedef int* POKER;
typedef struct SWanJia* WANJIA;
typedef int PAI;

//按照给的牌数返回洗好的牌，动态分配内存，需要到计分时释放 ，paiShu: 需要几张牌 
POKER XiPai(int paiShu);

//按照给的人数动态内存分配并初始化玩家， renShu : 有几个玩家 
WANJIA ChuShiHuaPaiJu(int renShu, int paiShu);

//把牌分给牌局中的玩家 
////poker: 所有牌 paiShu: 一共有多少牌 paiJu: 当前牌局 renShu: 几个玩家 ，
void FenPai(POKER poker, int paiShu, WANJIA paiJu, int renShu);

//显示剩余的所有牌，还有几张，每个玩家剩下的都是什么牌 ，几张 
//poker: 所有牌 paiShu: 一共有多少牌 paiJu: 当前牌局 renShu: 几个玩家 
void XianPai(POKER poker, int paiShu, WANJIA paiJu, int renShu);

//paiJu: 当前牌局 renShu: 几个玩家 ，得出庄家，将牌，定约  返回庄家是谁 
int JiaoPai(WANJIA paiJu, int renShu, int *zhuangJia, int *jiangPai, int *dingYue);

//paiJu: 当前牌局 wanJia: 轮到谁出牌， 返回当前玩家出的牌 
PAI ChuPai(WANJIA paiJu, int wanJia, PAI pai[], int xianChuPai);

//paiJu: 当前牌局 wanJia: 轮到谁出牌， 返回当前玩家出的牌 自动出牌 
PAI ZiDongChuPai(WANJIA paiJu, int wanJia, PAI pai[], int xianChuPai);

//pai: 一圈人出的牌 renShu:几个人出牌 xianChu: 谁先出的, 返回谁的牌最大 
int SheiPaiDa(WANJIA paiJu, PAI* pai, int renShu, int xianChu, int jiangPai);

// poker: 所有牌 paiJu: 当前牌局 renShu: 几个玩家
// zhuangJia: 这一局的庄家 jiangPai: 这一局的将牌 dingYue: 这一局的定约 
void DeFen(POKER poker, WANJIA paiJu, int renShu, int zhuangJia, int jiangPai, int dingYue);

void DuPaiMing(int pai);

#endif
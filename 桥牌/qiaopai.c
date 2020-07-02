#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>
#include <stdbool.h>
#include "qiaopai.h"

struct SWanJia{
	bool *g_poker;
	char g_name[11];
	int g_paiShu;
	int g_dun;
};

//牌面数字 
enum EPaiNumber{TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE};
				
//牌面花色和无将				
enum EPaiHua{MEIHUA, FANGKUAI, HONGTAO, HEITAO};

//按照给的牌数返回洗好的牌，动态分配内存，需要到计分时释放 ，paiShu: 需要几张牌 
POKER XiPai(int paiShu)
{
	POKER poker = (POKER)malloc(sizeof(int) * paiShu);
	bool judge[paiShu];
	srand(time(0));
	int i, tmp;
	for(i = 0; i < paiShu; i++)
	{
		judge[i] = true;
	}
	
	for(i = 0; i < paiShu; i++)
	{
		tmp = rand() % paiShu;
		while(judge[tmp] == false)
		{
			tmp++;
			if(tmp == paiShu)
			{
				tmp = 0;
			}
		}
		poker[i] = tmp;
		judge[tmp] = false;
	}
	
	return poker;
}

//按照给的人数动态内存分配并初始化玩家， renShu : 有几个玩家 
WANJIA ChuShiHuaPaiJu(int renShu, int paiShu)
{
	WANJIA paiJu = (WANJIA)malloc(sizeof(struct SWanJia) * renShu);
	int i, j;
	for(i = 0; i < renShu; i++)
	{
		paiJu[i].g_poker = (bool *)malloc(sizeof(bool) * paiShu);
		for(j = 0; j < paiShu; j++)
		{
			paiJu[i].g_poker[j] = false;
		}
		paiJu[i].g_dun = 0;
		paiJu[i].g_paiShu = 0;
		printf("请输入玩家%d的名字（不超过10位的英文字符不可以有空格）：", i);
		scanf("%10s", paiJu[i].g_name );
	}
	
	return paiJu;
}

//把牌分给牌局中的玩家 
////poker: 所有牌 paiShu: 一共有多少牌 paiJu: 当前牌局 renShu: 几个玩家 
void FenPai(POKER poker, int paiShu, WANJIA paiJu, int renShu)
{
	int i, j;
	int count = paiShu / renShu;
	for(i = 0 ; i < count; i++)
	{
		for(j = 0; j < renShu; j++)
		{
			paiJu[j].g_poker[poker[i*renShu+j]] = true;
			paiJu[j].g_paiShu += 1;
		}
	}
	return;
}

//显示剩余的所有牌，还有几张，每个玩家剩下的都是什么牌 ，几张 
//poker: 所有牌 paiShu: 一共有多少牌 paiJu: 当前牌局 renShu: 几个玩家 
void XianPai(POKER poker, int paiShu, WANJIA paiJu, int renShu)
{
	int i, j , count;
	printf("*******************************************************\n");
	printf("所有人剩下的牌是：\n"); 
	for(i = 0, count = 0; i < paiShu; i++)
	{
		if(i != 0 && i % 13 == 0)
		{
			printf("\n");
		}
		if(poker[i] != -1)
		{
			DuPaiMing(i);
			printf("  ");
			count++;
		}
	}
	printf("一共还剩下%d张牌\n\n", count);
	for(i = 0; i < renShu; i++)
	{
		printf("玩家%d：%s剩下的牌是：\n", i, paiJu[i].g_name);
		for(j = 0, count = 0; j < paiShu; j++)
		{
			if(j != 0 && j % 13 == 0)
			{
				printf("\n");
			}
			if(paiJu[i].g_poker[j] == true)
			{
				DuPaiMing(j);
				printf("  ");
				count++;
			}
		}
		printf("一共还剩下%d张牌\n\n", count);
	}
	printf("*******************************************************\n");
	return; 
}

//paiJu: 当前牌局 renShu: 几个玩家 ，得出庄家，将牌，定约  返回庄家是谁 
int JiaoPai(WANJIA paiJu, int renShu, int *zhuangJia, int *jiangPai, int *dingYue)
{
	*zhuangJia = 0;
	*jiangPai = MEIHUA;
	*dingYue = 6;
	printf("************************************************\n"); 
	printf("庄家是玩家0,将牌是梅花,定约是6.\n");
	printf("************************************************\n");
	return 0;
}

//paiJu: 当前牌局 wanJia: 轮到谁出牌， 返回当前玩家出的牌 
PAI ChuPai(WANJIA paiJu, int wanJia, PAI pai[], int xianChuPai)
{
	
	printf("请玩家%d:%s出牌: ", wanJia, paiJu[wanJia].g_name);
	char chuPai[100];
	bool shuRuCuoWu;
	PAI p = 1;
	do{
		shuRuCuoWu = false;
		scanf("%s", chuPai);
		if(strlen(chuPai) != 2)
		{
			shuRuCuoWu = true;//输入字符串长度错误 
		}
		else
		{
			//把输入的字符串转换成代表牌的数字 
			switch(chuPai[0])
			{
				case 'c': p = 0; break;
				case 'd': p = 13; break;
				case 'h': p = 26; break;
				case 's': p = 39; break;
				default : shuRuCuoWu = true;
			}
			if(chuPai[1] >= '2' && chuPai[1] <= '9')
			{
				p += chuPai[1] - '2';
			}
			else
			{
				switch(chuPai[1])
				{
					case 't': p += 8; break;
					case 'j': p += 9; break;
					case 'q': p += 10; break;
					case 'k': p += 11; break;
					case 'a': p += 12; break;
					default : shuRuCuoWu = true;
				}
			}
			
			//输入字符串在合理范围
			if(shuRuCuoWu == false)
			{
				 //玩家如果有这张牌 
				if(paiJu[wanJia].g_poker[p] == true)
				{
					//玩家即不是先出也不与先出的花色一致，判定是是否有先出花色的牌
					if((wanJia != xianChuPai) && (pai[xianChuPai]/13 != p/13))
					{
						int i = pai[xianChuPai] / 13 * 13, j = i+13;
						for(i; i < j; i++)
						{
							if(paiJu[wanJia].g_poker[i] == true) 
							{
								shuRuCuoWu = true;
								break;
							}
						}
					}
				}
				else
				{
					shuRuCuoWu = true;
				}	
			}
		}
		if(shuRuCuoWu == false)
		{
			paiJu[wanJia].g_poker[p] = false;
			paiJu[wanJia].g_paiShu--;
			printf("玩家%d:%s出的牌是:", wanJia, paiJu[wanJia].g_name);
			DuPaiMing(p);
			printf("\n");
		}
		else
		{
			printf("输入错误!请重新输入:");
		}
	}while(shuRuCuoWu);
	
	return p;
}

PAI ZiDongChuPai(WANJIA paiJu, int wanJia, PAI pai[], int xianChuPai)
{
	int i;
	printf("玩家%d:%s出的牌是:", wanJia, paiJu[wanJia].g_name);
	//如果不是先出，出和先出一样的花色 
	if(wanJia != xianChuPai)
	{
		int tongHuaTou = pai[xianChuPai]/13*13;
		for(i = pai[xianChuPai]/13*13 + 12; i >= tongHuaTou; i--)
		{
			if(paiJu[wanJia].g_poker[i] == true)
			{
				paiJu[wanJia].g_poker[i] = false;
				DuPaiMing(i);
				printf("\n");
				return i;
			}
		}
	}
		
	for(i = 51; i >= 0; i--)
	{
		if(paiJu[wanJia].g_poker[i] == true)
		{
			paiJu[wanJia].g_poker[i] = false;
			DuPaiMing(i);
			printf("\n");
			return i;
		}
	}
}

//pai: 一圈人出的牌 renShu:几个人出牌 xianChu: 谁先出的, 返回谁的牌最大 
int SheiPaiDa(WANJIA paiJu, PAI* pai, int renShu, int xianChu, int jiangPai)
{
	int big = xianChu, i, houChu = xianChu + 1;
	for(i = 0; i < 3; i++, houChu++)
	{
		houChu %= renShu;
		if(pai[houChu]/13 == pai[big]/13)
		{
			if(pai[houChu] > pai[big])
			{
				big = houChu;
			}
		}
		else if(pai[houChu]/13 == jiangPai)
		{
			if(pai[big]/13 != jiangPai 
				|| (pai[big]/13 == jiangPai && pai[houChu] > pai[big]))
			{
				big = houChu;
			}
		}
	}
	paiJu[big].g_dun++;
	return big;
}

// poker: 所有牌 paiJu: 当前牌局 renShu: 几个玩家
// zhuangJia: 这一局的庄家 jiangPai: 这一局的将牌 dingYue: 这一局的定约 
void DeFen(POKER poker, WANJIA paiJu, int renShu, int zhuangJia, int jiangPai, int dingYue)
{
	if(poker != NULL)
	{
		free(poker);
	}
	else
	{
		printf("释放内存失败！！！");
		exit(1);
	}
	int yingDun = paiJu[zhuangJia].g_dun + paiJu[(zhuangJia + 2)%renShu].g_dun;
	int i = 0;
	for(i; i < renShu; i++) 
	{
		if(paiJu[i].g_poker != NULL)
		{
			free(paiJu[i].g_poker);
			paiJu[i].g_poker = NULL;
		}
		else
		{
			printf("释放内存失败！！！");
			exit(1);
		}
	}
	printf("定约是：%d墩, 赢了%d墩!\n", dingYue, yingDun);
	return;
}

//把数字转换成花色和数字的叫法 
void DuPaiMing(int pai)
{
	if(pai < 0)
	{
		printf("牌面输入错误！！！");
		exit(1) ;
	}
	pai %= 54;
	if(pai > 51)
	{
		if(pai == 52)
		{
			printf("小王"); 
		}
		else
		{
			printf("大王");
		}
	}
	else
	{
		int hua = pai / 13, number = pai % 13;
		switch (hua)
		{
			case MEIHUA  : printf("梅花"); break;
			case FANGKUAI: printf("方块"); break;
			case HONGTAO : printf("红桃"); break;
			case HEITAO  : printf("黑桃"); break;
		}
		
		switch (number)
		{
			case TWO  : printf("2") ; break;
			case THREE: printf("3") ; break;
			case FOUR : printf("4") ; break;
			case FIVE : printf("5") ; break;
			case SIX  : printf("6") ; break;
			case SEVEN: printf("7") ; break;
			case EIGHT: printf("8") ; break;
			case NINE : printf("9") ; break;
			case TEN  : printf("10"); break;
			case JACK : printf("J") ; break;
			case QUEEN: printf("Q") ; break;
			case KING : printf("K") ; break;
			case ACE  : printf("A") ; break;
		}
	}
	return;	
}
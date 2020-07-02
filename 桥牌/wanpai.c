#include <stdio.h>
#include <stdlib.h>
#include "qiaopai.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	int paiShu = 52, renShu = 4;
	int zhuangJia, jiangPai, dingYue, quanYingJia;
	
	POKER poker = XiPai(paiShu);         //动态内存分配出一副牌，记得释放 
	
	WANJIA paiJu = ChuShiHuaPaiJu(renShu, paiShu);   //动态内存分配并初始化四个玩家，
	
	FenPai(poker, paiShu, paiJu, renShu);     //把扑克分给牌局中的玩家
	
	XianPai(poker, paiShu, paiJu, renShu);    //显示各个玩家和总共还剩什么牌 
	
	quanYingJia = JiaoPai(paiJu, renShu, &zhuangJia, &jiangPai, &dingYue);
	
	int i, j, k;
	PAI pai[renShu];          //一张单牌，和一圏的4张牌 
	for(i = 0; i < paiShu/renShu; i++)
	{
		printf("c,d,h,s分别代表：梅花,方块,红桃,黑桃。\n");
		printf("数字2~9代表点数2~9，t,j,q,k,a分别代表：10，J，Q，K，A。\n");
		printf("例如h2代表红桃2，sa代表黑桃A!\n");
		//从上一圈的赢家开始出牌 
		for(j = 0, k = quanYingJia; j < renShu; j++, k++)
		{
			k %= renShu;
			if(k == zhuangJia || k == (zhuangJia + 2) % renShu) 
			{
				pai[k] = ChuPai(paiJu, k, pai, quanYingJia);
			}
			else
			{
				pai[k] = ZiDongChuPai(paiJu, k, pai, quanYingJia);
			}
			poker[pai[k]] = -1;
		}
		//判断这圈谁是赢家 
		quanYingJia = SheiPaiDa(paiJu, pai, renShu, quanYingJia, jiangPai);
		
		//显示各个玩家和总共还剩什么牌 
		XianPai(poker, paiShu, paiJu, renShu);
	}
	
	DeFen(poker, paiJu, renShu, zhuangJia, jiangPai, dingYue);  // 计算得分，并析构扑克和牌局 
		
	return 0;
}
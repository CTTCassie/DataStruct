#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	int i=1;
	int input=0;
	int count=0;   //控制游戏执行的次数
	int random=0;
	while(i)
	{
		printf("********欢迎来到猜数字游戏*********\n");
		printf("请输入您的选择:1.开始游戏0.退出游戏\n");
		scanf("%d",&i);
		switch(i)
		{
		case 1:
			srand((unsigned int)time(NULL));
			random=rand()%101;
			count=0;
			while(count < 10)
			{
				printf("请输入一个您猜测的数字在1-100之间:\n");
				scanf("%d",&input);
				if(input == random)
				{
					printf("恭喜您，猜对了\n");
					break;
				}
				else if(input > random)
				{
					count++;
					printf("猜大了\n");
				}
				else
				{
					count++;
					printf("猜小了\n");
				}
			}
			if(count == 10)
			{
				printf("您的机会已用完,游戏结束\n");
			}
			break;
		case 0:
			break;
		default:
			printf("您的选择错误\n");
			break;
		}
	}
	system("pause");
	return 0;
}
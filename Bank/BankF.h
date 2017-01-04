#define _CRT_SECURE_NO_WARNINGS 1 

const int MAXPROCESS=100;
const int MAXRESOURCE=100; 

int Available[MAXRESOURCE];         //可用资源向量  
int Max[MAXPROCESS][MAXRESOURCE];   //最大需求矩阵  
int Allocation[MAXPROCESS][MAXRESOURCE];  //分配矩阵  
int Need[MAXPROCESS][MAXRESOURCE];        //需求矩阵  

int Request[MAXRESOURCE];      //请求向量  
 
int Work[MAXRESOURCE];         //工作向量  
bool Finish[MAXPROCESS]; 
int SafeSeries[MAXPROCESS];    //安全序列  

int n;   //进程数  
int m;   //资源数  

void Init()  
{  
	cout<<"请输入进程总数>";  
	cin>>n;
	cout<<"请输入资源种类数>";  
	cin>>m;
	int i,j;  
	printf("请输入%d类资源的当前可利用资源数目>\n",m);
	for( i = 0; i < m; ++i )  
	{  
		cin >> Available[i];  
	}  
	printf("最大需求矩阵(%d*%d输入)>\n",n,m);
	for( i = 0; i < n; ++i )  
	{  
		for( j = 0; j < m; ++j )  
		{  
			cin >> Max[i][j];  
		}  
	}  
	printf("分配矩阵(%d*%d输入)>\n",n,m); 
	for( i = 0; i < n; ++i )  
	{  
		for( j = 0; j < m; ++j )  
		{  
			cin >> Allocation[i][j]; 
			Need[i][j] = Max[i][j] - Allocation[i][j];
		}  
	}  
}  

bool IsSafe()  
{  
	int i=0;
	for (i=0;i<n;++i)
	{
		if(Finish[i] == true)
			continue;
		else
			break;
	}
	if(i == n)
		return true;    //安全
	else
		return false;   //不安全
}   

bool Select(int &tmp,int tmpNeed[][MAXRESOURCE])  
{  
	//选择一个Finish[i]=false,Need[i]<=Work[i] 
	int j=0; 
	for (int i=0;i<n;++i)
	{
		if(Finish[i])
			continue;
		for (j=0;j<m;++j)
		{
			if(tmpNeed[i][j] > Work[j])
				break;
		}
		if(j == m)
		{
			tmp=i;
			return true;
		}
	}
	return false;
}  

bool Safe(int *tmpAvail,int tmpAlloc[][MAXRESOURCE],int tmpNeed[][MAXRESOURCE])  
{  
	for(int i = 0; i < n; ++i)  
	{  
		Finish[i] = false;  
	}  
	for (int j = 0; j < m; ++j)  
	{  
		Work[j] = tmpAvail[j];  
	}  
	int tmp=0;  
	int index = 0;  
	while(Select(tmp,tmpNeed))  
	{  
		Finish[tmp] = true;  
		for (int k = 0; k < m; ++k)  
		{  
			Work[k] += tmpAlloc[tmp][k];  
		}  
		SafeSeries[index++] = tmp;
	}  
	if(IsSafe())  
		return true;    //安全
	else
		return false;   //不安全
}   

void Display()
{
	int i=0;
	int j=0;
	cout<<"当前可利用的资源数目"<<endl;
	for(i = 0; i < m; ++i)  
	{  
		cout << Available[i]<<" ";  
	}  
	cout<<endl;
	cout<<"最大需求矩阵"<<endl;
	for(i = 0; i < n; ++i )  
	{  
		for( j = 0; j < m; ++j)  
		{  
			cout<<Max[i][j]<<" ";
		}  
		cout<<endl;
	}  
	cout<<"分配矩阵"<<endl;
	for( i = 0; i < n; ++i )  
	{  
		for( j = 0; j < m; ++j )  
		{  
			cout<<Allocation[i][j]<<" "; 
		}  
		cout<<endl;
	}  
	cout<<"需求矩阵"<<endl;
	for( i = 0; i < n; ++i )  
	{  
		for( j = 0; j < m; ++j )  
		{  
			cout<<Need[i][j]<<" ";
		}  
		cout<<endl;
	} 
}

void BankA()
{
	int i=0;
	int index=0;
	cout<<"请输入请求资源的进程下标>";
	cin>>index;
	assert(index < n && index >= 0);
	cout<<"请输入当前的请求资源>"<<endl;
	for (i=0;i<m;++i)
	{
		cin>>Request[i];
	}
	for (i=0;i<m;++i)
	{
		if(Request[i] <= Need[index][i])
		{
			continue;
		}
		else
		{
			cout<<"第一次试分配失败"<<endl;
			break;
		}
	}
	if(i < m)   //如果第一次试分配失败则不执行后面的语句
	{
		return ;
	}
	for(i=0;i<m;++i)
	{
		if(Request[i] <= Available[i])
		{
			continue;
		}
		else
		{
			cout<<"第二次试分配失败"<<endl;
			break;
		}
	}
	if(i < m)     //如果第二次试分配失败则不同执行后面的语句
	{
		return ;
	}
	//开始试分配
	int tmpAvail[MAXRESOURCE]={0};
	int tmpAlloc[MAXPROCESS][MAXRESOURCE]={0};
	int tmpNeed[MAXPROCESS][MAXRESOURCE]={0};
	memmove(tmpAvail,Available,sizeof(int)*MAXRESOURCE);
	memmove(tmpAlloc,Allocation,sizeof(int)*MAXPROCESS*MAXRESOURCE);
	memmove(tmpNeed,Need,sizeof(int)*MAXPROCESS*MAXRESOURCE);
	for (int i=0;i<m;++i)
	{
		int j=0;
		tmpAvail[i] -= Request[i];
		tmpAlloc[index][i] += Request[i];
		tmpNeed[index][i] -= Request[i];
		for (j=0;j<m;++j)
		{
			if(tmpNeed[index][j] == 0)
				continue;
			else
				break;
		}
		if(j == m)   //当前需求全为0
		{
			for (int k=0;k<m;++k)
			{
				tmpAvail[k] += tmpAlloc[index][k];
				tmpAlloc[index][k]=0;
				tmpNeed[index][k]=0;
			}
		}
		//当前需求不全为0则不做任何处理
	}
	//开始执行安全性算法
	bool ret=Safe(tmpAvail,tmpAlloc,tmpNeed);
	if(ret == true)
	{
		//如果试分配成功则更新Available,Allocation,Allocation的状态
		memmove(Available,tmpAvail,sizeof(int)*MAXRESOURCE);
		memmove(Allocation,tmpAlloc,sizeof(int)*MAXPROCESS*MAXRESOURCE);
		memmove(Need,tmpNeed,sizeof(int)*MAXPROCESS*MAXRESOURCE);
		cout<<"进程p"<<index<<"请求资源允许"<<endl;
	}
	else
	{
		//只要试分配失败则将Finish置为false
		for(int i = 0; i < n; ++i)  
		{  
			Finish[i] = false;  
		}  
		cout<<"第三次试分配失败"<<endl;
	}
}

void Menu()
{
	cout<<"*************银行家算法*************"<<endl;
	cout<<"**********1.测试安全性代码**********"<<endl;
	cout<<"**********2.测试银行家算法**********"<<endl;
	cout<<"**********3.初始化******************"<<endl;
	cout<<"**********4.打印矩阵****************"<<endl;
	cout<<"**********0.退出********************"<<endl;
}
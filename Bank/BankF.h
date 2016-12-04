#define _CRT_SECURE_NO_WARNINGS 1 

const int MAXPROCESS=100;
const int MAXRESOURCE=100; 

int Available[MAXRESOURCE];         //可用资源向量  
int Max[MAXPROCESS][MAXRESOURCE];   //最大需求矩阵  
int Allocation[MAXPROCESS][MAXRESOURCE];  //分配矩阵  
int Need[MAXPROCESS][MAXRESOURCE];        //需求矩阵  
int Request[MAXPROCESS][MAXRESOURCE];     //请求向量  
 
int Work[MAXRESOURCE];       //工作向量  
bool Finish[MAXPROCESS]; 
int SafeSeries[MAXPROCESS];  //安全序列  

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
		}  
	}  
	printf("需求矩阵(%d*%d输入)\n",n,m); 
	for( i = 0; i < n; ++i )  
	{  
		for( j = 0; j < m; ++j )  
		{  
			cin >> Need[i][j];  
		}  
	}  
}  

bool IsSafe()  
{  
	for(int i = 0; i < n; ++i)  
	{  
		if(!Finish[i])
		{
			return false; //不安全 
		}
	}  
	return true;         //安全
}   

bool Select(int &tmp)  
{  
	//选择一个Finish[i]=false,Need[i]<=Work[i] 
	int j=0; 
	for (int i=0;i<n;++i)
	{
		if(Finish[i])
			continue;
		for (j=0;j<m;++j)
		{
			if(Need[i][j] > Work[j])
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

bool Safe()  
{  
	for(int i = 0; i < n; ++i)  
	{  
		Finish[i] = false;  
	}  
	for (int j = 0; j < m; ++j)  
	{  
		Work[j] = Available[j];  
	}  
	int tmp=0;  
	int index = 0;  
	while(Select(tmp))  
	{  
		Finish[tmp] = true;  
		for (int k = 0; k < m; ++k)  
		{  
			Work[k] += Allocation[tmp][k];  
		}  
		SafeSeries[index++] = tmp;
	}  
	if(IsSafe())  
		return true;    //安全
	else
		return false;   //不安全
}   

void testBank()
{
	Init();  
	Safe();  
	if(IsSafe())  
	{  
		cout<<"存在一个安全序列>";  
		for (int i = 0; i < n ; ++i)  
		{  
			printf("p%d->",SafeSeries[i]);
		}  
		cout<<"end"<<endl;
	}  
	else  
	{  
		cout<<"无法找到一个安全序列"<<endl;
	}  
}
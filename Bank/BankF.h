#define _CRT_SECURE_NO_WARNINGS 1 

const int MAXPROCESS=100;
const int MAXRESOURCE=100; 

int Available[MAXRESOURCE];         //������Դ����  
int Max[MAXPROCESS][MAXRESOURCE];   //����������  
int Allocation[MAXPROCESS][MAXRESOURCE];  //�������  
int Need[MAXPROCESS][MAXRESOURCE];        //�������  
int Request[MAXPROCESS][MAXRESOURCE];     //��������  
 
int Work[MAXRESOURCE];       //��������  
bool Finish[MAXPROCESS]; 
int SafeSeries[MAXPROCESS];  //��ȫ����  

int n;   //������  
int m;   //��Դ��  

void Init()  
{  
	cout<<"�������������>";  
	cin>>n;
	cout<<"��������Դ������>";  
	cin>>m;
	int i,j;  
	printf("������%d����Դ�ĵ�ǰ��������Դ��Ŀ>\n",m);
	for( i = 0; i < m; ++i )  
	{  
		cin >> Available[i];  
	}  
	printf("����������(%d*%d����)>\n",n,m);
	for( i = 0; i < n; ++i )  
	{  
		for( j = 0; j < m; ++j )  
		{  
			cin >> Max[i][j];  
		}  
	}  
	printf("�������(%d*%d����)>\n",n,m); 
	for( i = 0; i < n; ++i )  
	{  
		for( j = 0; j < m; ++j )  
		{  
			cin >> Allocation[i][j];  
		}  
	}  
	printf("�������(%d*%d����)\n",n,m); 
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
			return false; //����ȫ 
		}
	}  
	return true;         //��ȫ
}   

bool Select(int &tmp)  
{  
	//ѡ��һ��Finish[i]=false,Need[i]<=Work[i] 
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
		return true;    //��ȫ
	else
		return false;   //����ȫ
}   

void testBank()
{
	Init();  
	Safe();  
	if(IsSafe())  
	{  
		cout<<"����һ����ȫ����>";  
		for (int i = 0; i < n ; ++i)  
		{  
			printf("p%d->",SafeSeries[i]);
		}  
		cout<<"end"<<endl;
	}  
	else  
	{  
		cout<<"�޷��ҵ�һ����ȫ����"<<endl;
	}  
}
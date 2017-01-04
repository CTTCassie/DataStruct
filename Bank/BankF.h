#define _CRT_SECURE_NO_WARNINGS 1 

const int MAXPROCESS=100;
const int MAXRESOURCE=100; 

int Available[MAXRESOURCE];         //������Դ����  
int Max[MAXPROCESS][MAXRESOURCE];   //����������  
int Allocation[MAXPROCESS][MAXRESOURCE];  //�������  
int Need[MAXPROCESS][MAXRESOURCE];        //�������  

int Request[MAXRESOURCE];      //��������  
 
int Work[MAXRESOURCE];         //��������  
bool Finish[MAXPROCESS]; 
int SafeSeries[MAXPROCESS];    //��ȫ����  

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
		return true;    //��ȫ
	else
		return false;   //����ȫ
}   

bool Select(int &tmp,int tmpNeed[][MAXRESOURCE])  
{  
	//ѡ��һ��Finish[i]=false,Need[i]<=Work[i] 
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
		return true;    //��ȫ
	else
		return false;   //����ȫ
}   

void Display()
{
	int i=0;
	int j=0;
	cout<<"��ǰ�����õ���Դ��Ŀ"<<endl;
	for(i = 0; i < m; ++i)  
	{  
		cout << Available[i]<<" ";  
	}  
	cout<<endl;
	cout<<"����������"<<endl;
	for(i = 0; i < n; ++i )  
	{  
		for( j = 0; j < m; ++j)  
		{  
			cout<<Max[i][j]<<" ";
		}  
		cout<<endl;
	}  
	cout<<"�������"<<endl;
	for( i = 0; i < n; ++i )  
	{  
		for( j = 0; j < m; ++j )  
		{  
			cout<<Allocation[i][j]<<" "; 
		}  
		cout<<endl;
	}  
	cout<<"�������"<<endl;
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
	cout<<"������������Դ�Ľ����±�>";
	cin>>index;
	assert(index < n && index >= 0);
	cout<<"�����뵱ǰ��������Դ>"<<endl;
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
			cout<<"��һ���Է���ʧ��"<<endl;
			break;
		}
	}
	if(i < m)   //�����һ���Է���ʧ����ִ�к�������
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
			cout<<"�ڶ����Է���ʧ��"<<endl;
			break;
		}
	}
	if(i < m)     //����ڶ����Է���ʧ����ִͬ�к�������
	{
		return ;
	}
	//��ʼ�Է���
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
		if(j == m)   //��ǰ����ȫΪ0
		{
			for (int k=0;k<m;++k)
			{
				tmpAvail[k] += tmpAlloc[index][k];
				tmpAlloc[index][k]=0;
				tmpNeed[index][k]=0;
			}
		}
		//��ǰ����ȫΪ0�����κδ���
	}
	//��ʼִ�а�ȫ���㷨
	bool ret=Safe(tmpAvail,tmpAlloc,tmpNeed);
	if(ret == true)
	{
		//����Է���ɹ������Available,Allocation,Allocation��״̬
		memmove(Available,tmpAvail,sizeof(int)*MAXRESOURCE);
		memmove(Allocation,tmpAlloc,sizeof(int)*MAXPROCESS*MAXRESOURCE);
		memmove(Need,tmpNeed,sizeof(int)*MAXPROCESS*MAXRESOURCE);
		cout<<"����p"<<index<<"������Դ����"<<endl;
	}
	else
	{
		//ֻҪ�Է���ʧ����Finish��Ϊfalse
		for(int i = 0; i < n; ++i)  
		{  
			Finish[i] = false;  
		}  
		cout<<"�������Է���ʧ��"<<endl;
	}
}

void Menu()
{
	cout<<"*************���м��㷨*************"<<endl;
	cout<<"**********1.���԰�ȫ�Դ���**********"<<endl;
	cout<<"**********2.�������м��㷨**********"<<endl;
	cout<<"**********3.��ʼ��******************"<<endl;
	cout<<"**********4.��ӡ����****************"<<endl;
	cout<<"**********0.�˳�********************"<<endl;
}
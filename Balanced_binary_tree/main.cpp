#include<stdio.h>
#include<malloc.H>
#define LH 1  //���
#define EH 0 //�ȸ�
#define RH -1 //�Ҹ�
#define EQ(a,b) ((a)==(b)) //a==b
#define LT(a,b) ((a)<(b))//a<b

enum Boolean {FALSE,TRUE};

typedef struct BSTNode
{
    int data;
    int bf;//����ƽ������
    struct BSTNode *lchild,*rchild;//���Һ���ָ��
} BSTNode,*BSTree;


//��������������֮��Pָ���µ�������㣬���ô���֮ǰ���������ĸ����
void R_Rotate(BSTree &p)
{
    BSTree lc;
    lc=p->lchild;
    p->lchild=lc->rchild;
    lc->rchild=p;
    p=lc;
}

//��������
void L_Rotate(BSTree &p)
{
    BSTree rc;
    rc=p->rchild;
    p->rchild=rc->lchild;
    rc->lchild=p;
    p=rc;
}

//����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת�������㷨����ʱ��ָ��Tָ���µĸ����
void LeftBalance(BSTree &T)
{
    BSTree lc,rd;
    lc=T->lchild;
    switch(lc->bf)  //���*T����������ƽ��ȣ�������Ӧƽ�⴦��
    {
    case LH:  //�½�������*T�����ӵ��������ϣ�Ҫ������������
        T->bf=lc->bf=EH;
        R_Rotate(T);
        break;
    case RH:  //�½�������*T�����ӵ��������ϣ�Ҫ��˫������
        rd=lc->rchild; //rdָ��*T�����ӵ���������
        switch(rd->bf)   //�޸�*T4�������ӵ�ƽ������
        {
        case LH:
            T->bf=RH;
            lc->bf=EH;
            break;
        case EH:
            T->bf=lc->bf=EH;
            break;
        case RH:
            T->bf=EH;
            lc->bf=LH;
            break;
        }
        rd->bf=EH;
        L_Rotate(T->lchild);  //��*T��������������ƽ�⴦��
        R_Rotate(T);   //��*T������ƽ�⴦��
    }
}

void RightBalance(BSTree &T)
{
//����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת���������㷨����ʱ��ָ��Tָ���µĸ����
    BSTree rc,ld;
    rc=T->rchild;  //rcָ��*T�������������
    switch(rc->bf)  //���*T����������ƽ��ȣ�������Ӧƽ�⴦��
    {
    case RH:  //�½�������*T���Һ��ӵ��������ϣ�Ҫ������������
        T->bf=rc->bf=EH;
        L_Rotate(T);
        break;
    case LH:  //�½�������*T���Һ��ӵ��������ϣ�Ҫ��˫������
        ld=rc->lchild; //ldָ��*T���Һ��ӵ���������
        switch(ld->bf)   //�޸�*T�����Һ��ӵ�ƽ������
        {
        case LH:
            T->bf=EH;
            rc->bf=LH;
            break;
        case EH:
            T->bf=rc->bf=EH;
            break;
        case RH:
            T->bf=RH;
            rc->bf=EH;
            break;
        }
        ld->bf=EH;
        R_Rotate(T->rchild);  //��*T��������������ƽ�⴦��
        L_Rotate(T);   //��*T������ƽ�⴦��
    }
}

//�����½��
int InsertAVL(BSTree &T,int e,enum Boolean &taller)
{
    if(!T)
    {
        //���ڵ㣬�������ߡ�����tallerΪTRUE
        T=(BSTree)malloc(sizeof(BSTNode));
        T->data=e;
        T->lchild=T->rchild=NULL;
        T->bf=EH;
        taller=TRUE;
    }
    else
    {
        if(EQ(e,T->data))  //�����Ѵ��ں�e����ͬ�ؼ��ֵĵ����ٲ���
        {
            taller=FALSE;
            printf("�����Ѵ������У��������������֣�\n");
            return 0;
        }
        if(LT(e,T->data))    //������*T���������н�������e<t->data
        {
            if(!InsertAVL(T->lchild,e,taller))
                return 0;  //δ����
            if(taller)    //�Ѳ��뵽*T�����������������������ߡ�
                switch(T->bf)   //���*T��ƽ���
                {
                case LH:  //ԭ�����������������ߣ���Ҫ����ƽ�⴦��
                    LeftBalance(T);
                    taller=FALSE;
                    break;
                case EH:  //ԭ�����������ȸߣ��������������߶�ʹ������
                    T->bf=LH;
                    taller=TRUE;
                    break;
                case RH:  //ԭ�����������������ߣ��������������ȸ�
                    T->bf=EH;
                    taller=FALSE;
                    break;
                }
        }
        else       //������*T���������н�������
        {
            if(!InsertAVL(T->rchild,e,taller))
                return 0;//δ����
            if(taller)  //�Ѳ��뵽*T��������������������
                switch(T->bf) //���*T��ƽ���
                {
                case LH://ԭ�����������������ߣ������������ȸ�
                    T->bf=EH;
                    taller=FALSE;
                    break;
                case EH://ԭ�����������ȸߣ��������������߶�ʹ������
                    T->bf=RH;
                    taller=TRUE;
                    break;
                case RH:   //ԭ�����������������ߣ���Ҫ����ƽ�⴦��
                    RightBalance(T);
                    taller=FALSE;
                    break;
                }//switch(T->bf)
        }
    }
    return 1;
}


//ɾ��ƽ���������Ԫ�أ�����ƽ�⴦��
int DeleteAVL(BSTree &T,int e,enum Boolean &taller)
{

    if(!T)
        return 0;
    else
    {
        if(EQ(e,T->data))  //�ҵ���e��ȵĽ��
        {
            if(!T->lchild&&!T->rchild)
            {
                taller=FALSE;    //�ý��ΪҶ�ӽ��
                free(T);
                T=NULL;
                return 1;
            }
            else if(T->lchild)  //�ý����������
            {
                if(!T->lchild->rchild)  //����������Ѱ�����ֵ�����T
                {
                    T->data=T->lchild->data;
                    T->lchild->data=e;
                    DeleteAVL(T->lchild,e,taller);
                }
                else
                {
                    T->data=T->lchild->rchild->data;
                    T->lchild->rchild->data=e;
                    DeleteAVL(T->lchild->rchild,e,taller);
                }
                if(!taller)  //�Ѵ�������ɾ�����������䰫
                    switch(T->bf) //���*T��ƽ���
                    {
                    case LH://ԭ�����������������ߣ������������ȸ�
                        T->bf=EH;
                        taller=FALSE;
                        break;
                    case EH://ԭ�����������ȸߣ������������䰫��ʹ������
                        T->bf=RH;
                        taller=TRUE;
                        break;
                    case RH:   //ԭ�����������������ߣ���Ҫ����ƽ�⴦��
                        RightBalance(T);
                        taller=FALSE;
                        break;
                    }
            }
            else if(T->rchild)  //�ý����������
            {
                if(!T->rchild->lchild)  //����������Ѱ����Сֵ�����T
                {
                    T->data=T->rchild->data;
                    T->rchild->data=e;
                    DeleteAVL(T->rchild,e,taller);
                }
                else
                {
                    T->rchild->data=T->rchild->lchild->data;
                    T->rchild->lchild->data=e;
                    DeleteAVL(T->rchild->lchild,e,taller);
                }
                if(!taller)    //�Ѵ�������ɾ�����������䰫
                    switch(T->bf)   //���*T��ƽ���
                    {
                    case LH:  //ԭ�����������������ߣ���Ҫ����ƽ�⴦��
                        LeftBalance(T);
                        taller=FALSE;
                        break;
                    case EH:  //ԭ�����������ȸߣ������������䰫��ʹ������
                        T->bf=LH;
                        taller=TRUE;
                        break;
                    case RH:  //ԭ�����������������ߣ������������ȸ�
                        T->bf=EH;
                        taller=FALSE;
                        break;
                    }
            }
        }
        if(LT(e,T->data))    //������*T���������н�������
        {
            if(!DeleteAVL(T->lchild,e,taller))
                return 0;  //δɾ��
        }
        else       //������*T���������н�������
        {
            if(!DeleteAVL(T->rchild,e,taller))
                return 0;//δɾ��
        }
    }
    return 1;
}

//����״��ӡ���������
void Print_BSTree(BSTree T,int i)
{
    int j;
    if(T->rchild)
        Print_BSTree(T->rchild,i+1);
    for(j=1; j<=i; j++)
        printf("     "); //��ӡi���ո��Ա�ʾ�����
    printf("%5d\n",T->data); //��ӡTԪ��,����
    if(T->lchild)
        Print_BSTree(T->lchild,i+1);
}

//����ƽ�������
void Destroy_BSTree(BSTree &T)
{
    BSTree p;
    p=T;
    while(p->lchild&&p->rchild)
    {
        Destroy_BSTree(p->lchild);
        Destroy_BSTree(p->rchild);
    }
    if(!p->lchild&&p->rchild)
        Destroy_BSTree(p->rchild);
    if(!p->rchild&&p->lchild)
        Destroy_BSTree(p->lchild);
    if(!p->lchild&&!p->rchild)
        free(p);
    T=NULL;
}

int main()
{
    char x;
    int e,i=0;
    enum Boolean taller;
    BSTree T=NULL;
    while(1)
    {
        printf("-----------------------------------------------------------------\n");
        printf("                      ƽ������� \n\n");
        printf("                     1.����������\n");
        printf("                     2.������  \n");
        printf("                     3.ɾ�����  \n");
        printf("                     4.ɾ����    \n");
        printf("                     5.�˳�      \n");
        printf("-----------------------------------------------------------------\n");
        printf(" ��ѡ��:");
        x=getchar();
        if(x=='1')
        {
            e=0;
            printf("������(������Ϊ-1ʱ����������������):\n");
            while(e!=-1)
            {
                scanf("%d",&e);
                if(e!=-1)
                {
                    taller=FALSE;
                    InsertAVL(T,e,taller);//��������
                }
            }
            printf("������Ϊ:\n");
            Print_BSTree(T,0);
        }
        else if(x=='2')
        {
            e=0;
            while(e!=-1)
            {
                printf("��������:");
                scanf("%d",&e);
                if(e!=-1)
                {
                    taller=FALSE;
                    InsertAVL(T,e,taller);
                    Print_BSTree(T,i);
                }
            }
        }
        else if(x=='3')
        {
            if(T==NULL)
                printf("����!\n");
            else
            {
                e=0;
                while(e!=-1)
                {
                    printf("������һ������:");
                    scanf("%d",&e);
                    if(e!=-1)
                    {
                        taller=TRUE;
                        DeleteAVL(T,e,taller);
                        if(T==NULL)
                            printf("����!\n");
                        else
                            Print_BSTree(T,i);
                    }
                }
            }
        }
        else if(x=='4')
        {
            Destroy_BSTree(T);
            printf("�������!\n");
        }
        else if(x=='5')
            break;
        else
            printf("Error!\n");
        getchar();
    }
}
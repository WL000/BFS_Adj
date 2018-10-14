/*BFS�����ڽӱ�*/
#include <stdio.h>
#include <stdlib.h>
#define NUM 10

typedef struct ArcNode
{
    int adjvex;               //ָ�򶥵�Ļ�
    struct ArcNode *nextarc;   //ָ����һ������ָ��
} ArcNode;

typedef struct VNode
{
    char data;             //������Ϣ
    ArcNode *firstarc;    //ָ���һ�������ö���Ļ���ָ��
} VNode,AdjList[NUM];

typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;   //����ͼ�������ͻ���
} ALGraph;

typedef struct QNode
{
    char data;
    struct QNode *next;
} QNode,*QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} LinQueue;    //����

int visited[MAX_VERTEX_NUM];//���ʱ�־����

void InitQueue(LinQueue *Q)
{
    //��ʼ������
    Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));
    if(!Q->front) exit(1);
    Q->front->next=NULL;
}

int EmptyQueue(LinQueue *Q)
{
    //����Ϊ�շ���true,���򷵻�false
    if(Q->rear==Q->front)
        return 1;
    else
        return 0;
}

void EnQueue(LinQueue *Q,char e)
{
    //���
    QNode *p;
    p=(QNode *)malloc(sizeof(QNode));
    p->data=e;
    p->next=NULL;
    (Q->rear)->next=p;
    Q->rear=p;
}

char DeQueue(LinQueue *Q)
{
    //��ͷ����
    char e;
    QNode *p;
    if(EmptyQueue(Q))
    {
        printf("�ӿ�!\n");
        return 0;
    }
    p=Q->front->next;
    e=p->data;
    Q->front->next=p->next;
    if(Q->rear==p) Q->rear=Q->front;
    free(p);
    return e;
}
int LocateVex(ALGraph G,char v)
{
    /*Ѱ�����������ھ����е�λ��*/
    int i;
    for(i=0; i<G.vexnum; i++)
    {
        if(G.vertices[i].data==v)
            return i;
    }
    return -1;
}
void Creat_T(ALGraph *G)
{
    /*�����ڽӱ�*/
    int i,m,n;
    char v1,v2;
    ArcNode *p,*q;
    p=NULL;
    q=NULL;//��ֹҰָ��
    printf("����������ͼ�Ķ�����:\n");
    scanf("%d",&G->vexnum);
    printf("����������ͼ�ı���:\n");
    scanf("%d",&G->arcnum);
    printf("�����붥����Ϣ��\n");
    for(i=0; i<G->vexnum; i++)
    {
        fflush(stdin);
        scanf("%c",&G->vertices[i].data);
        G->vertices[i].firstarc=NULL;   //��ʼ����ָ��
    }
    printf("������ߣ�\n");
    for(i=0; i<G->arcnum; i++)
    {
        fflush(stdin);
        scanf("%c%c",&v1,&v2);
        m=LocateVex(*G,v1);
        n=LocateVex(*G,v2);
        p=(ArcNode *)malloc(sizeof(ArcNode));
        if(!p) exit(1);
        p->nextarc=NULL;
        p->adjvex=-1;
        p->adjvex=m;
        p->nextarc=G->vertices[n].firstarc;
        G->vertices[n].firstarc=p;
        q=(ArcNode *)malloc(sizeof(ArcNode));
        if(!p) exit(1);
        q->nextarc=NULL;
        q->adjvex=n;
        q->nextarc=G->vertices[m].firstarc;
        G->vertices[m].firstarc=q;
    }
}
void BFSTraverse(ALGraph *G,LinQueue *Q)
{
    //������ȱ�������ͼ�ڽӱ�
    int i,n;
    char v;
    ArcNode *p;
    p=NULL;
    for(i=0; i<G->vexnum; i++)  //��ʼ��visited����
    {
        visited[i]=0;
    }
    EnQueue(Q,G->vertices[0].data);
    visited[0]=1;
    printf("%c->",G->vertices[0].data);
    while(!EmptyQueue(Q))
    {
        v=DeQueue(Q);
        n=LocateVex(*G,v);
        p=G->vertices[n].firstarc;
        while(p!=NULL)
        {
            if(!visited[p->adjvex])
            {
                printf("%c->",G->vertices[p->adjvex].data);
                visited[p->adjvex]=1;
                EnQueue(Q,G->vertices[p->adjvex].data);
            }
            p=p->nextarc;
        }
    }
    printf("END");
    free(p);
}
int main()
{
    /*���Ժ���*/
    ALGraph  G;
    LinQueue Q;//�������
    InitQueue(&Q);//��ʼ������
    Creat_T(&G);//�����ڽӱ�
    BFSTraverse(&G,&Q);//BFS
    return 0;
}

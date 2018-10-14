/*BFS遍历邻接表*/
#include <stdio.h>
#include <stdlib.h>
#define NUM 10

typedef struct ArcNode
{
    int adjvex;               //指向顶点的弧
    struct ArcNode *nextarc;   //指向下一条弧的指针
} ArcNode;

typedef struct VNode
{
    char data;             //顶点信息
    ArcNode *firstarc;    //指向第一条依附该顶点的弧的指针
} VNode,AdjList[NUM];

typedef struct
{
    AdjList vertices;
    int vexnum,arcnum;   //无向图顶点数和弧数
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
} LinQueue;    //队列

int visited[MAX_VERTEX_NUM];//访问标志数组

void InitQueue(LinQueue *Q)
{
    //初始化队列
    Q->front=Q->rear=(QueuePtr)malloc(sizeof(QNode));
    if(!Q->front) exit(1);
    Q->front->next=NULL;
}

int EmptyQueue(LinQueue *Q)
{
    //队列为空返回true,否则返回false
    if(Q->rear==Q->front)
        return 1;
    else
        return 0;
}

void EnQueue(LinQueue *Q,char e)
{
    //入队
    QNode *p;
    p=(QNode *)malloc(sizeof(QNode));
    p->data=e;
    p->next=NULL;
    (Q->rear)->next=p;
    Q->rear=p;
}

char DeQueue(LinQueue *Q)
{
    //队头出队
    char e;
    QNode *p;
    if(EmptyQueue(Q))
    {
        printf("队空!\n");
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
    /*寻找两个定点在矩阵中的位置*/
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
    /*创建邻接表*/
    int i,m,n;
    char v1,v2;
    ArcNode *p,*q;
    p=NULL;
    q=NULL;//防止野指针
    printf("请输入无向图的顶点数:\n");
    scanf("%d",&G->vexnum);
    printf("请输入无向图的边数:\n");
    scanf("%d",&G->arcnum);
    printf("请输入顶点信息：\n");
    for(i=0; i<G->vexnum; i++)
    {
        fflush(stdin);
        scanf("%c",&G->vertices[i].data);
        G->vertices[i].firstarc=NULL;   //初始化该指针
    }
    printf("请输入边：\n");
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
    //广度优先遍历无向图邻接表
    int i,n;
    char v;
    ArcNode *p;
    p=NULL;
    for(i=0; i<G->vexnum; i++)  //初始化visited函数
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
    /*测试函数*/
    ALGraph  G;
    LinQueue Q;//申请队列
    InitQueue(&Q);//初始化队列
    Creat_T(&G);//建立邻接表
    BFSTraverse(&G,&Q);//BFS
    return 0;
}

/*typedef union {
	int cint;
	char cchar;
	double cdouble;
	float cfloat;
}Cdata;*/

/*enum Cla{c0,c1,c2,c3};*/

typedef union{ 
	char Symbol;
	double Number;
}EleType;

typedef struct node{
	int rank;
	EleType data;
	struct node *next;
}ChainNode;

typedef struct{
	ChainNode *head;
	ChainNode *tail;
}List;
/*声明*/
 
List *CreateList(void);

void DestroyList(List *);

void ClearList(List *);

int ListAppend(List *,EleType);

int ListInsert(List *,int,EleType);

int ListDelete(List *,int);

int GetElement(List *,int,EleType *);

ChainNode *GetAddr(List *,int);

int TraverseList(List *,int (*)(EleType *));

ChainNode *NewChainNode(EleType);

void settail(List *);
/*改变尾指针*/ 

/*函数体*/

List *CreateList(void){
	List *p;
	EleType *data=0;/*初始空指针*/ 
	
	p=(List *)malloc(sizeof(List));
	
	if(!p) return 0;
	
	p->head=NewChainNode(*data);/*data特别*/
	p->tail =p->head ; /*尾指针*/ 
	
	if(!p->head){
	free(p);return 0;}
	
	return p;
}

void DestroyList(List *lp){
	ClearList(lp);
	free(lp->head);
	free(lp->tail);/*清尾指针*/ 
	free(lp);
}

void ClearList(List *lp){
	while(ListDelete(lp,1));
}

int ListAppend(List *lp,EleType data){
	/*ChainNode *p;*/
	ChainNode *newp;
	
	newp=NewChainNode(data);
	if(!newp) return 0;
	
	/*for(p=lp->head;p->next;p=p->next);*/
	lp->tail->next=newp;
	lp->tail=newp;/*尾*/ 
	return 1; 
}

int ListInsert(List *lp,int n,EleType data){
	ChainNode *p;
	ChainNode *newp;
	
	p=GetAddr(lp,n-1);
	if(!p) return 0;
	
	newp=NewChainNode(data);
	if(!newp) return 0;
	
	newp->next=p->next;
	p->next=newp;
	settail(lp);/*尾*/ 
	
	return 1;
}

int ListDelete(List *lp,int n){
	ChainNode *p,*p1;
	
	if(!lp->head->next) return 0;
	
	p=GetAddr(lp,n-1);
	if(!(p&&p->next )) return 0;
	
	p1=p->next ;
	p->next =p->next ->next;
	
	free(p1);
	settail(lp);/*尾*/ 
	
	return 1;
}

int GetElement(List *lp,int n,EleType *data){
	ChainNode *p;
	
	p=GetAddr(lp,n);
	if(!p) return 0;
	
	*data=p->data;
	
	return 1;
}

int TraverseList(List *lp,int (*f)(EleType *)){
	ChainNode *p;
	int a=0;
	
	for(p=lp->head->next;p ;p=p->next){
		if(!f(&(p->data))) return a+1;
		a++;
	}
	return 0;
}

ChainNode *NewChainNode(EleType data){
	ChainNode *p;
	
	p=(ChainNode *)malloc(sizeof(ChainNode));
	if(!p) return 0;
	
	p->data =data;
	p->next =0;
	
	return p;
}

ChainNode *GetAddr(List *lp,int n){
	ChainNode *p;
	int a;
	
	if(n<0) return 0;
	
	p=lp->head ;
	a=0;
	
	while(p&&a<n){
		p=p->next;
		a++;
	}
	
	return p;
}
 
void settail(List *lp){
	ChainNode *p;
	
	for(p=lp->head ;p->next ;p=p->next );
	lp->tail =p;
	

	
}




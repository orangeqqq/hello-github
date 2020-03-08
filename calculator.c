#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include "list.h"
/*声明*/
double FourSum(List *lp);


int main(){
	char orginstr[21],choose[20];
	char distinct[]="0123456789+-*/()";
	int i=0,j,flag,k;
	int right=0,left=0;
	double answer;
	List *lp;
	EleType data;
	
	/*/检验,标准化字符  */
	/*/字符数*/
	do{
		printf("please input words,don't excess 20 byte \n");
		scanf("%s",orginstr);/*输入的字符超啦咋办？*/
		printf("\n");
		if(strlen(orginstr)>20) i=1;	/*字节数限制，*可改*/
	}while(i);
	/*查错*/
	printf("your function:%s\n",orginstr);
	
	/*/检验输入字符是否是算数表达式*/
	for(i=0;orginstr[i];i++){
		for(flag=0,j=0;distinct[j];j++){
			if(orginstr[i]==distinct[j])flag=1;
		}
		if(flag!=1) {
			printf("match express have mistake");
			return 0;
		}
	}
	
	lp=CreateList();
	if(!lp) return 0;
	
	for(flag=0,i=0;orginstr[i];i++){		/*/flag用来鉴别表达式无两个运算符在一起的错误。*/
		switch(orginstr[i]){
			case '+':
			case '-':{
				data.Symbol=orginstr[i];
				ListAppend(lp,data);
				lp->tail->rank=1;
				
				if(flag==1){printf("error!please input again.\n");return 0;}
				flag=1;
				break;
			}
			case '*':
			case '/':{
				data.Symbol=orginstr[i];
				ListAppend(lp,data);
				lp->tail->rank=2;
				
				if(flag==1){printf("error!please input again.\n");return 0;}
				flag=1;
				break;
			}
			case '(':{							/*/保证(,)至少是3级，括号内镶的括号依级递增*/
				left++;
				data.Symbol=orginstr[i];
				ListAppend(lp,data);
				
				lp->tail->rank=2+left-right;
				flag=0;
				break;
			}
			case ')':{
				right++;
				data.Symbol=orginstr[i];
				ListAppend(lp,data);
				
				if(right>left){				/*/保证先有左括号再有右括号*/
					printf("error!\n");
					return 0;
				}
				lp->tail->rank=3+left-right;
				flag=0;
				break;
			}
			default:{
				k=0;			/*/这里的j好像多余啊*/
				j=i;
				while('0'<=orginstr[j]&&orginstr[j]<='9'){
					choose[k]=orginstr[j];
					k++;
					j++;
				}
				
				choose[k]='\0';
				data.Number=atof(choose);
				ListAppend(lp,data);
				lp->tail->rank=0;
				i=j-1;
				
				flag=0;
			}
		}
	}
	/*/检查括号是否配对*/
	if(right!=left){
		printf("the '(',and')' don't mate.");
		return 0;
	}
	/*/第一个不能是*,/*/
	if(lp->head->next->rank==2){
		printf("input error!\n");
		return;
	}
	
	answer=FourSum(lp);
	printf("answer=%f\n",answer);
}


double FourSum(List *lp){
	ChainNode *p,*pright,*pleft;
	List *lp2;
	double sum=0;
	EleType data;
	
	lp2=CreateList();
	if(!lp2) return;
	
	/*/消括号*/
	for(p=lp->head->next;p;p=p->next){
		if(p->rank>2){
			if(p->data.Symbol=='('){
				pleft=p;
				p=p->next;		
				
				while(p->rank!=pleft->rank){
					if(!p) break;
					ListAppend(lp2,p->data);
					lp2->tail->rank=p->rank;
					
					p=p->next;					
				}
				
				pright=p;
				pleft->data.Number=FourSum(lp2);
				pleft->rank=0;
				/*/删除括号内的节点*/
				while(pleft->next!=pright->next){
					p=pleft->next;
					pleft->next=p->next;
					free(p);
				}
				p=pleft;
				
			}
		}
	}
	DestroyList(lp2);
	
	/*/统一处理第一位含+-*/
	if(lp->head->next->rank==0){
		data.Symbol='+';
		ListInsert(lp,1,data);
		lp->head->next->rank=1;
	}
	
	/*/处理*,/*/
	for(p=lp->head->next;p;p=p->next){
		if(p->next->rank==2){
			if(p->next->data.Symbol=='*'){
				pleft=p;
				pright=p->next->next;											
				
				pleft->data.Number=pleft->data.Number*pright->data.Number;
				/*删除*的节点*/
				while(pleft->next!=pright->next){
					p=pleft->next;
					pleft->next=p->next;
					free(p);
				}
				p=pleft;
				continue;
			}
			else if(p->next->data.Symbol=='/'){
				pleft=p;
				pright=p->next->next;											
				
				pleft->data.Number=pleft->data.Number/pright->data.Number;
				/*/删除*的节点*/
				while(pleft->next==pright->next){
					p=pleft->next;
					pleft->next=p->next;
					free(p);
				}
				p=pleft;	
				continue;
			}
		}	
	}
	
	/*处理+,-*/
	for(p=lp->head->next;p;p=p->next){
		if(p->rank==1){
			if(p->data.Symbol=='+'){
				sum=sum+p->next->data.Number;
				p=p->next;
			}
			else{
				sum=sum-p->next->data.Number;
				p=p->next;
			}
		}
	}
	
	return sum;
	
}









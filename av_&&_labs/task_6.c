#include <stdio.h>
typedef struct Transaction{
    int id;
    int sum;
    int provision;
    int creditCard;
}Transaction;
void readTransaction(Transaction *t){
    scanf("%d%d%d%d",&t->id,&t->sum,&t->provision,&t->creditCard);
}
int main(){
    int n,flag=0;
    scanf("%d",&n);
    Transaction transactions[20];
    for (int i = 0; i < n; ++i) {
        readTransaction(&transactions[i]);
    }

    for (int i = 0; i < n; ++i) {
        if(transactions[i].creditCard==1){
            printf("%d %d\n",transactions[i].id,transactions[i].sum+transactions[i].provision);
            flag=1;
        }
    }

    if(!flag){
        printf("No credit card transaction");
    }
    return 0;
}
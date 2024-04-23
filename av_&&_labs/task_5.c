#include <stdio.h>
typedef struct Item{
    char name[20];
    int price;
}Item;
typedef struct ShoppingCart{
    int id;
    Item items[10];
    int numItems;

}ShoppingCart;
void readItem(Item *i){
    scanf("%s %d",i->name,&i->price);
}
void readCart(ShoppingCart *c){
    scanf("%d %d",&c->id,&c->numItems);
    for (int i = 0; i <c->numItems ; ++i) {
        readItem(&c->items[i]);
    }
}
Item lowest(ShoppingCart c){
    Item l=c.items[0];
    for (int i = 1; i < c.numItems; ++i) {
        if(c.items[i].price<l.price){
            l=c.items[i];
        }
    }
    return l;
}
void printAverageOfLowestItems(ShoppingCart *c,int n){
    double average=0;
    Item low;
    for (int i = 0; i <n ; ++i) {
        low= lowest(c[i]);
        average+=low.price;
    }
    printf("Average: %.2lf\n",average/(double)n);
}
//Item highest(ShoppingCart c){
//    Item m=c.items[0];
//    for (int i = 1; i < c.numItems; ++i) {
//        if(c.items[i].price>m.price){
//            m=c.items[i];
//        }
//    }
//    return m;
//}
void printHighestPricedItem(ShoppingCart *c,int n){
    Item max=c[0].items[0];
    int maxId=c[0].id;
    for (int i = 0; i <n ; ++i) {
        for (int j = 0; j < c[i].numItems; ++j) {
            if(c[i].items[j].price>max.price){
                max=c[i].items[j];
                maxId=c[i].id;
            }
        }
    }
    printf("Shoping cart id: %d\nProduct: %s",maxId,max.name);
}
int main(){
    int n;
    ShoppingCart carts[10];
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) {
        readCart(&carts[i]);
    }
    printAverageOfLowestItems(carts,n);
    printHighestPricedItem(carts,n);
    return 0;
}
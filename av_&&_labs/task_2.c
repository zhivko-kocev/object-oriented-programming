#include <stdio.h>
struct date{
    int den;
    int mesec;
    int godina;
};
void vnesiData(struct date *datum){
    scanf("%d",&datum->den);
    scanf("%d",&datum->mesec);
    scanf("%d",&datum->godina);
}
int sporedi(struct date *datum1,struct date *datum2){
    if(datum1->godina>datum2->godina){
        return 1;
    }else if(datum1->godina<datum2->godina){
        return -1;
    }else{
        if(datum1->mesec>datum2->mesec){
            return 1;
        }else if(datum1->mesec<datum2->mesec){
            return -1;
        }else{
            if(datum1->den>datum2->den){
                return 1;
            }else if(datum1->den<datum2->den){
                return -1;
            }else{return 0;}
        }
    }
}
int denovi(struct date prvaData,struct date vtoraData){
    int d=0;
    d+=(prvaData.den-vtoraData.den)+(prvaData.mesec-vtoraData.mesec)*30+(prvaData.godina-vtoraData.godina)*360;
    return d;
}
int main(){
    struct date prvaData,vtoraData;
    vnesiData(&prvaData);
    vnesiData(&vtoraData);
   if(sporedi(&prvaData,&vtoraData)==1){
       printf("Razlikata vo denovi e %d",denovi(prvaData,vtoraData));
   }else if(sporedi(&prvaData,&vtoraData)==-1){
        printf("Razlikata vo denovi e %d",denovi(vtoraData,prvaData));
    }else{
       printf("Ednakvi se");
   }
  return 0;
}
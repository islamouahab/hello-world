#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
using namespace std;
using std::string;

int init_batch(void);
class node{
    public:
    int num_pross,tmp_att,tmp_exe,tmp_sort,id,tmp_perdu;
    time_t tmp_sec;
    struct tm tmp_arr;
    string etat;
    node *next;
    node(int id,struct tm tmp_arr,int unit_calcul,time_t t){
        this->tmp_att=0;
        this->tmp_arr=tmp_arr;
        this->tmp_sort=0;
        this->id=id;
        this->num_pross=1+(rand()%100);
        this->etat="P";
        this->tmp_exe=unit_calcul;
        this->tmp_perdu=0;
        this->tmp_sec=t;
    }
    int getId(){
        return this->id;
    }
    string getEtat(){
        return this->etat;
    }
    int getTemp(){
        return this->tmp_exe;
    }
};


class file{
    public:
    node *head;
    node *tail;
    file(node *h,node *t){
        this->head=h;
        this->tail=t;
    }
};


void enfiler(node *n,file *f){
           if (f->head==NULL && f->tail==NULL){
            f->head=n;
            f->tail=n;
            n->next=NULL;
           }
           else{
            f->tail->next=n;
            f->tail=n;
            n->next=NULL;
           }
}


node *defiler(file *f){
    node *tmp=f->head;
    tmp->etat="A";
    f->head=f->head->next;
    return tmp;
}
node *defiler_t(file *f){
    node *tmp=f->head;
    if (tmp->tmp_exe>0){
    f->head=f->head->next;
    f->tail->next=tmp;
    tmp->next=NULL;
    }

}

void check(file *f){
    if (f){
    file F = *f;
    system("CLS");
    while(F.head){
        cout<<"etat de processus "<<F.head->getId()<<" : "<<F.head->getEtat()<<"      le temp d'arrive : "<<F.head->tmp_arr.tm_hour<<":"<<F.head->tmp_arr.tm_min<<":"<<F.head->tmp_arr.tm_sec<<endl;
        F.head=F.head->next;
     }
     system("pause");
    }
    else{
        system("CLS");
        cout<<"la file est vide !"<<endl;
        system("pause");
    }
}

void stat(file *f,int total,time_t t){
    file F = *f;
    time_t diff_time=F.head->tmp_sec-t;
    F.head->tmp_att=total;
    int i=0;
    while(i<diff_time){
            cout<<"/"<<" ";
            i++;
         }
    while(total-diff_time>0){
         cout<<F.head->getEtat()<<" ";
         total--;
    }
}
void etat(file *f){
    int total=0,count=0;
    float total_att=0;
    time_t time=f->head->tmp_sec;
    while (f->head){ 
        node *rem=defiler(f);
        total+=rem->tmp_exe;
        total_att+=rem->tmp_att;
        while (rem->tmp_exe>0){
            cout<<rem->getEtat()<<" ";
            rem->tmp_exe--;
        }
        cout<<endl;
        if (f->head)
        stat(f,total,time);
        count++;
       
    }
    cout<<"le temps moyen d'attent est : "<<total_att/count<<" uc"<<endl;
}

void executer(file *f){
    system("CLS");
     etat(f);

}


file *cree_file(int id){
    int tmp,nbr_node,i=0;
    time_t t;
    struct tm* c;
    file *f = new file(NULL,NULL);
    system("CLS");
    cout<<"le numero des processus?"<<endl;
    cin>>nbr_node;
    system("CLS");
    while(i<nbr_node){
        cout<<"svp inserer le n d'unite de calcule d'execution de processus "<<i+1<<endl;
        cin>>tmp;
        t=time(NULL);
        c=localtime(&t);
        struct tm s=*c;
        node *n = new node(id,s,tmp,t);
        enfiler(n,f);
        i++;
        id++;
    }
    return f;
    /*etat(f,nbr_node);*/
    /*check(f);*/

}


int init_batch(){
    int temp,id=0;bool terminer=false;
    file *f = NULL;
    while(!terminer){
    system("CLS");
    cout<<"Menu:"<<endl;
    cout<<"1.inserer un processus"<<endl;
    cout<<"2.consulter la file d'attente"<<endl;
    cout<<"3.executer la sequence des processus"<<endl;
    cin>>temp;
    switch(temp){
        case 1 : id++ ;f=cree_file(id);
        break;
        case 2 : check(f);
        break;
        case 3 : executer(f); terminer=true;
        break;
        default : init_batch();
    }
}
}



int main(){

init_batch();
cout<<"terminer !";



}
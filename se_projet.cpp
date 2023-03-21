#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
using namespace std;
using std::string;


/*this is where i made the change*/
class node{
    public:
    int num_pross,tmp_arr,tmp_att,tmp_exe,tmp_sort,id;
    string etat;
    node *next;
    node(int id){
        this->tmp_att=0;
        this->tmp_arr=0;
        this->tmp_sort=0;
        this->id=id;
        this->num_pross=1+(rand()%100);
        this->etat="P";
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


void check(file *f){
    if (f){
    file F = *f;
    system("CLS");
    while(F.head){
        cout<<"etat de processus "<<F.head->getId()<<" : "<<F.head->getEtat()<<"      le temp d'arrive : "<<F.head->tmp_arr<<" seconds"<<endl;
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


void stat(file *f){
    if (f){
    file F = *f;
    while(F.head){
        cout<<"etat de processus "<<F.head->getId()<<" : "<<F.head->getEtat()<<"      le temp d'arrive : "<<F.head->tmp_arr<<" seconds"<<endl;
        F.head=F.head->next;
     }
    }
}


void etat(file *f){
    int temp_arrive=0,count=0;
    while(f->head){
     node *rem=defiler(f);
     rem->tmp_arr=temp_arrive;
     system("CLS");
     cout<<"etat de processus "<<rem->getId()<<" : "<<rem->getEtat()<<"      le temp d'arrive : "<<rem->tmp_arr<<" seconds"<<endl;
     stat(f);
     cout<<"le temp rest pour le processus actif : "<<rem->getTemp()<<" seconds";
     sleep(rem->getTemp());
     temp_arrive+=rem->getTemp();
     count++;
    }
    system("CLS");
    cout<<"le temp moyen d'attente : "<<temp_arrive/count<<" seconds"<<endl;

}


void executer(file *f){
     etat(f);

}


file *cree_file(int id){
    int tmp,nbr_node,i=0;
    file *f = new file(NULL,NULL);
    system("CLS");
    cout<<"le numero des processus?"<<endl;
    cin>>nbr_node;
    system("CLS");
    while(i<nbr_node){
        node *n = new node(id);
        cout<<"svp inserer le temp d'execution de processus "<<n->getId()<< " en second"<<endl;
        cin>>tmp;
        n->tmp_exe=tmp;
        enfiler(n,f);
        i++;
        id++;
    }
    return f;
    /*etat(f,nbr_node);*/
    /*check(f);*/

}


int init(){
    int temp;
    cout<<"ce program support just la politique FIFO en mode batch"<<endl;
    cout<<"Menu:"<<endl;
    cout<<"1.inserer un processus"<<endl;
    cout<<"2.consulter la file d'attente"<<endl;
    cout<<"3.executer la sequence des processus"<<endl;
    cin>>temp;
    return temp;
}


int main(){
    int choix,id=0;
    bool error = false,terminer=false;
    file *f= NULL;
        system("CLS");
        choix=init();
    switch(choix){
        case 1 : id++ ;cree_file(id);
        break;
        case 2 : check(f);
        break;
        case 3 : executer(f);
        break;
        default : error = true;
    }
    while(error || !terminer){
        system("CLS");
         choix=init();
    switch(choix){
        case 1 : id++; f=cree_file(id); error=false;
        break;
        case 2 : check(f);
        break;
        case 3 : executer(f); terminer = true;
        break;
    }
    }
cout<<"terminer !";
int neww;



}
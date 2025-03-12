/*
 * La 1,2 arborele binar
 * Am creat arborele alegand aleatoriu dintr-un vector radacina, am pus-o pe prima pozitie a vectorului apoi am inserat pe rand in arbore
 * Structul node este pentru arbore
 * La postorder iterativ nu am folosit memorie aditionala, O(n)
 * La postorder recursiv am folosit doua stive, una pentru a pastra nodurile de pe ramura parcursa si una pentru ordinea lor la afisare, O(h)- in caz average cu h- inaltimea si O(n)- pentru cel mai rau caz, arbore dezechilibrat
 *
 * La 3, 4, 5
 * In t1 mi-am declarat un vectori de noduri, l-am alocat si mi-am creat un nod pentru fiecare index
 * t1: R2 primeste valoarea radacinii, iar pana o gaseste face pe rand legaturile parinti - copii(sons)
 * t2: R3 primeste valoarea radacinii din R2, apoi in while verific daca nodul din stanga este ocupat, daca nu este pun primul copil, altfel adaug restul copiilor,daca mai sunt, in dreapta primului copil si apoi ma duc la urmatorul nod de la copilul din dreapta( primul copil al radacinii la inceput)
 * Ambele transformari au complexitatea O(n) si memoria aditionala O(n)
 */
#include <iostream>
#include <list>
#include <stack>
#include "Profiler.h"
using namespace std;
//int parent[]={-100,2,7,5,2,7,7,-1,5,2}

Profiler profiler;

struct node{
    int key;
    node* left;
    node* right;
};

struct node2{
    int key;
    list<node2*> sons; //lista copii
};

node2 *R2;
//node2 *R2const[500];//pentru liniar time - am declarat in functie

struct node3{
    int key;
    node3 *left, *right;//left - copil, right-frate
};

void t1(int *parent, node2 *&R2,int n){
    node2 **nodes=new node2*[n];

    for(int i=1;i<n;i++){
        nodes[i]=new node2;
        nodes[i]->key=i;
    }

    for(int i=1;i<n;i++){
        if (parent[i] == -1)
            R2 = nodes[i];
        else {
            nodes[parent[i]]->sons.push_back(nodes[i]);
        }
    }
    delete[] nodes;
}

void t2(node2 *R2,node3 *&R3){
    R3 = new node3;
    R3->key=R2->key;
    R3->left= nullptr;
    R3->right= nullptr;

    node3 *current_child= nullptr;

    for(auto it:R2->sons){
        node3 *new_child= nullptr;
        t2(it,new_child);

        if(!R3->left){
            R3->left=new_child;
        } else{
            current_child->right=new_child;
        }

        current_child=new_child;
    }
}

void pretty_print1(int parent[],int n,int tabs,int index_parent){ //prima data pasam indexul de la -1, in acest caz 7 --pentru R1
    for(int i=0;i<tabs;i++){
        cout<<"  ";
    }
    cout<<index_parent<<endl;
    for(int i=1;i<=n;i++){ //implementat de la 1 dupa ex
        if(parent[i]==index_parent){
            pretty_print1(parent,n,tabs+2,i);
        }
    }
}
void pretty_print2(node2 *R2,int tabs){
    if(R2){
        for(int i=0;i<tabs;i++){
            cout<<"  ";
        }
        cout<<R2->key<<endl;
        for(auto it:R2->sons){ //it-iterator
            pretty_print2(it,tabs+2);
        }
    }
}

void pretty_print3(node3 *R3,int tabs){
    if(R3){
        for(int i=0;i<tabs;i++){
            cout<<"  ";
        }
        cout<<R3->key<<endl;
        pretty_print3(R3->left,tabs+2);
        pretty_print3(R3->right,tabs);
    }
}

node* create_tree_demo(int a[],int n,int i){
    if(i>=n)
        return nullptr;

    node *root = new node;

    if(i==0){
        int random[2]={};
        FillRandomArray(random,2,1,n);
        swap(a[i],a[random[1]]);//radacina random
    }

    root->key = a[i];

    root->left = create_tree_demo(a, n, 2*i+1);
    root->right = create_tree_demo(a, n, 2*i+2);

    return root;
}
void postorder_recursiv(node *root,Operation &count){
    if(root){
        postorder_recursiv(root->left,count);
        postorder_recursiv(root->right,count);
        //cout<<root->key<<" ";
        count.count();
    }
}

void postorder_iterativ(node* root,Operation &count){
    if(root== nullptr)
        return;

    stack<node*> stack1,stack2;

    stack1.push(root);//dam push la radacina

    while (!stack1.empty()){ //cat timp avem noduri pe stiva
        node* current=stack1.top();
        stack1.pop();
        stack2.push(current);

        if(current->left){
            stack1.push(current->left);
        }
        if(current->right){
            stack1.push(current->right);
        }
    }

    while (!stack2.empty()){
       // cout<<stack2.top()->key<<" ";
        stack2.pop();
        count.count();
    }
}

void demo(){
    int parent[]={-100,2,7,5,2,7,7,-1,5,2};
    int n=sizeof(parent)/ sizeof(parent[0]);
    for(int i=0;i<10;i++){
        if(parent[i] == -1){
            pretty_print1(parent,n,0,i);
            break;
        }
    }

    R2= nullptr;
    t1(parent,R2,n);
    pretty_print2(R2,0);

    node3 *R3= nullptr;
    t2(R2,R3);
    pretty_print3(R3,0);

    int a[]={1,2,5,4,7,9,6,4,7,6};
    int n2= sizeof(a)/sizeof(a[0]);

    Operation count=profiler.createOperation("demo_count",n2); //pentru a avea aceeasi functie si pentru grafice
    node* root=create_tree_demo(a,n2,0);

    postorder_recursiv(root,count);
    cout<<endl;
    postorder_iterativ(root,count);
}

void perf(){
    for(int i=100;i<=10000;i+=100){
        int a[i];
        FillRandomArray(a,i,0,5000000,true,UNSORTED);
        node* root=create_tree_demo(a,i,0);

        Operation count_it=profiler.createOperation("iterativ_count",i);
        Operation count_rec=profiler.createOperation("recursiv_count",i);

        postorder_recursiv(root,count_rec);
        postorder_iterativ(root,count_it);

    }
    profiler.createGroup("Comp_it_rec","iterativ_count","recursiv_count");
    profiler.showReport();
}
int main() {
    demo();
    //perf();
    return 0;
}

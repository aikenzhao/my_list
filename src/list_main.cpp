/**********************************************************
 * Author        : Aiken.zhao
 * Email         : Aiken.zhao@goertek.com
 * Last modified : 2018-03-30 16:36
 * Filename      : list_main.cpp
 * Description   : 
 * *******************************************************/

#include<iostream>
#include"my_list.h"

int main(){
    
    char *a = new char[100];
    for(int i = 0; i < 100; i++){
        a[i] = i;
    }
    char *b = NULL;

    MyList *m = MyList::get_list(NULL);
    b = a;
    for(int i = 0; i < 11 ; i++){
       // for(int j = 0 ; j < 2 ; j++){
       //     cout<<"["<<(int)b[j]<<"]";
       // }
        m->write_data(b,2);
        b += 2;
    }
    m->print_data();
    // cout<<"P++++++"<<b<<endl;

   // m->print_list();
    char *c = NULL;
    for(int i = 0; i < 5 ; i++){
        cout<<"+++++++++++++"<<i<<endl;
        int tmp = m->read_data(&c);
       // cout<<"b :"<<(int )b<<endl;
        m->print_list();
       
        cout<<"tmp = "<<tmp<<endl;
        
        for(int j = 0 ; j < tmp ; j++){
            cout<<"["<<(int)c[j]<<"]";
        }
        cout<<endl;
    }
    m->print_data();

    for(int i = 0; i < 3 ; i++){
        m->write_data(b,2);
        b += 2;
    }
    m->print_data();
    return 0;

}

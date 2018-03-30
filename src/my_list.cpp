/**********************************************************
 * Author        : Aiken.zhao
 * Email         : 
 * Last modified : 2018-03-30 16:36
 * Filename      : my_list.cpp
 * Description   : 
 * *******************************************************/
#include"my_list.h"
#include<iostream>

MyList::MyList() : first(NULL), last(NULL), element_num(0),\
                       element_num_max(1000), element_num_min(0),\
                    pth_lock(NULL){
    cout<<"*************creat MyList success***********"<<endl;
    cout<<"*first element   : ";
    if(NULL == first){
        cout<<"NULL"<<endl;
    }else{
        cout<<(POINTER_DATA)first<<endl;
    }
    cout<<"*last element    : ";
    if( NULL == last){
        cout<<"NULL"<<endl;
    }else{
        cout<<(POINTER_DATA)last<<endl;
    }
    cout<<"*element_num     : "<<element_num<<endl;
    cout<<"*element_num_max : "<<element_num_max<<endl;
    cout<<"*element_num_min : "<<element_num_min<<endl;
    cout<<"*****************************************"<<endl;
}

MyList::MyList(pthread_mutex_t *p_lock) : first(NULL), last(NULL), element_num(0),\
                       element_num_max(1000), element_num_min(0), pth_lock(p_lock) {
    cout<<"*************creat MyList success***********"<<endl;
    cout<<"*first element   : ";
    if(NULL == first){
        cout<<"NULL"<<endl;
    }else{
        cout<<(POINTER_DATA)first<<endl;
    }
    cout<<"*last element    : ";
    if( NULL == last){
        cout<<"NULL"<<endl;
    }else{
        cout<<(POINTER_DATA)last<<endl;
    }
    cout<<"*element_num     : "<<element_num<<endl;
    cout<<"*element_num_max : "<<element_num_max<<endl;
    cout<<"*element_num_min : "<<element_num_min<<endl;
    cout<<"*****************************************"<<endl;
}
MyList::~MyList(){
    cout<<"deleat MyList"<<endl;
}

void MyList::delete_first(){//删除第一个
    if(NULL == this->pth_lock){
        cout<<"pth_lock is NULL, this unuse pthread mutex"<<endl;
    }else{
        pthread_mutex_lock(this->pth_lock);
    }

    DataElement *tem = this->first;
    if(element_num == 1){
        this->first = NULL;
        this->last = NULL;
    }else{
        this->first = this->first->next;
        this->first->prev = NULL;
    }
    this->element_num --;
    
    if(NULL != this->pth_lock){
        pthread_mutex_unlock(this->pth_lock);
    }

    delete tem;
}

void MyList::add_last(DataElement *ele){ 
    
    if(NULL == this->pth_lock){
        cout<<"pth_lock is NULL, this unuse pthread mutex"<<endl;
    }else{
        pthread_mutex_lock(this->pth_lock);
        cout<<"add lock"<<endl;
    }

    if(is_empty() == 1){
        this->first = ele;
    }else{
        this->last->next = ele;
        ele->prev = this->last;
    }
    this->last = ele;
    this->element_num += 1;//计数加1
    
    if(NULL != this->pth_lock){
        cout<<"add unlock"<<endl; 
        pthread_mutex_unlock(this->pth_lock);
        
    }
}

DataElement* MyList::creat_element(){
    DataElement *tmp = new DataElement;
    tmp->prev = NULL;
    tmp->next = NULL;
    tmp->data = NULL;
    tmp->data_len = 0;
    return tmp;
}


MyList *MyList::get_list(pthread_mutex_t *p_lock){
    return new MyList(p_lock);
}
void MyList::release(){//有待完善
    
}

int MyList::write_data(char *data, int data_len){
    //cout<<"write data"<<endl;
    if(is_full() == 1){
        cout<<"list is full"<<endl;
        delete_first();
    }
    
    //cout<<"cheack full"<<endl;
    
    //创建element
    DataElement *tmp = creat_element();
    tmp->data = data;
    tmp->data_len = data_len;
    //cout<<"creat element"<<endl;
    
    //添加element
    add_last(tmp);
  
    /*if(is_empty() == 1){
     //   this->last = tmp;
        this->first = tmp;
    }else{
        this->last->next = tmp;
        tmp->prev = this->last;
       /
   // this->last->next = tmp;
   // tmp->prev = this->last;

    this->last = tmp;
    
    this->element_num += 1;//计数加1
    */
    return 1;
}

int MyList::read_data(char** data){
    
    if(is_empty() == 1){
        cout<<"read_data fail!"<<endl;
        cout<<"list is empty!"<<endl;
        return 0;
    }

    *data = this->first->data;
    int data_len = this->first->data_len;

    delete_first();

    return data_len;
}

void MyList::print_list(){
    cout<<"**************Print_list My List ****************"<<endl;
    cout<<"*first element   : ";
    if(NULL == first){
        cout<<"NULL"<<endl;
    }else{
        cout<<(POINTER_DATA)first<<endl;
    }
    cout<<"*last element    : ";
    if( NULL == last){
        cout<<"NULL"<<endl;
    }else{
        cout<<(POINTER_DATA)last<<endl;
    }
    cout<<"*first data      : ";
    if(NULL == first){
        cout<<"NULL"<<endl;
    }else{
        cout<<(POINTER_DATA)first->data<<endl;
    }
    cout<<"*last data        : ";
    if( NULL == last){
        cout<<"NULL"<<endl;
    }else{
        cout<<(POINTER_DATA)last->data<<endl;
    }
    cout<<"*element_num     : "<<element_num<<endl;
    cout<<"*element_num_max : "<<element_num_max<<endl;
    cout<<"*element_num_min : "<<element_num_min<<endl;

    cout<<"*pth_lock        : ";
    if(NULL == this->pth_lock){
        cout<<"NULL"<<endl;
    }else{
        cout<<"has lock"<<endl;
    }

    cout<<"*****************************************"<<endl;
}

int MyList::cheack_list(){
    //检查互斥锁
    cout<<"*pth_lock        : ";
    if(NULL == this->pth_lock){
        cout<<"NULL"<<endl;
    }else{
        cout<<"has lock"<<endl;
    }


    if(NULL  == this->last ){//空的
        cout<<"******cheack NULL********"<<endl;
        if(NULL == this->first){
            if(0 == element_num ){
                cout<<"this list is empty"<<endl;
                return 1;
            }
            cout<<"element is not rigth "<<endl;
            return 0;
        }
        cout<<"first is not NULL "<<endl;
        return 0;
    }
    
    //检查开头和结尾

    if(NULL != this->last->next){
        cout<<"*WRONG*  : last->next is not NULL"<<endl;
        this->last->next = NULL;
    }
    if(NULL != this->first->prev){ 
        cout<<"*WRONG*  : first->prev is not NULL"<<endl;
        this->first->prev = NULL;
    }
    
    //检查num是否正确
    int tmp = 0;
    DataElement *td = NULL;
    
    td = this->first;
    while(NULL != td){
        tmp++;
        td = td->next;
        if(tmp > element_num){
            cout<<"*ERROR* : element_num is not right , too small!!"<<endl;
            return 0;
        }
    }

    if(tmp == element_num){
        cout<<"element_num is right"<<endl;
        return 1;
    }
    cout<<"*ERROR* : element_num is not right , too big!!"<<endl;
    return 0;

}

int MyList::is_full(){
//    if(cheack_list() != 1){
//        cout<<"MyList is wrong"<<endl;
//        return 0;
//    }

    if(element_num >= element_num_max){
        //cout<<"MyList is full!!"<<endl;
        return 1;
    }
    return 0;
}
int MyList::is_empty(){
    if(element_num <= 0){
        //cout<<"MyList is empty"<<endl;
        return 1;
    }
    return 0;
}

void MyList::print_data(){
    print_list();
    DataElement *tmp = this->first;
    for(int i = 0; i < this->element_num; i++){
        int len = tmp->data_len;
        for(int j = 0; j < len; j++){
            cout<<"["<<(POINTER_DATA)tmp->data[j]<<"]";
        }
        cout<<"---->"<<len<<endl;
        tmp = tmp->next;
    }
    
}

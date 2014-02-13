#include "ConcurrentLinkedList.h"


ListNode * getNewListNode(){
    ListNode * node = malloc(sizeof(ListNode));
    return node;
}

ConcurrentLinkedList * getNewList(){
    ConcurrentLinkedList * list = malloc(sizeof(ConcurrentLinkedList));
    list->head=getNewListNode();
    list->size=0;
    pthread_mutex_init(&(list->lock), NULL);
    return list;
}

void destroyList(ConcurrentLinkedList * list){
    pthread_mutex_lock(&list->lock);
    ListNode * current = list->head;
    ListNode * prev;
    while(current != NULL){
        prev=current;
        current = current->nextNode;
        free(prev);
    }
    pthread_mutex_unlock(&list->lock);
    pthread_mutex_destroy(&(list->lock));
}

void addElement(ConcurrentLinkedList * list, void * E){
    if(list == NULL){
        list = getNewList();
    }
    pthread_mutex_lock(&list->lock);
    ListNode * current=list->head;
    if(list->size == 0){
        current->Element = E;
    }else{
        ListNode * tempNode = getNewListNode();
        tempNode->Element = E;
        tempNode->nextNode = current;
        list->head = tempNode;
    }
    list->size++;   
    pthread_mutex_unlock(&list->lock);
}

void removeElement(ConcurrentLinkedList * list, void * E){
    pthread_mutex_lock(&list->lock);
    if(list->size==0)
        return;
    ListNode * current=list->head;
    ListNode * prev;
    if(current->Element == E){
        if(list->size == 1){
            current->Element=NULL;
        }else{
            list->head = current->nextNode;
        }
    }else{
        while(current->Element != E && current != NULL ){
            prev = current;
            current = current->nextNode;
        }
        if(current == NULL){
            pthread_mutex_unlock(&list->lock);
            return;
        }else{
            if(current->nextNode == NULL){
                prev->nextNode=NULL;
                free(current);
            }else{
                prev->nextNode = current->nextNode;
                free(current);
            }            
        }
    }
    list->size--;
    pthread_mutex_unlock(&list->lock);
}
void * getElement(ConcurrentLinkedList * list, int index){
    pthread_mutex_lock(&list->lock);
    int idx=index;
    void * result = NULL;
    ListNode * current = list->head;
    while(idx > 0 && current != NULL){
        current = current->nextNode;
        idx--;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sorted-list.h"

/*
 * Creates the sorted list, allocating space for it, CompareFuncT,
 * DestructFuncT, the head of the list, and "next". It also initializes
 * head, next, and numPtr.
 */
SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df) {
    SortedListPtr SL = (SortedListPtr)malloc(sizeof(SortedList));
    SL->CompareFuncT = (CompareFuncT)malloc(sizeof(CompareFuncT));
    SL->CompareFuncT = cf;
    SL->DestructFuncT = (DestructFuncT)malloc(sizeof(DestructFuncT)); 
    SL->DestructFuncT = df;
    SL->head = (SortedListPtr)malloc(sizeof(SortedListPtr));
    SL->head = NULL;
    SL->next = (SortedListPtr)malloc(sizeof(SortedListPtr));
    SL->next = NULL;
    SL -> numPtr = 0;
    return SL;
}

/*
 * Will insert nodes into sorted list, or create a head for new sorted 
 * list. Return 1 if successful, 0 if any other case. The sorted list is 
 * in descending order.
 */
int SLInsert(SortedListPtr list, void *newObj) {

    SortedListPtr temp = (SortedListPtr) malloc(sizeof(SortedList));

    temp->data = newObj;
    temp->numPtr+=1;
   
    if (list->head == NULL) {
        list->head = temp;
        return 1;
    }
    else {
        if (list->CompareFuncT(list->head->data, newObj) < 0) { /*If the new object is greater than the head's data*/
            temp->next = list->head;
            list->head = temp;
            return 1;
        }
        else if (list->CompareFuncT(list->head->data, newObj) == 0) {  //Head and newObj is equal no need to insert data
            return 0;
        }
        else if (list->CompareFuncT(list->head->data, newObj) > 0 && list->head->next == NULL) { /*If the head's data is greater than the new object*/
            list->head->next = temp;
            return 1;
        }
        else {
            SortedListPtr curr = list->head; /*Points to the head of the list*/
            SortedListPtr prev = NULL; /*Initializes prev pointer*/
            while (curr->next != NULL) { /*While the pointer is not null*/
                int comp = list->CompareFuncT(curr->next->data, newObj); /*Stores the result of the comparison between curr->next's data and the new object in an int*/
                prev = curr; /*Makes the previous pointer the current pointer*/
                if (comp < 0) { /*If curr->next's data is less than the new object*/

                    temp->next = prev->next;
                    prev->next = temp;
                    return 1;
                }
                else if (comp == 0) { /*If curr->next's data is equal to the new object*/
                    return 0;
                }
                else { /*If curr->next's data is greater than the new object*/
                    if (curr->next->next == NULL) { /*If curr->next->next is null*/
                        curr->next->next = temp; /*curr->next->next is temp*/
                        return 1;
                    }
                    else { /*If curr->next->next is not null*/
                        curr = curr->next; /*Moves on to the next pointer and continues the loop*/
                    }
                }
            }
            return 0;
        }
    }
}

/*
 * Will remove nodes from the sorted list if their data matches the data 
 * that is specified. Returns 1 if successful, 0 if any other case. 
 */
int SLRemove(SortedListPtr list, void *newObj) {
    if (list->head == NULL) { /*If the list has nothing in it*/
        return 0; /*Nothing can be deleted*/
    }
    else { /*If the list's head has data*/
        if (list->CompareFuncT(list->head->data, newObj) < 0) { /*If the head's data is smaller than the new object*/
            return 0; /*Nothing can be deleted*/
        }
        else if (list->CompareFuncT(list->head->data, newObj) == 0) {  /*If the head's data and the new object are equal*/
            if (list->head->next == NULL) { /*If there is nothing after the head*/
                if (list->head->numPtr == 1) {      //if head is is only referenced by head
                    list->DestructFuncT(list->head);
                }
                list->head = NULL; /*Makes the head null*/  
                return 1;
            }
            else { /*If there is something after the head*/
                SortedListPtr temp = list->head;
                list->head = list->head->next; /*Makes the item after the head the new head*/
                temp->numPtr-=1;
                if (temp->numPtr == 0) {            
                    list->DestructFuncT(temp);
                }
                else {
                    list->head->numPtr+=1;
                }
                return 1;
            }
        }
        else { /*If the head's data is greater than the new object*/
            if (list->head->next == NULL) { /*If there is nothing after the head*/
                return 0; /*Nothing can be deleted*/
            }
            else { /*If there is something after the head*/
                SortedListPtr curr = list->head; /*Points to the head of the list*/
                SortedListPtr prev = NULL; /*Initializes prev pointer*/
                while (curr->next != NULL) { /*While the pointer is not null*/
                    int comp = list->CompareFuncT(curr->next->data, newObj); /*Stores the result of the comparison between curr->next's data and the new object in an int*/
                    SortedListPtr temp = curr->next;
                    prev = curr; /*Makes the previous pointer the current pointer*/
                    if (comp < 0) { /*If curr->next's data is less than the new object*/
                        return 0; /*Nothing can be deleted*/
                    }
                    else if (comp == 0) { /*If curr->next's data is equal to the new object*/
                        prev->next = prev->next->next; /*Makes prev->next->next the item immediately following prev*/
                        temp->numPtr-=1;
                        if (temp->numPtr==0) {
                            list->DestructFuncT(temp);
                        }
                        else if (temp->next != NULL) {
                                temp->next->numPtr+=1;      //if its not null, incrememnt ptr. 
                        }
                        return 1;
                    }
                    else { /*If curr->next's data is greater than the new object*/
                        if (curr->next->next == NULL) { /*If curr->next->next is null*/
                            return 0; /*Nothing can be deleted*/
                        }
                        else { /*If curr->next->next is not null*/
                            curr = curr->next; /*Moves on to the next pointer and continues the loop*/
                        }
                    }
                }
            }
            return 0;
        }
    }
}

/*
 * Creates a sorted list iterator, allocating space for it if the sorted 
 * list exists and has a head, and making it point to the head of the list, 
 * incrementing numPtr by 1. It also allocates space for DestructFuncT, which 
 * points to the sorted list's DestructFuncT.
 */
SortedListIteratorPtr SLCreateIterator (SortedListPtr list) {
    SortedListIteratorPtr iter;
    if (list == NULL || list->head == NULL)
        return NULL;
    else {
        iter = (SortedListIteratorPtr) malloc(sizeof(struct SortedListIterator));
        iter->DestructFuncT = (DestructFuncT)malloc(sizeof(DestructFuncT));
        iter->DestructFuncT = list->DestructFuncT;
        iter->CurrNode = list->head;
        iter->CurrNode->numPtr+=1;
    }
    return iter;
}

/*
 * Goes to the node in the list that a given iterator pointing to. If it 
 * doesn't exist, return 0, else return that node's data.
 */
void* SLGetItem(SortedListIteratorPtr iter) {
    if (iter == NULL)
        return 0;
    SortedListPtr temp = iter->CurrNode;
    if (temp == NULL){
        return 0;
    }
    else { 
        return temp->data;
    }
}

/*
 * Goes to the node in the list that follows the node that a given iterator
 * is pointing to. If it exists, the iterator will point to that node, and
 * numPtr for that node will increase by one. numPtr for the node that the
 * iterator was previously pointing to will decrease by 1, and if the 
 * resulting numPtr is 0, then that node will be destroyed. numPtr for the
 * current node will decrease by 1, and its data will be returned. If the
 * node does not exist, the iterator will point to nothing, and numPtr for
 * the node that it was previously pointing to will decrease by 1. If the
 * resulting numPtr is 0, then that node will be destroyed. NULL is returned.
 */
void * SLNextItem(SortedListIteratorPtr iter) {
    SortedListPtr temp = iter->CurrNode;
    if (temp->next == NULL) {          
        iter->CurrNode = NULL;
        temp->numPtr-=1;
        if (temp->numPtr == 0)
            iter->DestructFuncT(temp);
        return NULL;
    }
    else {
        iter->CurrNode = temp->next;
        iter->CurrNode->numPtr+=1;
        temp->numPtr-=1;
        if (temp->numPtr == 0){
            iter->CurrNode->numPtr-=1;
            iter->DestructFuncT(temp);
        }
        return iter->CurrNode->data;
    }
}

/*
 * Destroys a sorted list when called.
 */
void SLDestroy(SortedListPtr list) {
    free(list);
}

/*
 * Destroys an iterator when called.
 */
void SLDestroyIterator(SortedListIteratorPtr iter) {
    free(iter);
}

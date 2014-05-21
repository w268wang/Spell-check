//CS 136 Assignment 10 Problem 3
//Wang, Weijie ID: 20505037

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

struct llnode {
   char *item;
   struct llnode *next;
};

struct strqueue {
   struct llnode *front;
   struct llnode *back;
   int length;
};
typedef struct strqueue *StrQueue;

// see strqueue.h documentation
StrQueue create_StrQueue(void){

   StrQueue temp = malloc(sizeof(struct strqueue));
   temp->front = NULL;
   temp->back = NULL;
   temp->length = 0;
   return temp;

}


// see strqueue.h documentation
void destroy_StrQueue(StrQueue sq) {

   struct llnode *current = sq->front; 
	struct llnode *next;
	while (current!=NULL) {
		next = current->next;
		free(current->item);
		free(current);
		current = next;
	}
	sq->back = NULL;
	sq->front = NULL;
	free(sq);

}


// see strqueue.h documentation
void sq_add_back(StrQueue sq, const char *str) {
   
   sq->length++;
   struct llnode *temp = sq->back;
   sq->back = malloc(sizeof(struct llnode));
   sq->back->item = malloc(sizeof(char)*(strlen(str)+1));
   strcpy(sq->back->item, str);
   sq->back->next = NULL;
   if(sq->length == 1) {
      sq->front = sq->back;
   } else {
      temp->next = sq->back;
   }
   
}


// see strqueue.h documentation
char *sq_remove_front(StrQueue sq) {
   
   if(sq->length==0) return NULL;
   sq->length--;
   struct llnode *temp = sq->front;
   char *this_item = temp->item;
   sq->front = temp->next;
   if(sq->length == 0) {
      sq->back = NULL;
   }
   free(temp);
   return this_item;

}


// see strqueue.h documentation
int sq_length(StrQueue sq) {
   return sq->length;
}



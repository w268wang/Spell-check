//CS 136 Assignment 10 Problem 1
//Wang, Weijie ID: 20505037

// spellcheck.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "dictionary.h"
#include "file2strqueue.h"


const char apostrophe = '\'';


int strcmp_wrapper(const void *a, const void *b) {
  assert(a);
  assert(b);
  const char *str_a = a;
  const char *str_b = b;
  return strcmp(str_a, str_b);
}


int valid = 1;
void *VALID = &valid;

void do_nothing(void *p) {
  return;
}

bool only_letter(char *c) {
   for(int i=0; c[i]!='\0'; i++) {
      char temp = c[i];
      if((temp!=apostrophe&&temp<'A')||(temp>'Z'&&temp<'a')
      ||temp>'z') return false;
   }
   return true;
}

char *lowercase(char *c){
   char *temp = malloc(sizeof(char *)*(strlen(c)));
   strcpy(temp, c);
   for(char *p = temp;*p;++p) if(*p>64&&*p<91) *p+=32;
   return temp;
}

int main(void) {

   Dictionary wordlist = create_Dictionary(strcmp_wrapper, free, do_nothing);
   StrQueue sq = file2StrQueue("wordlist.txt");
  
   while (sq_length(sq)) {
      char *word = sq_remove_front(sq);
      insert(wordlist, word, VALID); 
   }
  
   destroy_StrQueue(sq);
   sq = NULL;
   


   Dictionary autocorrect = create_Dictionary(strcmp_wrapper, free, free);
   sq = file2StrQueue("autocorrect.txt");
   
   while (sq_length(sq)) {
    char *word = sq_remove_front(sq);
    char *word2 = sq_remove_front(sq);
    insert(autocorrect, word, word2);
   }
   
   destroy_StrQueue(sq);
   sq = NULL;
   
   sq = file2StrQueue(NULL);
   for(int i=1; sq_length(sq); i++) {
   
      char *word = sq_remove_front(sq);
      char *lower = lowercase(word);
      if (!only_letter(word)) {
         printf( "_%s_", word);
      } else {
         char *ac = lookup(autocorrect, word);
         if (lookup(wordlist, lower)==VALID) {
            printf("%s", word);
         } else if (ac!=NULL) {
            printf("*%s*", ac);
         } else {
            printf("[%s]", word);
         }
      }
      if(i%10==0||sq_length(sq)==0) {
         printf("\n");
      } else {
         printf(" ");
      }
      free(lower);
      free(word);
      
   }
   printf("\n");
   
   
   destroy_StrQueue(sq);
   sq = NULL;
   destroy_Dictionary(wordlist);
   destroy_Dictionary(autocorrect);
}

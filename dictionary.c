//CS 136 Assignment 10 Problem 4
//Wang, Weijie ID: 20505037

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

struct bstnode {
   void *key;
   void *value;
   struct bstnode *left;
   struct bstnode *right;
};

typedef int (*CompareFunction)(const void *, const void *);
typedef void (*FreeFunction)(void *);

struct dictionary {
   struct bstnode *root;
   CompareFunction comp;
   FreeFunction freekey;
   FreeFunction freevalue;
};
typedef struct dictionary *Dictionary;


// see dictionary.h documentation
Dictionary create_Dictionary(CompareFunction comp_k, FreeFunction free_k, FreeFunction free_v) {

   Dictionary temp = malloc(sizeof(struct dictionary));
   temp->root = NULL;
   temp->comp = comp_k;
   temp->freekey = free_k;
   temp->freevalue = free_v;
   return temp;
   
}

void destroy_node(struct bstnode *t, FreeFunction free_k, FreeFunction free_v) {
	if (NULL == t) {return;}
	free_k(t->key);
	free_v(t->value);
	destroy_node(t->left, free_k, free_v);
	destroy_node(t->right, free_k, free_v);
	free(t);
}

// see mmstack.h documentation
void destroy_Dictionary(Dictionary dict) {

   destroy_node(dict->root, dict->freekey, dict->freevalue);
   free(dict);

}


// see mmstack.h documentation
void insert(Dictionary dict, void *k, void *v) {

   if (dict->root==NULL) {
      dict->root = malloc(sizeof(struct bstnode));
      dict->root->key = k;
      dict->root->value = v;
      dict->root->left = NULL;
      dict->root->right = NULL;
      return;
   }
   
   struct bstnode *temp = dict->root;
   
   while(1) {
      if (dict->comp(k, temp->key)==0) {
         dict->freevalue(temp->value);
         temp->value = v;
         return;
      } else if (dict->comp(k, temp->key)<0) {
         if(temp->left==NULL) {
            temp->left = malloc(sizeof(struct bstnode));
            temp->left->value = v;
            temp->left->key = k;
            temp->left->left = NULL;
            temp->left->right = NULL;
            return;
         }
         temp = temp->left;
      } else {
         if(temp->right==NULL) {
            temp->right = malloc(sizeof(struct bstnode));
            temp->right->value = v;
            temp->right->key = k;
            temp->right->left = NULL;
            temp->right->right = NULL;
            return;
         }
         temp = temp->right;
      }
   } 

}


// see mmstack.h documentation
void *lookup(Dictionary dict, void *k) {
   
   struct bstnode *temp = dict->root;
   
   while(1) {
      if(temp==NULL) {
         return NULL;
      } else if (dict->comp(k, temp->key)==0) {
         return temp->value;
      } else if (dict->comp(k, temp->key)<0) {
         temp = temp->left;
      } else {
         temp = temp->right;
      }
   } 

}



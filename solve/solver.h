#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <pthread.h>
#define MEM_LIMIT 64000000
#define error(m, c) do{fprintf(stderr, "%s\n", m);exit(c);}while(0)
#define BINS 101
struct node {
  struct node *next;
  char *value;
};
typedef struct node node;
typedef struct {
  node **table;
  int size;
  int bins;
} hashset;
struct tnode{
	char* value;
	struct tnode* left;
	struct tnode* right;
};
typedef struct tnode tnode;//tnode is my binary tree node typedef
//hash set functions
int search(hashset h, char *val);
int insert(hashset *h, char *val);
hashset set_init();
//bst functions
tnode* talloc();
void inorder_print(tnode* root);
int bst_insert(tnode** root_p, char* val);
typedef struct{
     char** subpuzzle; //this is part of the char*** buffer that you want a single solver thread to solve
     int min_len;//this is the first integer passed after -len flag in the command-line argument: minimum length of puzzle solution
     int max_len;//this is the second integer passed after -len flag in the command-line argument: minimum length of puzzle solution
     int line;//the line number which the subpuzzle is taken from. Used for printing line span on the output.
     int col;//the column number which the subpuzzle is taken from. Used for printing column span on the output.
     int subpuzzle_lines;//determines the height (# of rows/lines) of current subpuzzle that the solver thread must solve
     int subpuzzle_cols;//determines the width (# of cols) of current subpuzzle that the solver thread must solve
     int t_id;//the id of thread. Used for printing it on the output along with the puzzle solution
}info;
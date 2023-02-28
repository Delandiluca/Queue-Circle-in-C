#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct Queue {
  int init;
  int end;
  int size;
  char *object;
} Queue; 


int isFull(Queue p);
int isEmpty(Queue p);
void createEmptyQueue(Queue *p);
int isOpenOperator(char c);
int isCloseOperator(char c); 
void push(Queue *p, char elem);
char pop(Queue *p);
char peek(Queue *p);
void printQueue(Queue *p);
int validateOperator(char *op, Queue *p);


void createEmptyQueue(Queue *p) {
  p->init = 0;
  p->end = 0;
  p->object = (char *)malloc(MAX_SIZE * sizeof(char));
}

int isEmpty(Queue p) {
  return ((p.init == p.end));
}

int isFull(Queue p) {
  return ((p.end + 1) == p.init);
}

void push(Queue *p, char elem) {
  if (!isFull(*p)) {
    p->object[p->end] = elem;
    int nextPos = ((p->end + 1) % MAX_SIZE);
    p->end = nextPos;
  } else {
    puts("\nError: Stack Overflow");
    exit(1);
  }
}

char pop(Queue *p) {
  if (!isEmpty(*p)) {
    char element = p->object[p->init];
    int nextPos = ((p->end + 1) % MAX_SIZE);
    p->init = nextPos;
    return element;
  } else {
    puts("\nError: Stack Underflow");
    exit(1);
  }
}

char peek(Queue *p) {
  if(isEmpty(*p)){
    puts("LISTA VAZIA!!");
  }
  return p->object[p->init];
}

void printQueue(Queue *p) {
  if (!isEmpty(*p)) {
    for (int i = 0; p->init <= i <= p->end; i++) {
      printf("\nCaracter %c ", p->object[i]);
    }
  } else {
    puts("\nError: Stack Empty");
    exit(1);
  }
}

int isOpenOperator(char c) {
  return (c == '(' || c == '{' || c == '[' || c == '<');
}

int isCloseOperator(char c) {
  return (c == ')' || c == '}' || c == ']' || c == '>');
}

int validateOperator(char *op, Queue *p) { 
  int i;
  for (i = 0; i < strlen(op); i++) {
    if (isOpenOperator(op[i])) {
      push(p, op[i]);
    } else if (isCloseOperator(op[i])) {
      if (!isEmpty(*p)) {
        char popped = pop(p);
        if ((op[i] == ')' && popped != '(') ||
            (op[i] == '}' && popped != '{') ||
            (op[i] == ']' && popped != '[') ||
            (op[i] == '>' && popped != '<')) {
          return 0;
        }
      } else {
        return 0;
      }
    }
  }
  return isEmpty(*p);
}

int main(void) {

  Queue queue;

  while (1) {
    createEmptyQueue(&queue);

    char operators[MAX_SIZE];
    puts("\nInsira a operação: ");
    scanf("%s", operators);

    printf("\nOperação %s",
           (validateOperator(operators, &queue)) ? "Válida" : "Inválida");
  }

  return 0;
}

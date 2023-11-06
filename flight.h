typedef struct FFlight flight;
typedef struct LLNode Node;

struct FFlight{
  char* place;
  int num;
  int arrive;
  int depart;
}FFlight;

struct LLNode {
  flight* fly;
  Node * next;
}LLNode;

Node * makeNode(flight* n, Node * nextItem);
flight* makeFlight(char* p, int n, int a, int d);
Node* makeList(Node* flights, FILE *fp);
void printFlights(Node* flights);
Node* addNode(Node * flights, char* c, int n, int a, int d);
Node* delete(Node * flights, int num);
void save(Node * flights, char * name);
void freeNode(Node * out);

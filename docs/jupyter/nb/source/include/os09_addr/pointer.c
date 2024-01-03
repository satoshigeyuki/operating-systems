#com 4
#ifpy VER == 1
int deref_int(int * a) {
  return *a;
}
long deref_long(long * a) {
  return *a;
}
#elifpy VER == 2
int idx_int(int * a, long i) {
  return a[i];
}
long idx_long(long * a, long i) {
  return a[i];
}
#elifpy VER == 3
typedef struct node {
  struct node * next;
  long x;
} node_t;
long chase(node_t * a) {
  long s = 0;
  for (node_t * p = a; p; p = p->next) {
    s += p->x;
  }
  return s;
}
#elifpy VER == 4
int main() {
  char * p = 918;
  return *p;
}
#endifpy

#include <stdio.h>
#include <stdlib.h>

#ifdef MAX
#undef MAX
#endif

#define MAX(a, b) ((a) > (b) ? (a) : (b))

struct node {
  int key, height, val;
  struct node *left;
  struct node *right;
};

typedef struct node node_t;

node_t *node_new(int key) {
  node_t *n = malloc(sizeof(node_t));
  if (!n)
    return NULL;
  n->height = 1;
  n->key = key;
  n->val = 0;
  n->left = NULL;
  n->right = NULL;
  return n;
}

int node_height(node_t *node) {
  if (node == NULL)
    return 0;
  return node->height;
}

node_t *node_left_rotate(node_t *n) {
  node_t *r = n->right;
  node_t *rl = r->left;
  r->left = n;
  n->right = rl;

  r->height = MAX(node_height(r->left), node_height(r->right)) + 1;
  n->height = MAX(node_height(n->left), node_height(n->right)) + 1;
  return r;
}

node_t *node_right_rotate(node_t *n) {
  node_t *l = n->left;
  node_t *lr = l->right;
  l->right = n;
  n->left = lr;

  l->height = MAX(node_height(l->left), node_height(l->right)) + 1;
  n->height = MAX(node_height(n->left), node_height(n->right)) + 1;
  return l;
}

node_t *node_insert(node_t *node, node_t **up, int key) {
  if (node == NULL) {
    *up = node_new(key);
    return *up;
  }

  if (node->key < key) {
    node->right = node_insert(node->right, up, key);
    *up = node->right;
  } else if (node->key > key) {
    node->left = node_insert(node->left, up, key);
    *up = node->left;
  } else {
    *up = node;
    return *up;
  }

  node->height = 1 + MAX(node_height(node->left), node_height(node->right));
  int balance = node_height(node->left) - node_height(node->right);
  if (balance > 1) {
    if (key > node->left->key)
      node->left = node_left_rotate(node->left);
    return node_right_rotate(node);
  }

  if (balance < -1) {
    if (key > node->right->key)
      node->right = node_right_rotate(node->right);
    return node_left_rotate(node);
  }

  return node;
}

node_t *node_find(node_t *root, int key) {
  if (root == NULL)
    return NULL;

  if (root->key < key)
    return node_find(root->right, key);
  else if (root->key > key)
    return node_find(root->left, key);
  else
    return root;
}

// Print the tree
void node_print(node_t *root) {
  if (root != NULL) {
    printf("%d ", root->key);
    node_print(root->left);
    node_print(root->right);
  }
}

int main() {
  node_t *root = NULL;
  node_t *n = NULL;
  char c;
  int v, max_v;
  int max = 0;
  scanf("nums = [");
  while (scanf("%d%c", &v, &c)) {
    root = node_insert(root, &n, v);
    if (++n->val > max) {
      max = n->val;
      max_v = n->key;
    }
    if (c == ']')
      break;
  }

  printf("%d", max_v);
}

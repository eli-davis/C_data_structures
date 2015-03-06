#include <iostream>


string to_lower(string s)
{ for (int i = 0; s[i]; i += 1)
    if (s[i] >= 'A' && s[i] <= 'Z')
      s[i] += 'a' - 'A';
  return s; }

struct node
{ string s;
  node * left;
  node * right; };

node * create_node(string str, node * l = NULL, node * r = NULL)
{ node * n = new node;
  n->s = str;
  n->left = l;
  n->right = r;
  return n; }

class binary_tree
{ private:
    node * root;
    int n_items;
    node * add(string, node *);
    bool is_in_tree(string, node *);
    void print(node *);
    void delete_node(node *);
  public:
      binary_tree();
      binary_tree(string);
      ~binary_tree();
    int size();
    void add(string);
    bool is_in_tree(string);
    void print(); };

binary_tree::binary_tree()
{ root = NULL;
  n_items = 0; }

binary_tree::binary_tree(string s)
{ root = create_node(s);
  n_items = 1; }

binary_tree::~binary_tree()
{ delete_node(root); }

void binary_tree::delete_node(node * n)
{ if (n)
  { delete_node(n->left);
    delete_node(n->right);
    delete n; } }

int binary_tree::size()
{ return n_items; }

void binary_tree::add(string s)
{ if (root)
    add(s, root);
  else
  { root = create_node(s);
    n_items = 1; } }

node * binary_tree::add(string s, node * n)
{ n_items += 1;
  if (!n)
    return create_node(s);
  else if (to_lower(s) < to_lower(n->s))
    n->left = add(s, n->left);
  else
    n->right = add(s, n->right);
  return n; }

bool binary_tree::is_in_tree(string s)
{ return is_in_tree(s, root); }

bool binary_tree::is_in_tree(string s, node * n)
{ if (!n)
    return false;
  else if (to_lower(s) == to_lower(n->s))
    return true;
  else if (to_lower(s) < to_lower(n->s))
    return is_in_tree(s, n->left);
  else
    return is_in_tree(s, n->right); }

void binary_tree::print()
{ print(root); }

void binary_tree::print(node * n)
{ if (n)
  { print(n->left);
    cout << n->s << "\n";
    print(n->right); } }

void test_one()
{ cout << "case insensitive binary tree of strings:\n\n";
  binary_tree B;
  B.add("yoo");
  B.add("whats");
  B.add("up");
  B.add("brotha");
  B.add("AAA");
  B.add("cryptic");
  B.add("random");
  B.add("zzzz");
  B.print();
  cout << "\n\n";
  string x = "yoo";
  if (B.is_in_tree(x))
    cout << x << " IN TREE\n";
  else
    cout << x << " NOT IN TREE\n";
  x = "dog";
  if (B.is_in_tree(x))
    cout << x << " IN TREE\n";
  else
    cout << x << " NOT IN TREE\n"; }

int main()
{ test_one(); }

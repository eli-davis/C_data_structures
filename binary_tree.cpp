#include <iostream>

char * to_lower(char * s)
{
    for (int i = 0; s[i]; i += 1)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] += 'a' - 'A';
        }
    }
    return s; 
}

struct node { 
    char * s;
    node * left;
    node * right; 
};

node * new_node(char * c_string, node * l = NULL, node * r = NULL)
{ 
    node * n = new node;
    n->s = c_string;
    n->left = l;
    n->right = r;
    return n; 
}

class binary_tree { 
    node * root;
    int n_items;
    node * add(char *, node *);
    bool is_in_tree(char *, node *);
    void print(node *);
    void delete_node(node *);
public:
    binary_tree();
    binary_tree(char *);
    ~binary_tree();
    int size();
    void add(char *);
    bool is_in_tree(char *);
    void print(); 
};

binary_tree::binary_tree()
{ 
    root = NULL;
    n_items = 0; 
}

binary_tree::binary_tree(char * s)
{ 
    root = new_node(s);
    n_items = 1; 
}

binary_tree::~binary_tree()
{ 
    delete_node(root); 
}

void binary_tree::delete_node(node * n)
{ 
    if (n)
    {
        delete_node(n->left);
        delete_node(n->right);
        delete n; 
    } 
}

int binary_tree::size()
{ 
    return n_items; 
}

void binary_tree::add(char * s)
{ 
    n_items += 1;
    if (root == NULL)
    {
        root = new_node(s); 
    }
    else
    {
        add(s, root);
    }
}

node * binary_tree::add(char * s, node * n)
{ 
    if (!n)
    {
        return new_node(s);
    }
    else if (to_lower(s) < to_lower(n->s))
    {
        n->left = add(s, n->left);
    }
    else
    {
        n->right = add(s, n->right);
    }
    return n; 
}

bool binary_tree::is_in_tree(char * s)
{ 
    return is_in_tree(s, root); 
}

bool binary_tree::is_in_tree(char * s, node * n)
{ 
    if (n == NULL)
    {
        return false;
    }
    else if (to_lower(s) == to_lower(n->s))
    {
        return true;
    }
    else if (to_lower(s) < to_lower(n->s))
    {
        return is_in_tree(s, n->left);
    }
    else
    {
        return is_in_tree(s, n->right);
    }
}
void binary_tree::print()
{ 
    print(root); 
}

void binary_tree::print(node * n)
{ 
    if (n)
    { 
        print(n->left);
        cout << n->s << "\n";
        print(n->right); 
    } 
}

void test_one()
{ 
    cout << "case insensitive binary tree of c_strings:\n\n";
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
    cout << "\ntree has " << B.size() << " items\n\n";
    const char * x = "yoo";
    if (B.is_in_tree(x))
    {
        cout << x << " IN TREE\n";
    }
    else
    {
        cout << x << " NOT IN TREE\n";
    }
    const char * y = "dog";
    if (B.is_in_tree(x))
    {
        cout << x << " IN TREE\n";
    }
    else
    {
        cout << x << " NOT IN TREE\n"; 
    }
}

int main()
{ 
    test_one(); 
}

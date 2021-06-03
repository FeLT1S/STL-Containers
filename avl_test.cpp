#include <iostream>

template<typename T>
class avl_tree {
	struct node
	{
		T key;
		unsigned char height;
		node* left;
		node* right;
		node* parent;
		node() {key = 0; left = right = 0; height = 1; parent = 0;}
		node(int k) { key = k; left = right = 0; height = 1; parent = 0;}
	};

	node *root;
public:
	avl_tree() : root(NULL) {}
	unsigned char get_height(node* p) {
		return p ? p->height : 0;
	}
private:
	void take_phantom(node *p) {
		if (p->right)
			take_phantom(p->right);
		else {
			p->parent->right = 0;
			delete p;
		}
	}

	void take_phantom() {
		if (root->right)
			take_phantom(root->right);
	}

	void push_phantom(node *p) {
		if (p->right)
			push_phantom(p->right);
		else {
			p->right = new node;
			p->right->parent = p;
		}
	}

	void push_phantom() {
		if (root->right)
			push_phantom(root->right);
		else {
			root->right = new node;
			root->right->parent = root;
		}
	}


	int bfactor(node* p) {
		return get_height(p->right) - get_height(p->left);
	}

	void fixheight(node* p) {
		unsigned char hl = get_height(p->left);
		unsigned char hr = get_height(p->right);
		p->height = (hl > hr ? hl : hr)+1;
	}

	node* rotateright(node* p) {
		node* q = p->left;
		p->left = q->right;
		if (p->left)
			p->left->parent = p;
		q->right = p;
		q->parent = p->parent;
		p->parent = q;
		fixheight(p);
		fixheight(q);
		return (q);
	}

	node* rotateleft(node* p) {
		node* q = p->right;
		p->right = q->left;
		if (p->right)
			p->right->parent = p;
		q->left = p;
		q->parent = p->parent;
		p->parent = q;
		fixheight(p);
		fixheight(q);
		return (q);
	}

	node* balance(node* p) {
		fixheight(p);
		if( bfactor(p)== 2)
		{
			if( bfactor(p->right) < 0 )
				p->right = rotateright(p->right);
			return rotateleft(p);
		}
		if( bfactor(p)== -2)
		{
			if( bfactor(p->left) > 0  )
				p->left = rotateleft(p->left);
			return rotateright(p);
		}
		return p;
	}

	node* findmin(node* p)
	{
		return p->left ? findmin(p->left) : p;
	}

	node* removemin(node* p)
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

	node* insert(node* prev, node* p, int k)
	{
		if( !p ) {
			node* tmp = new node(k);
			tmp->parent = prev;
			return tmp;
		}
		if( k < p->key )
			p->left = insert(p, p->left, k);
		else
			p->right = insert(p, p->right, k);
		return balance(p);
	}

	node* remove(node* p, int k)
	{
		if (!p)
			return 0;
		if(k < p->key)
			p->left = remove(p->left,k);
		else if(k > p->key)
			p->right = remove(p->right,k);	
		else
		{
			node* q = p->left;
			node* r = p->right;
			delete p;
			if (!r) return q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}
public:
	void insert(int k)
	{
		if( !root ) {
			root = new node(k);
			push_phantom();
			return ;
		}
		take_phantom();
		if( k< root->key )
			root->left = insert(root, root->left, k);
		else
			root->right = insert(root, root->right, k);
		root = balance(root);
		push_phantom();
	}

	void remove(int k)
	{
		if (!root)
			return ;
		take_phantom();
		if(k < root->key)
			root->left = remove(root->left,k);
		else if(k > root->key)
			root->right = remove(root->right,k);	
		else
		{
			node* q = root->left;
			node* r = root->right;
			delete root;
			if (!r) 
				root = q;
			node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			root = balance(min);
		}
		root = balance(root);
		push_phantom();
	}

};

int main() {
	avl_tree<int> tree;
	tree.insert(10);
	tree.insert(54);
	tree.insert(64);
	tree.insert(24);
	tree.insert(34);
	tree.insert(14);
	tree.remove(24);
	return 0;
}
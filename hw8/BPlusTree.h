/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree {
public:
    // Constructors & Destructor
    BPlusTree(int s) : root_(NULL), size_(s) {};
    BPlusTree(const BPlusTree<T>& old) : size_(old.size_) {
        root_ = this->copy_tree(old.root_, NULL);
    }
    BPlusTree<T>& operator=(const BPlusTree<T>& old) {
        if (&old != this) {
            this->destroy_tree(root_);
            root_ = this->copy_tree(old.root_, NULL);
            size_ = old.size_;
        }
        return *this;
    }
    ~BPlusTree() {
        this->destroy_tree(root_);
        root_ = NULL;
    }
    
    // Find & Insert
    BPlusTreeNode<T>* find(const T& key) const { return find(key, root_); }
    void insert(const T& key) { insert(key, root_, NULL); }
    
    // Print
    void print_sideways(std::ostream& outfile) const {
        print_sideways(outfile, root_, 0);
    }
    void print_BFS(std::ostream& outfile) const;
    void print_BFS_pretty(std::ostream& outfile) const;
private:
    // Representation
    BPlusTreeNode<T>* root_;
    int size_;
    
    // Private helper functions
    BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* old_root,
                                BPlusTreeNode<T>* the_parent);
    void destroy_tree(BPlusTreeNode<T>* p);
    BPlusTreeNode<T>* find(const T& key, BPlusTreeNode<T>* p) const;
    void create_new_parent(BPlusTreeNode<T>*& p);
    void process(const T& key,
                 BPlusTreeNode<T>*& p,
                 BPlusTreeNode<T>* the_parent,
                 unsigned int i);
    void insert(const T& key,
                BPlusTreeNode<T>*& p,
                BPlusTreeNode<T>* the_parent);
    void print_sideways(std::ostream& outfile, BPlusTreeNode<T>* p, int level) const;
};

template <class T>
BPlusTreeNode<T>* BPlusTree<T>::copy_tree(BPlusTreeNode<T>* old_root,
                                          BPlusTreeNode<T>* the_parent) {
    // Base case
    if (old_root == NULL) return NULL;
    
    // Dynamically allocate new node and
    BPlusTreeNode<T>* tmp = new BPlusTreeNode<T>();
    
    // Copy children nodes recursively
    for (unsigned int i = 0; i < old_root->children.size(); ++i)
        tmp->children.push_back(copy_tree(old_root->children[i], tmp));
    
    // Everything else
    tmp->keys = old_root->keys;
    tmp->parent = the_parent;
    
    // Finish for one tree
    return tmp;
}

template <class T>
void BPlusTree<T>::destroy_tree(BPlusTreeNode<T>* p) {
    // Base case
    if (p == NULL) return;
    
    // Delete recursively
    for (unsigned int i = 0; i < p->children.size(); ++i)
        destroy_tree(p->children[i]);
    
    delete p;
}

template <class T>
BPlusTreeNode<T>* BPlusTree<T>::find(const T& key, BPlusTreeNode<T>* p) const {
    // return NULL if tree is empty
    if (this->root_ == NULL) return NULL;
    
    // Find recursively
    unsigned int i = 0;
    for (; i < p->keys.size(); ++i) {
        if (key < p->keys[i]) { // key in left child node or does not exist
            if (p->is_leaf()) return p;
            else return find(key, p->children[i]);
        }
    }
    if (p->is_leaf()) return p; // key does not exist
    else return find(key, p->children[i]); // key might in rightmost child node
}

template <class T>
void BPlusTree<T>::create_new_parent(BPlusTreeNode<T>*& p) {
    // Calculate two nodes' size
    unsigned int first_half = p->keys.size() / 2;
    unsigned int second_half;
    if (p->is_leaf())
        second_half = p->keys.size() - first_half;
    else second_half = p->keys.size() - first_half - 1;
    
    // create new child node and split keys
    BPlusTreeNode<T>* new_child = new BPlusTreeNode<T>();
    while (new_child->keys.size() != second_half) {
        new_child->keys.insert(new_child->keys.begin(), p->keys.back());
        p->keys.pop_back();
    }
    
    // split children nodes for non-leaf node
    if (!p->is_leaf()) {
        while (new_child->children.size() != new_child->keys.size() + 1) {
            new_child->children.insert(new_child->children.begin(),
                                       p->children.back());
            new_child->children.front()->parent = new_child;
            p->children.pop_back();
        }
    }
    
    // create new parent node
    BPlusTreeNode<T>* new_parent = new BPlusTreeNode<T>();
    p->parent = new_parent;
    new_child->parent = new_parent;
    if (p->is_leaf()) new_parent->keys.push_back(new_child->keys.front());
    else {
        new_parent->keys.push_back(p->keys.back());
        p->keys.pop_back();
    }
    new_parent->children.push_back(p);
    new_parent->children.push_back(new_child);
    this->root_ = new_parent;
}

template <class T>
void BPlusTree<T>::process(const T& key,
                           BPlusTreeNode<T>*& p,
                           BPlusTreeNode<T>* the_parent,
                           unsigned int i) {
    if (!p->is_leaf()) {
        // Key is in left child node. Find recursively in deeper level
        insert(key, p->children[i], p);
        
        // If this child node exceeds degree limit
        if (p->children[i]->keys.size() >= this->size_) {
            // Calculate two nodes' size
            unsigned int first_half = p->children[i]->keys.size() / 2;
            unsigned int second_half;
            if (p->children[i]->is_leaf())
                second_half = p->children[i]->keys.size() - first_half;
            else second_half = p->children[i]->keys.size() - first_half - 1;
            
            // Split keys
            BPlusTreeNode<T>* new_child = new BPlusTreeNode<T>();
            new_child->parent = p;
            while (new_child->keys.size() != second_half) {
                new_child->keys.insert(new_child->keys.begin(),
                                       p->children[i]->keys.back());
                p->children[i]->keys.pop_back();
            }
            
            // split children nodes for non-leaf node
            if (!p->children[i]->is_leaf()) {
                while (new_child->children.size() != new_child->keys.size() + 1) {
                    new_child->children.insert(new_child->children.begin(),
                                               p->children[i]->children.back());
                    new_child->children.front()->parent = new_child;
                    p->children[i]->children.pop_back();
                }
            }
            
            // Extract key from children to put into p's key vector
            T parent_key(p->children[i]->keys.back());
            if (p->children[i]->is_leaf()) parent_key = new_child->keys.front();
            else p->children[i]->keys.pop_back();
            
            /* Insert children's key and new child node to p's key and
             children vector */
            typename std::vector<T>::iterator keys_itr = p->keys.begin();
            typename std::vector<BPlusTreeNode<T>*>::iterator children_itr;
            children_itr = p->children.begin();
            p->keys.insert(keys_itr + i, parent_key);
            p->children.insert(children_itr + i + 1, new_child);
        }
        
        // If p does not have parent and p exceeds degree limit
        if (the_parent == NULL && p->keys.size() >= this->size_)
            create_new_parent(p);
    } else {
        /* Arrive at leaf of tree. Inserting key to p's key vector in sorted
         order */
        typename std::vector<T>::iterator itr = p->keys.begin();
        p->keys.insert(itr + i, key);
        
        // If p does not have parent and p exceeds degree limit
        if (the_parent == NULL && p->keys.size() >= this->size_)
            create_new_parent(p);
    }
}

template <class T>
void BPlusTree<T>::insert(const T& key,
                          BPlusTreeNode<T>*& p,
                          BPlusTreeNode<T>* the_parent) {
    // If B+ tree is empty, dynamically allocate a new node.
    if (this->root_ == NULL) {
        this->root_ = new BPlusTreeNode<T>();
        this->root_->keys.push_back(key);
        return;
    }
    
    // Check each keys to find key in tree's leaves
    unsigned int i = 0;
    for (; i < p->keys.size(); ++i) {
        if (key < p->keys[i]) {
            process(key, p, the_parent, i);
            return;
        }
    }
    process(key, p, the_parent, i);
}

// PrintSideways() print B+ tree using in-order traversal
template <class T>
void BPlusTree<T>::print_sideways(std::ostream& outfile,
                                  BPlusTreeNode<T>* p,
                                  int level) const {
    // Check: If tree is empty
    if (this->root_ == NULL) {
        outfile << "Tree is empty." << std::endl;
        return;
    }
    
    // Compute splitted size
    unsigned int left = p->children.size() / 2;
    unsigned int right = p->children.size() - left;
    
    // traverse left child
    for (unsigned int i = 0; i < left; ++i)
        print_sideways(outfile, p->children[i], level + 1);
    
    // print key vector
    for (int i = 0; i < level; ++i) outfile << '\t';
    outfile << p->keys[0];
    for (unsigned int i = 1; i < p->keys.size(); ++i) outfile << ',' << p->keys[i];
    outfile << std::endl;
    
    // traverse right child
    for (unsigned int i = left; i < left + right; ++i)
        print_sideways(outfile, p->children[i], level + 1);
}

template <class T>
void BPlusTree<T>::print_BFS(std::ostream& outfile) const {
    // Check: If tree is empty
    if (this->root_ == NULL) {
        outfile << "Tree is empty." << std::endl;
        return;
    }
    
    // Initialize a FIFO queue
    std::vector<BPlusTreeNode<T>*> queue;
    queue.push_back(this->root_);
    std::vector<int> levels;
    levels.push_back(0);
    
    int last_level = 0;
    while (queue.size() != 0) {
        // get and remove the first element from queue
        BPlusTreeNode<T>* current(queue.front());
        queue.erase(queue.begin());
        int level(levels.front());
        levels.erase(levels.begin());
        
        //spacing
        if (level == last_level && level > 0) outfile << '\t';
        else if (level != last_level) outfile << std::endl;
        
        // print key vector
        outfile << current->keys[0];
        for (unsigned int i = 1; i < current->keys.size(); ++i)
            outfile << ',' << current->keys[i];
        
        // append current node's children to queue
        for (unsigned int i = 0; i < current->children.size(); ++i) {
            queue.push_back(current->children[i]);
            levels.push_back(level + 1);
        }
        
        last_level = level;
    }
    outfile << std::endl;
}

template <class T>
void BPlusTree<T>::print_BFS_pretty(std::ostream& outfile) const {
    // Check: If tree is empty
    if (this->root_ == NULL) {
        outfile << "Tree is empty." << std::endl;
        return;
    }
    
    // Find total level number of tree
    int total_level = 0;
    BPlusTreeNode<T>* ptr = this->root_;
    while (ptr->children.size() != 0) {
        ptr = ptr->children[0];
        total_level += 1;
    }
    
    // Initialize a FIFO queue
    std::vector<BPlusTreeNode<T>*> queue;
    queue.push_back(this->root_);
    std::vector<int> levels;
    levels.push_back(0);
    std::vector<BPlusTreeNode<T>*> parents;
    parents.push_back(NULL);
    
    int last_level = -1;
    BPlusTreeNode<T>* last_parent = NULL;
    while (queue.size() != 0) {
        // get and remove the first element from queue
        BPlusTreeNode<T>* current(queue.front());
        queue.erase(queue.begin());
        int level(levels.front());
        levels.erase(levels.begin());
        BPlusTreeNode<T>* parent(parents.front());
        parents.erase(parents.begin());
        
        // spacing
        if (level != last_level) {
            if (level > 0) outfile << std::endl;
            for (int i = 0; i < total_level - level; ++i) outfile << '\t';
        } else {
            outfile << '\t';
            if (parent != last_parent && level == total_level) outfile << '\t';
            else if (parent != last_parent) {
                for (int i = 0; i <= total_level - level; ++i) outfile << '\t';
                for (int i = 0; i <= size_; ++i) outfile << '\t';
            } else for (int i = 0; i < total_level - level; ++i) outfile << '\t';;
        }
        
        // print key vector
        outfile << current->keys[0];
        for (unsigned int i = 1; i < current->keys.size(); ++i)
            outfile << ',' << current->keys[i];
        
        // append current node's children to queue
        for (unsigned int i = 0; i < current->children.size(); ++i) {
            queue.push_back(current->children[i]);
            levels.push_back(level + 1);
            parents.push_back(current->children[i]->parent);
        }
        
        last_level = level;
        last_parent = current->parent;
    }
    outfile << std::endl;
}

#endif

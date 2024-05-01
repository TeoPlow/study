#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cctype>
#define fast_io std::ios::sync_with_stdio(false); std::cin.tie(0); std::cout.tie(0) // Ускорялка

using data = std::pair<std::string, unsigned long long>;

class AVL_tree;

class Node {
private:
    data node_data;
    Node* right = nullptr;
    Node* left = nullptr;
    int height = 0;
    Node* parent = nullptr;

    void rebalance(AVL_tree* tree, const std::string& key) {
        if (key.compare(this->node_data.first) < 0) {
            this->height++;
        } else {
            this->height--;
        }
        if (abs(this->height) == 1) {
            if (this->parent != nullptr) {
                this->parent->rebalance(tree, this->node_data.first);
            }
            return;
        } else if (this->height == -2) {
            if (this->right->height == -1) {
                this->right->height = 0;
                this->height = 0;
                this->rotate_left(tree);
            } else {
                switch (this->right->left->height) {
                    case -1:
                        this->height = 1;
                        this->right->height = 0;
                        break;
                    case 0:
                        this->height = 0;
                        this->right->height = 0;
                        break;
                    case 1:
                        this->height = 0;
                        this->right->height = -1;
                        break;
                }
                this->right->left->height = 0;
                this->right->rotate_right(tree);
                this->rotate_left(tree);
            }
            return;
        } else if (this->height == 2) {
            if (this->left->height == 1) {
                this->left->height = 0;
                this->height = 0;
                this->rotate_right(tree);
            } else {
                switch (this->left->right->height) {
                    case -1:
                        this->height = 0;
                        this->left->height = 1;
                        break;
                    case 0:
                        this->height = 0;
                        this->left->height = 0;
                        break;
                    case 1:
                        this->height = -1;
                        this->left->height = 0;
                        break;
                }
                this->left->right->height = 0;
                this->left->rotate_left(tree);
                this->rotate_right(tree);
            }
            return;
        }
    }

    void remove_and_rebalance(AVL_tree *tree, const std::string &key) {
        if (key.compare(this->node_data.first) < 0) {
            this->height--;
        } else {
            this->height++;
        }
        if (this->height == 0) {
            if (this->parent != nullptr) {
                this->parent->remove_and_rebalance(tree, this->node_data.first);
            }
            return;
        } else if (this->height == -2) {
            if (this->right->height == 0) {
                this->right->height = 1;
                this->height = -1;
                this->rotate_left(tree);
            } else if (this->right->height == -1) {
                this->right->height = 0;
                this->height = 0;
                this->rotate_left(tree);
                if (this->parent->parent != nullptr) {
                    this->parent->parent->remove_and_rebalance(tree, this->node_data.first);
                }
            } else {
                switch (this->right->left->height) {
                    case -1:
                        this->height = 1;
                        this->right->height = 0;
                        break;
                    case 0:
                        this->height = 0;
                        this->right->height = 0;
                        break;
                    case 1:
                        this->height = 0;
                        this->right->height = -1;
                        break;
                }
                this->right->left->height = 0;
                this->right->rotate_right(tree);
                this->rotate_left(tree);
                if (this->parent->parent != nullptr) {
                    this->parent->parent->remove_and_rebalance(tree, this->node_data.first);
                }
            }
            return;
        } else if (this->height == 2) {
            if (this->left->height == 0) {
                this->left->height = -1;
                this->height = 1;
                this->rotate_right(tree);
            } else if (this->left->height == 1) {
                this->left->height = 0;
                this->height = 0;
                this->rotate_right(tree);
                if (this->parent->parent != nullptr) {
                    this->parent->parent->remove_and_rebalance(tree, this->node_data.first);
                }
            } else {
                switch (this->left->right->height) {
                    case -1:
                        this->height = 0;
                        this->left->height = 1;
                        break;
                    case 0:
                        this->height = 0;
                        this->left->height = 0;
                        break;
                    case 1:
                        this->height = -1;
                        this->left->height = 0;
                        break;
                }
                this->left->right->height = 0;
                this->left->rotate_left(tree);
                this->rotate_right(tree);
                if (this->parent->parent != nullptr) {
                    this->parent->parent->remove_and_rebalance(tree, this->node_data.first);
                }
            }
            return;
        }
    }

    data remove_min(AVL_tree* tree) {
        if (this->left == nullptr) {
            data new_node_data = this->node_data;
            if (this->right != nullptr) {
                if (this->node_data.first.compare(this->parent->node_data.first) < 0) {
                    this->parent->left = this->right;
                    this->right->parent = this->parent;
                } else {
                    this->parent->right = this->right;
                    this->right->parent = this->parent;
                }
            } else {
                if (this->node_data.first.compare(this->parent->node_data.first) < 0) {
                    this->parent->left = nullptr;
                } else {
                    this->parent->right = nullptr;
                }
            }
            this->parent->remove_and_rebalance(tree, new_node_data.first);
            delete this;
            return new_node_data;
        }
        return this->left->remove_min(tree);
    }

    void rotate_left(AVL_tree *tree);

    void rotate_right(AVL_tree *tree);

public:
    Node(data node_data, Node* parent) : node_data(std::move(node_data)), parent(parent) {}

    void insert(AVL_tree *tree, const data &node_data, bool &flag);

    void remove(AVL_tree *tree, const std::string &key, bool &flag);

    unsigned long long search(const std::string& key, bool& flag) {
        if (this->node_data.first == key) {
            return this->node_data.second;
        } else if (this->node_data.first.compare(key) > 0) {
            if (this->left != nullptr) {
                return this->left->search(key, flag);
            } else {
                flag = false;
                return -1;
            }
        } else {
            if (this->right != nullptr) {
                return this->right->search(key, flag);
            } else {
                flag = false;
                return -1;
            }
        }
    }

    void save_to_file(std::ofstream &file) {
        size_t size = this->node_data.first.length();
        file.write(reinterpret_cast<char*>(&size), sizeof(size));
        file.write(this->node_data.first.c_str(), size);
        file.write(reinterpret_cast<char*>(&(this->node_data.second)), sizeof(this->node_data.second));
        if (this->left != nullptr) {
            this->left->save_to_file(file);
        }
        if (this->right != nullptr) {
            this->right->save_to_file(file);
        }
    }

    void clear_tree() {
        if (this->left != nullptr) {
            this->left->clear_tree();
        }
        if (this->right != nullptr) {
            this->right->clear_tree();
        }
        delete this;
    }

};

class AVL_tree {
private:
    Node *root = nullptr;

public:
    void set_root(Node *root) {
        this->root = root;
    }

    std::string insert(data &node_data) {
        bool flag = true;
        if (!root) {
            root = new Node(node_data, nullptr);
        } else {
            root->insert(this, node_data, flag);
        }
        return flag ? "OK" : "Exist";
    }

    std::string remove(const std::string& key) {
        bool flag = true;
        if (!root) {
            flag = false;
        } else {
            root->remove(this, key, flag);
        }
        return flag ? "OK" : "NoSuchWord";
    }

    std::string search(const std::string &key) {
        bool flag = true;
        unsigned long long node_data;
        if (!root) {
            flag = false;
        } else {
            node_data = root->search(key, flag);
        }
        return flag ? ("OK: " + std::to_string(node_data)) : "NoSuchWord";
    }

    void save_to_file(std::ofstream &file) {
        if (!root) {
            return;
        }
        root->save_to_file(file);
    }

    void load_from_file(std::ifstream &file) {
        this->clear_tree();
        size_t size;
        while (file.read(reinterpret_cast<char*>(&size), sizeof(size))) {
            std::string key;
            key.resize(size);
            file.read(key.data(), size);
            unsigned long long node_data;
            file.read(reinterpret_cast<char*>(&node_data), sizeof(node_data));
            data pair = make_pair(key, node_data);
            this->insert(pair);
        }
    }
    
    void clear_tree() {
        if (!root) {
            return;
        }
        root->clear_tree();
        root = nullptr;
    }
};

void Node::insert(AVL_tree* tree, const data& node_data, bool& flag) {
    if (node_data.first == this->node_data.first) {
        flag = false;
        return;
    }
    if (node_data.first.compare(this->node_data.first) < 0) {
        if (this->left == nullptr) {
            this->left = new Node(node_data, this);
            rebalance(tree, node_data.first);
        } else {
            this->left->insert(tree, node_data, flag);
        }
    } else {
        if (this->right == nullptr) {
            this->right = new Node(node_data, this);
            rebalance(tree, node_data.first);
        } else {
            this->right->insert(tree, node_data, flag);
        }
    }
}

void Node::rotate_left(AVL_tree* tree) {
    Node* root = this->right;
    this->right = root->left;
    if (root->left != nullptr) {
        root->left->parent = this;
    }
    root->parent = this->parent;
    if (this->parent == nullptr) {
        tree->set_root(root);
    } else if (this == this->parent->left) {
        this->parent->left = root;
    } else {
        this->parent->right = root;
    }
    root->left = this;
    this->parent = root;
}

void Node::rotate_right(AVL_tree* tree) {
    Node* root = this->left;
    this->left = root->right;
    if (root->right != nullptr) {
        root->right->parent = this;
    }
    root->parent = this->parent;
    if (this->parent == nullptr) {
        tree->set_root(root);
    } else if (this == this->parent->right) {
        this->parent->right = root;
    } else {
        this->parent->left = root;
    }
    root->right = this;
    this->parent = root;
}

void Node::remove(AVL_tree *tree, const std::string &key, bool &flag) {
    if (key.compare(this->node_data.first) < 0) {
        if (this->left != nullptr) {
            this->left->remove(tree, key, flag);
        } else {
            flag = false;
            return;
        }
    } else if (key.compare(this->node_data.first) > 0) {
        if (this->right != nullptr) {
            this->right->remove(tree, key, flag);
        } else {
            flag = false;
            return;
        }
    } else {
        if (this->left == nullptr and this->right == nullptr) {
            if (this->parent == nullptr) {
                tree->set_root(nullptr);
                delete this;
                return;
            }
            if (this->node_data.first.compare(this->parent->node_data.first) < 0) {
                this->parent->left = nullptr;
            } else {
                this->parent->right = nullptr;
            }
            this->parent->remove_and_rebalance(tree, key);
            delete this;
            return;
        } else if (this->left != nullptr and this->right == nullptr) {
            if (this->parent == nullptr) {
                tree->set_root(this->left);
                this->left->parent = nullptr;
                delete this;
                return;
            }
            if (this->node_data.first.compare(this->parent->node_data.first) < 0) {
                this->parent->left = this->left;
            } else {
                this->parent->right = this->left;
            }
            this->left->parent = this->parent;
            this->parent->remove_and_rebalance(tree, key);
            delete this;
            return;
        } else if (this->left == nullptr and this->right != nullptr) {
            if (this->parent == nullptr) {
                tree->set_root(this->right);
                this->right->parent = nullptr;
                delete this;
                return;
            }
            if (this->node_data.first.compare(this->parent->node_data.first) < 0) {
                this->parent->left = this->right;
            } else {
                this->parent->right = this->right;
            }
            this->right->parent = this->parent;
            this->parent->remove_and_rebalance(tree, key);
            delete this;
            return;
        } else {
            this->node_data = this->right->remove_min(tree);
            return;
        }
    }
}

void tolow(std::string& str) {
    for (char& c : str) {
        c = tolower(c);
    }
}

int main() {
    fast_io;
    
    AVL_tree tree;
    std::string input;
    std::string key;
    char sign;
    unsigned long long value;
    data node_data;
    
    while(std::getline(std::cin, input)) {
        std::istringstream str(input);

        if (input[0] == '+') {
            str >> sign;
            str >> key;
            str >> value;        
            tolow(key);
            node_data = make_pair(key, value);
            std::cout << tree.insert(node_data) << std::endl;
        } else if (input[0] == '-') {
            str >> sign;
            str >> key;
            tolow(key);
            std::cout << tree.remove(key) << std::endl;
        } else if (input[0] == '!') {
            std::string path;
            str >> sign;
            str >> key;
            str >> path;
            if (key == "Save") {
                std::ofstream file(path, std::ios_base::binary | std::ios_base::trunc);
                tree.save_to_file(file);
                file.close();
                std::cout << "OK" << std::endl;
            } else if (key == "Load") {
                std::ifstream file(path, std::ios_base::binary);
                tree.load_from_file(file);
                file.close();
                std::cout << "OK" << std::endl;
            }
        } else {
            str >> key;
            tolow(key);
            std::cout << tree.search(key) << std::endl;
        }
    }
    tree.clear_tree();
}
#pragma once
#include <cstdio>
#include <vector>
#include <queue>
#include "node.h"

template <typename T>
class naive_bst{
    private:
        /* helper method for searching for one value, if not found return nullptr */
        node<T>* tree_search_recursive(node<T>* root, T key){
            if(root == nil){
                return nullptr;     // not found
            }
            if(key < root->value){
                return tree_search_recursive(root->left_child, key);
            }
            else if(key == root->value){
                return root;
            }
            else{
                return tree_search_recursive(root->right_child, key);
            }
        }

        node<T>* tree_search_iterative(node<T>* root, T key){
            node<T>* ptr = root;
            while(ptr !=  nil){
                if(key == ptr->value){
                    return ptr;
                }
                else if(key < ptr->value){
                    ptr = ptr->left_child;
                }
                else{
                    ptr = ptr->right_child;
                }
            }
            return  nullptr;    // not found
        }

        /*helper method for searching for values in some ranges */
        void range_search_helper(node<T>* root, T lower_bound, T upper_bound, std::vector<node<T>*>& ret){
            if(root == this->nil)   return;
            if((root->value <= upper_bound) && (root->value >= lower_bound)){
                ret.push_back(root);
            }
            if(root->value >= lower_bound){
                range_search_helper(root->left_child, lower_bound, upper_bound, ret);
            }
            if(root->value <= upper_bound){
                range_search_helper(root->right_child, lower_bound, upper_bound, ret);
            }
        }

        void preorder_walk_helper(node<T>* root, std::vector<T>& result){
            if(root == nil) return;
            result.push_back(root->value);
            preorder_walk_helper(root->left_child, result);
            preorder_walk_helper(root->right_child, result);
        }

        void inorder_walk_helper(node<T>* root, std::vector<T>& result){
            if(root == nil) return;
            inorder_walk_helper(root->left_child, result);
            result.push_back(root->value);
            inorder_walk_helper(root->right_child, result);
        }

        void postorder_walk_helper(node<T>* root, std::vector<T>& result){
            if(root == nil) return;
            postorder_walk_helper(root->left_child, result);
            postorder_walk_helper(root->right_child, result);
            result.push_back(root->value);
        }
    protected:
        node<T>* nil;       // sentinel node
        node<T>* successor(node<T>* source){
            // if there is right subtree
            if(source->right_child !=  nil){
                node<T>* ptr = source->right_child;
                while(ptr->left_child !=  nil){
                    ptr=ptr->left_child;
                }
                return ptr;
            }
            // if there isn't right subtree, we go back to the ancestors
            node<T>* p_ptr = source->parent;
            node<T>* ptr = source;
            while(p_ptr != nil && p_ptr->right_child == ptr){
                ptr = p_ptr;
                p_ptr = p_ptr->parent;
            }
            return p_ptr;
        }   

        node<T>* predeccessor(node<T>* source){
            // if there is left subtree
            if(source->left_child != nil){
                node<T>* ptr = source->left_child;
                while(ptr->right_child != nil){
                    ptr=ptr->right_child;
                }
                return ptr;
            }
            // if there isn't left subtree, we go back to the ancestors
            node<T>* p_ptr = source->parent;
            node<T>* ptr = source;
            while(p_ptr != nil && p_ptr->left_child == ptr){
                ptr = p_ptr;
                p_ptr = p_ptr->parent;
            }
            return p_ptr;
        }

        void transplant(node<T>* u, node<T>* v){
            // if we need to transplant the root
            if(root == u){
                root = v;
                v->parent = nil;
                return;
            }
            // if the u is the left child
            if(u == u->parent->left_child){
                u->parent->left_child = v;
                v->parent = u->parent;      // update v-> parent, even if it's nil
            }
            // if the u is the right child
            else{
                u->parent->right_child = v;
                v->parent = u->parent;      // update v-> parent, even if it's nil
            }
        }

        void left_rotate(node<T>* x){
            if(x->right_child == this->nil){
                throw std::invalid_argument("left_rotate fails, x->right_child is nil");
            }
            node<T>* y = x->right_child;
            /* set the x's right subtree to be y's left subtree */
            x->right_child = y->left_child;
            if(y->left_child != this->nil){
                y->left_child->parent = x;
            }
            /* processing x's parent*/
            y->parent = x->parent;
            if(x == this->root){    
                this->root = y;
            }
            // x is the left child
            else if(x == x->parent->left_child){
                x->parent->left_child = y;
            }
            // x is the right child
            else{
                x->parent->right_child = y;
            }
            /* set x to be y's left son */
            y->left_child = x;
            x->parent = y;
            /*Update height(for AVL Tree)*/
            x->height = std::max(x->left_child->height, x->right_child->height) + 1;
            y->height = std::max(y->left_child->height, y->right_child->height) + 1;
        }
        
        void right_rotate(node<T>* x){
            if(x->left_child == this->nil){
                throw std::invalid_argument("right_rotate fails, x->left_child is nil");
            }
            node<T>* y = x->left_child;
            /* set the x's left subtree to be y's right subtree */
            x->left_child = y->right_child;
            if(y->right_child != this->nil){
                y->right_child->parent = x;
            }
            /* processing x's parent*/
            y->parent = x->parent;
            if(x == this->root){    
                this->root = y;
            }
            // x is the left child
            else if(x == x->parent->left_child){
                x->parent->left_child = y;
            }
            // x is the right child
            else{
                x->parent->right_child = y;
            }
            /* set x to be y's right son */
            y->right_child = x;
            x->parent = y;
            /*Update height(for AVL Tree)*/
            x->height = std::max(x->left_child->height, x->right_child->height) + 1;
            y->height = std::max(y->left_child->height, y->right_child->height) + 1;
        }

        virtual void pre_order_print_helper(node<T>* x, int level, int child_dir){
            bool is_nil = (x == this->nil);
            if(!is_nil)
                std::cout << "level=" << level <<" child=" << child_dir << " " << x->value << std::endl;
            else
                std::cout << "level=" << level <<" child=" << child_dir << " " << "null" << std::endl;
            if(is_nil)  return;
            pre_order_print_helper(x->left_child, level + 1, 0);
            pre_order_print_helper(x->right_child, level + 1, 1);
        }

    public:
        node<T>* root;

        /*Constructor*/
        naive_bst(){
            // initialize the sentinel
            nil = new node<T>(T(), nil, nil, nil);
            root = nil;
        }

        /*return the pointer to the new_created_note*/
        virtual node<T>* tree_insert(T new_val, std::string sat_data=""){
            node<T>* new_node = new node<T>(new_val, nil, nil, nil);
            new_node->set_satellite(sat_data);
            // if the tree is empty, corner case
            if(root == nil){
                root = new_node;
                return new_node;
            }
            node<T> *p_ptr;
            node<T> *ptr = root;
            while(ptr !=  nil){
                p_ptr = ptr;
                if(new_val > ptr->value){
                    ptr = ptr->right_child;
                }
                else{
                    ptr = ptr->left_child;
                }
            }

            if(new_val > p_ptr->value){
                p_ptr->right_child = new_node;
                new_node->parent = p_ptr;
            }
            else{
                p_ptr->left_child = new_node;
                new_node->parent = p_ptr;
            }
            return new_node;
        }

        /**delete a node from the tree*/
        virtual void tree_delete(node<T>* target){
            // corner case when delete the root, dealing with this->root
            if(target == root){
                if(target->left_child == this->nil){
                    this->root = target->right_child;
                }
                else if(target->right_child == this->nil){
                    this->root = target->left_child;
                }
                else{
                    this->root = successor(target);
                }
            }
            // if target has no left child
            if(target->left_child == this->nil){
                transplant(target, target->right_child);
                return;
            }
            // else if the target has no right child
            else if (target->right_child == this->nil){
                transplant(target, target->left_child);
                return;
            }
            // if the target has two child, find the successor, which must be on the right subtree
            node<T>* suc = successor(target);
            if(suc == target->right_child){
                transplant(target, suc);
                suc->left_child = target->left_child;
                suc->left_child->parent = suc;
                // not operate on the right child of target(it is suc itself and conflicts!!!)
            }
            else{
                transplant(suc, suc->right_child);
                transplant(target, suc);
                suc->left_child = target->left_child;
                suc->left_child->parent = suc;
                suc->right_child = target->right_child;
                suc->right_child->parent = suc;
            }
        }

        node<T>* tree_search(T key, bool is_recursion=false){
            /**is_recursion = true:     use the recursive method
             * is_recursion = false:    use the iterative method
            */
            if(root == nil){
                throw std::invalid_argument("empty tree, can't search");
            }
            if(is_recursion){
                return tree_search_recursive(root, key);
            }
            return tree_search_iterative(root, key);
            /*if not found, return  nullptr*/
        }

        std::vector<node<T>*> range_search(T lower_bound, T upper_bound){
            std::vector<node<T>*> ret;
            range_search_helper(this->root, lower_bound, upper_bound, ret);
            return ret;
        }

        std::vector<T> preorder_walk(){
            std::vector<T> ret;
            preorder_walk_helper(root, ret);
            return ret;
        }

        std::vector<T> inorder_walk(){
            std::vector<T> ret;
            inorder_walk_helper(root, ret);
            return ret;
        }

        std::vector<T> postorder_walk(){
            std::vector<T> ret;
            postorder_walk_helper(root, ret);
            return ret;
        }

        virtual void pre_order_print(){
            pre_order_print_helper(this->root, 0, 0);
        }

        virtual void breadth_first_walk_print(bool with_sat=false){
            std::cout << "--------------------------------------------------------------" << std::endl;
            if (this->root == this->nil) {
                std::cout << "(empty tree)" << std::endl;
                return;
            }
            std::queue<std::pair<node<T>*, int>> fringe;
            fringe.emplace(this->root, 1);
            int prev_height = 1;

            while(!fringe.empty()){
                auto [node_poped, height] = fringe.front();
                fringe.pop();
                if(height != prev_height){
                    std::cout << std::endl;
                    prev_height = height;
                }
                if(node_poped == this->root){
                    std::cout << node_poped->value;
                    if(with_sat) std::cout << ", " << node_poped->satellite; 
                    std::cout << "(root)\t";
                }
                else if(node_poped == node_poped->parent->left_child){
                    std::cout << node_poped->value;
                    if(with_sat) std::cout << ", " << node_poped->satellite;
                    std::cout << "(l, " << node_poped->parent->value << ")\t";
                }
                else{
                    std::cout << node_poped->value;
                    if(with_sat) std::cout << ", " << node_poped->satellite;
                    std::cout << "(r, " << node_poped->parent->value << ")\t";
                }
                if(node_poped->left_child != this->nil){
                    fringe.emplace(node_poped->left_child, height + 1);
                }
                if(node_poped->right_child != this->nil){
                    fringe.emplace(node_poped->right_child, height + 1);
                }
            }
            std::cout << std::endl;
            std::cout << "--------------------------------------------------------------" << std::endl;
        }

        node<T>* get_nil(){
            return this->nil;
        }
};
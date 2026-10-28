#include "naive_bst.h"

template <typename T>
class avl : public naive_bst<T>{
    private:
        /* update the height of p */
        void height_update(node<T>* p){
            p->height = std::max(p->left_child->height, p->right_child->height) + 1;
        }

        /* rotate to keep the balance at p */
        void rebalance(node<T>* p){
            if(p->left_child->height - p->right_child->height == 2){
                /* left-left : right rotation */
                if((p->left_child->left_child->height) >= (p->left_child->right_child->height)){
                    this->right_rotate(p);
                    height_update(p);
                    height_update(p->parent);
                }
                else{
                /* left-right : left-right rotation*/
                    node<T>* q = p->left_child;
                    this->left_rotate(q);
                    height_update(q);
                    height_update(q->parent);
                    this->right_rotate(p);
                    height_update(p);
                    height_update(p->parent);
                }
                /* if p is the root */
                if(this->root == p){
                    this->root = p->parent;
                }
            }
            else if(p->right_child->height - p->left_child->height == 2){
                /* right-right : left rotation */
                if((p->right_child->right_child->height) >= (p->right_child->left_child->height)){
                    this->left_rotate(p);
                    height_update(p);
                    height_update(p->parent);
                }
                else{
                /* right-left : right-left rotation */
                    node<T>* q = p->right_child;
                    this->right_rotate(q);
                    height_update(q);
                    height_update(q->parent);
                    this->left_rotate(p);
                    height_update(p);
                    height_update(p->parent);
                }
                /* if p is the root */
                if(this->root == p){
                    this->root = p->parent;
                }
            }
        }

        void insert_helper(node<T>* p_ptr, node<T>* ptr, node<T>* new_node){
            /*find the right position to insert*/
            if(ptr == this->nil){
                new_node->parent = p_ptr;
                if(new_node->value < p_ptr->value){
                    p_ptr->left_child = new_node;
                }
                else{
                    p_ptr->right_child = new_node;
                }
                return;
            }
            /*Insert into the left subtree*/
            if(new_node->value < ptr->value){
                insert_helper(ptr, ptr->left_child, new_node);
            }
            /*Insert into the right subtree*/
            else{
                insert_helper(ptr, ptr->right_child, new_node);
            }
            /*rebalance p*/
            rebalance(ptr);
            /*update the node height*/
            height_update(ptr);
            if (p_ptr != this->nil) {
                height_update(p_ptr);
            }
        }

        void delete_helper(node<T>* p_ptr, node<T>* ptr, node<T>* delete_node){
            /*find the right position to insert*/
            if(ptr == delete_node){
                /* no child or one child*/
                if(ptr->left_child == this->nil){
                    this->transplant(ptr, ptr->right_child);
                    if(p_ptr != this->nil)
                        height_update(p_ptr);
                }
                else if(ptr->right_child == this->nil){
                    this->transplant(ptr, ptr->left_child);
                    if(p_ptr != this->nil)
                        height_update(p_ptr);
                }
                /* two child */
                else{
                    // if the target has two child, find the successor, which must be on the right subtree
                    node<T>* suc = this->successor(delete_node);
                    if(suc == delete_node->right_child){
                        this->transplant(delete_node, suc);
                        suc->left_child = delete_node->left_child;
                        suc->left_child->parent = suc;
                        // not operate on the right child of target(it is suc itself and conflicts!!!)
                    }
                    else{
                        this->transplant(suc, suc->right_child);
                        rebalance(suc->parent);
                        height_update(suc->parent);
                        this->transplant(delete_node, suc);
                        suc->left_child = delete_node->left_child;
                        suc->left_child->parent = suc;
                        suc->right_child = delete_node->right_child;
                        suc->right_child->parent = suc;
                    }
                    height_update(suc);
                }
                return;
            }
            /*delete into the left subtree*/
            if(delete_node->value < ptr->value){
                delete_helper(ptr, ptr->left_child, delete_node);
            }
            /*delete into the right subtree*/
            else if(delete_node->value > ptr->value){
                delete_helper(ptr, ptr->right_child, delete_node);
            }
            /*rebalance p*/
            rebalance(ptr);
            /*update the node height*/
            height_update(ptr);
            if (p_ptr != this->nil) {
                height_update(p_ptr);
            }
        }

    protected:
    public:
        avl(){
            /* the height of the nil is -1 */
            this->nil = new node<T>(T(), this->nil, this->nil, this->nil, false, -1);
            this->root = this->nil;
        }

        /**TO-DO: override the insert method for avl tree*/
        node<T>* tree_insert(T val, std::string sat_data="") override{
            node<T>* new_node = new node<T>(val, this->nil, this->nil, this->nil, false, 0);
            new_node->set_satellite(sat_data);
            /* if it's an empty tree*/
            if(this->root == this->nil){
                this->root = new_node;
                return new_node;
            }
            insert_helper(this->nil, this->root, new_node);
            return new_node;
        }

        void tree_delete(node<T>* target) override{
            delete_helper(this->nil, this->root, target);
        }
};
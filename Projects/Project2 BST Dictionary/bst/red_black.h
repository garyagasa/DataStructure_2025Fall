#include "naive_bst.h"
#include <stdexcept>

template <typename T>
class red_black_tree : public naive_bst<T>{
    protected:
        //TO-DO: the insert fix_up method of red black tree
        void insert_fixup(node<T>* z){
            /** we assume that:
             *  z : z is where we need to deal with insert fix up
             *  y : y is the uncle unit of z
            */
            node<T>* y;
            while(z->parent->is_red == true){                   /*if the father is black, then we can stop*/
                // if z-> parent is the left child
                if(z->parent == z->parent->parent->left_child){
                    y = z->parent->parent->right_child;
                    /*Case 1 : the uncle unit is red, change the color*/
                    if(y->is_red == true){
                        z->parent->is_red = false;                      // case 1
                        y->is_red = false;                              // case 1
                        z->parent->parent->is_red = true;               // case 1
                        /*update z to its grandfather and continue*/    // case 1
                        z = z->parent->parent;                          // case 1
                    }
                    else{
                    /*Case 2: the uncle is black, and z and its father are the sons of different sides*/
                    // rotate to transform to case 3
                        if(z == z->parent->right_child){
                            z = z->parent;                              // case 2
                            this->left_rotate(z);                       // case 2
                        }
                    /*Case 3: the uncle is black, and z and its father are the sons of the same side*/
                        /*set parent to black, grandfather to red*/
                        z->parent->is_red = false;                      // case 3
                        z->parent->parent->is_red = true;               // case 3
                        this->right_rotate(z->parent->parent);          // case 3
                    }
                }
                // if z -> parent is the right child
                else{
                    y = z->parent->parent->left_child;
                    /*Case 1 : the uncle unit is red, change the color*/
                    if(y->is_red == true){
                        z->parent->is_red = false;                      // case 1
                        y->is_red = false;                              // case 1
                        z->parent->parent->is_red = true;               // case 1
                        /*update z to its grandfather and continue*/    // case 1
                        z = z->parent->parent;                          // case 1
                    }
                    else{
                    /*Case 2: the uncle is black, and z and its father are the sons of different sides*/
                    // rotate to transform to case 3
                        if(z == z->parent->left_child){
                            z = z->parent;                              // case 2
                            this->right_rotate(z);                      // case 2
                        }
                    /*Case 3: the uncle is black, and z and its father are the sons of the same side*/
                        /*set parent to black, grandfather to red*/
                        z->parent->is_red = false;                      // case 3
                        z->parent->parent->is_red = true;               // case 3
                        this->left_rotate(z->parent->parent);           // case 3
                    }
                }
            }
            this->root->is_red = false;
        }

        // TODO: delete_fixup
        void delete_fixup(node<T>* x){
            /* w is the brother node of x */
            node<T>* w = this->nil;
            while(x != this->root &&  x->is_red == false){
                /* if x is the left child */
                if(x == x->parent->left_child){
                    w = x->parent->right_child;
                    /*Case 1: w is red*/
                    // rotate at x->parent, transform to other cases
                    if(w->is_red == true){
                        w->is_red = false;                              // case 1
                        x->parent->is_red = true;                       // case 1
                        this->left_rotate(x->parent);                   // case 1
                        w = x->parent->right_child;                     // case 1
                    }
                    /*Case 2: w is black and nephew on the both sides are black*/
                    // change the brother w's color, move x to its parent
                    if(w->left_child->is_red == false && w->right_child->is_red == false){
                        w->is_red = true;                               // case 2
                        x = x->parent;                                  // case 2
                    }
                    else{
                    /*Case 3: w is black and nephew on the other side is black, nephew on the same side is red*/
                    // change colors of w and nephew on the same side, then rotate to case 4
                        if(w->right_child->is_red == false){
                            w->left_child->is_red = false;              // case 3
                            w->is_red = true;                           // case 3
                            this->right_rotate(w);                      // case 3
                            w = x->parent->right_child;                 // case 3 
                        }
                    /*Case 4: w is black and nephew on the other side is red*/
                        w->is_red = x->parent->is_red;                          // case 4
                        x->parent->is_red = false;                      // case 4
                        w->right_child->is_red = false;                 // case 4
                        this->left_rotate(x->parent);                   // case 4
                        x = this->root;                                 // case 4
                    }
                }
                /* if x is the right child */
                else{
                    w = x->parent->left_child;
                    /*Case 1: w is red*/
                    // rotate at x->parent, transform to other cases
                    if(w->is_red == true){
                        w->is_red = false;                              // case 1
                        x->parent->is_red = true;                       // case 1
                        this->right_rotate(x->parent);                  // case 1
                        w = x->parent->left_child;                      // case 1
                    }
                    /*Case 2: w is black and nephew on the both sides are black*/
                    // change the brother w's color, move x to its parent
                    if(w->left_child->is_red == false && w->right_child->is_red == false){
                        w->is_red = true;                               // case 2
                        x = x->parent;                                  // case 2
                    }
                    else{
                    /*Case 3: w is black and nephew on the other side is black, nephew on the same side is red*/
                    // change colors of w and nephew on the same side, then rotate to case 4
                        if(w->left_child->is_red == false){
                            w->right_child->is_red = false;             // case 3
                            w->is_red = true;                           // case 3
                            this->left_rotate(w);                       // case 3
                            w = x->parent->left_child;                  // case 3 
                        }
                    /*Case 4: w is black and nephew on the other side is red*/
                        w->is_red = x->parent->is_red;                  // case 4
                        x->parent->is_red = false;                      // case 4
                        w->right_child->is_red = false;                 // case 4
                        this->right_rotate(x->parent);                  // case 4
                        x = this->root;                                 // case 4
                    }
                }
            }
            x->is_red = false;
        }

        void pre_order_print_helper(node<T>* x, int level, int child_dir) override{
            bool is_nil = (x == this->nil);
            if(!is_nil){
                std::string color = (x->is_red) ? "(RED)" : "(BLACK)"; 
                std::cout << "level=" << level <<" child=" << child_dir << " " << x->value << color << std::endl;
            }
            else
                std::cout << "level=" << level <<" child=" << child_dir << " " << "null" << std::endl;
            if(is_nil)  return;
            pre_order_print_helper(x->left_child, level + 1, 0);
            pre_order_print_helper(x->right_child, level + 1, 1);
        }
    public:
        red_black_tree(){
            this->nil = new node<T>(T(), this->nil, this->nil, this->nil);
            this->root = this->nil;
        }

        node<T>* tree_insert(T val, std::string sat_data="") override{
            node<T>* z = naive_bst<T>::tree_insert(val, sat_data);
            z->is_red = true;
            insert_fixup(z);
            return z;
        }

        void tree_delete(node<T>* z) override{
            /* y is the last position where we need to delete, z or the successor of z */
            /* x is the node which inherits after deleting y */
            if(z == this->nil) return;      // empty value check

            node<T>* y = z;
            bool y_is_red = y->is_red;
            node<T>* x = this->nil;
    
            /* delete with only one or no child, y = z*/
            if(z->left_child == this->nil){
                x = z->right_child;
                this->transplant(z, z->right_child);
            }
            else if(z->right_child == this->nil){
                x = z->left_child;
                this->transplant(z, z->left_child);
            }
            /* delete with two child, y = successor(z)*/
            else{
                y = this->successor(z);
                y_is_red = y->is_red;
                
                /* delete at y */
                x = y->right_child;
                if(y->parent == z){
                    x->parent = y;
                }
                else{
                    this->transplant(y, x);
                    y->right_child = z->right_child;
                    y->right_child->parent = y;
                }
                this->transplant(z, y);
                y->left_child = z->left_child;
                y->left_child->parent = y;
                y->is_red = z->is_red;
            }
            /* if y is black, we need to fix up */
            if(y_is_red == false){
                delete_fixup(x);
            }
        }

        void breadth_first_walk_print(bool with_sat=false) override{
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
                std::string color = (node_poped->is_red) ? "RED" : "BLACK";
                if(height != prev_height){
                    std::cout << std::endl;
                    prev_height = height;
                }
                if(node_poped == this->root){
                    std::cout << node_poped->value; 
                    if(with_sat) std::cout << ", " << node_poped->satellite; 
                    std::cout << "(root, " << color <<")\t";
                }
                else if(node_poped == node_poped->parent->left_child){
                    std::cout << node_poped->value; 
                    if(with_sat) std::cout << ", " << node_poped->satellite; 
                    std::cout << "(l, " << node_poped->parent->value << ", " << color << ")\t";
                }
                else{
                    std::cout << node_poped->value;
                    if(with_sat) std::cout << ", " << node_poped->satellite; 
                    std::cout << "(r, " << node_poped->parent->value << ", " << color << ")\t";
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

        void pre_order_print() override{
            pre_order_print_helper(this->root, 0, 0);
        }
};
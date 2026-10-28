### Lab 3 Naive BST
Shiqiang Wu 24300810019@m.fudan.edu.cn
#### I. Lab structure
本实验包含以下文件结构：

```
Lab3 Naive BST/
├── README.md      
├── bst_node.h                  # BST node类的定义，Tree类的定义
├── bst_operation.h             # BST有关的操作(题目要求的实现均在此)
├── insert_walk_test.cpp        # 测试insert和前/中/后序遍历实现的正确性
├── search_successor_test.cpp   # 测试后继和前驱查找的正确性
└── search_delete_test.cpp      # 测试查找和删除的正确性
```

主要类说明：
- **node**: 二叉搜索树节点类
  ```cpp
    template <typename T>
    class node{
        public:
        T value;
        node* parent;
        node* left_child;
        node* right_child;

        node(T val, node* p=nullptr, node* lc=nullptr, node* rc=nullptr){
            value = val;
            parent = p;
            left_child = lc;
            right_child = rc;
        }
    };
  ```
- **Tree**: 二叉搜索树类
  ```cpp
    template <typename T>
    class tree{
        public:
        node<T>* root;
        tree(){
            root = nullptr;
        }
    };
  ```

#### II. BST methods in `bst_operation.h`
- Insert
    ```cpp
    template <typename T>
    void tree_insert(tree<T>& t, T new_val)
    ```
- **Search(Question1)**
    ```cpp
    template <typename T>
    node<T>* tree_search(tree<T> t, T key, bool is_recursion=false)
    ```
- **后继/前驱(Question2)**
    ```cpp
    template <typename T>
    node<T>* successor(node<T>* source)
    ```
    ```cpp
    template <typename T>
    node<T>* predeccessor(node<T>* source);
    ```
- **前/中/后序遍历(Question3)**
    ```cpp
    template <typename T>
    vector<T> preorder_walk(tree<T>& t);
    ```
    ```cpp
    template <typename T>
    vector<T> inorder_walk(tree<T>& t);
    ```
    ```cpp
    template <typename T>
    vector<T> postorder_walk(tree<T>& t);
    ```
- delete
    ```cpp
    template <typename T>
    void tree_delete(tree<T>& t, node<T>* target);
    ```
#### III.Test

```bash
.\search_successor_test
```

```bash
.\insert_walk_test
```

```bash
.\search_delete_test
```

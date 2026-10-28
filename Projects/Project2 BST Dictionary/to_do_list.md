#### To-Do List
- [x] **BST Wheels**
    - [x] `naive_bst`
        - [x] Insert
        - [x] Delete
        - [x] Search
            - [x] single value search
            - [x] range search
        - [x] PreOrder_print
    - [x] `red_black`(inherit from `naive_bst`)
        - [x] Insert(override)
        - [x] Delete(override)
        - [x] PreOrder_print(override)
    - [x] `AVL`(inherit from `naive_bst`)
        - [x] Insert(override)
        - [x] Delete(override)
    > Search methods used in three kind of BSTs are the same.
- [x] **Build the Dictionary**
    - [x] Red-Black Dictionary
        - [x] Initialize the dictionary
        - [x] Validate the `search` methods
        - [x] Validate the `insert` and `delete` methods
    - [x] AVL Dictionary
        - [x] Initialize the dictionary
        - [x] Validate the `search` methods
        - [x] Validate the `insert` and `delete` methods
- [x] **Time Benchmarks and Analysis**
    > 5 Competitions, each compare the running time of `Red-Black Dictionary` and `AVL Dictionary`:
    - [x] **Init Competition**:
        Insert 100 words from `init.txt` each times to initialize the dictionary, measure the time to take for every 100 words.
    - [x] **Delete and Insert Competition**:
        Repeating for several times:
        + delete words from `delete.txt`
        + insert words from `insert.txt`
  
        Each time we record the time to perform the `delete` and `insert` operations and compare.
    - [x] **Single Value Search Competition**:
    - [x] **Range Search Competition**:
- [x] **Bonus: Dictionary GUI**
    - [x] Build a larger dictionary contains basic english-chinese words used `red-black` Tree.
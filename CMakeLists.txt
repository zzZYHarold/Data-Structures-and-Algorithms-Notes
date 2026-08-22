cmake_minimum_required(VERSION 4.0)
project(data-structures-and-algorithms C)

set(CMAKE_C_STANDARD 17)

add_executable(ShujujiegouYuSuanfa main.c)
add_executable(p3_binary-search binary_search.c)

# 并查集--王道考研
add_executable(p5.5.2_disjoint-set-basic disjoint-set-union/ds_basic.c)
add_executable(p5.5.2_disjoint-set-advanced disjoint-set-union/ds_advanced.c)
add_executable(p5.5.2_union-by-rank disjoint-set-union/union_by_rank.c)

# 线性表
add_executable(p5-7_sequence-list linear-list/sequence_list.c)
add_executable(p8-10_linked-list linear-list/linked_list.c)
add_executable(p11_double-linked-list linear-list/double_linked_list.c)
add_executable(p12_circular-linked-list linear-list/circular_linked_list.c)
add_executable(p13-14_stack-by-array linear-list/stack_by_array.c)
add_executable(p15_stack-by-linked-list linear-list/stack_by_linked-list.c)
add_executable(p16-17_queue-by-array linear-list/queue_by_array.c)
add_executable(p18_queue-by-linked-list linear-list/queue_by_linked-list.c)

# 树
add_executable(p30_binary-tree-build tree/binary_tree_build.c)
add_executable(p31-35_binary-tree-traversal tree/binary_tree_traversal.c)
add_executable(p38-39_threaded-binary-tree tree/threaded_binary_tree.c)
add_executable(p40_binary-search-tree tree/binary_search_tree.c)
add_executable(p42_balanced-binary-tree tree/balanced_binary_tree.c)
add_executable(p47_priority-queue linear-list/priority_queue.c)
add_executable(p47_Huffman-tree tree/Huffman_tree.c)
add_executable(p48-49_Heap tree/heap.c)

# 哈希表/散列表
add_executable(p56_hash-table hash-table/hash_table.c)
add_executable(p57_linear-probing hash-table/linear_probing.c)
add_executable(p58_chain-address hash-table/chain_address.c)

# 图
add_executable(p64-65_adjacency-matrix graph/adjacency_matrix.c)
add_executable(p66_adjacency-list graph/adjacency_list.c)
add_executable(p68-69_DFS graph/dfs.c)
add_executable(p70_BFS graph/bfs.c)
add_executable(p73_Prim graph/prim.c)
add_executable(p73_Kruskal graph/kruskal.c)
add_executable(p74_Dijkstra graph/dijkstra.c)
add_executable(p75_Floyd graph/floyd.c)
add_executable(p76_Kahn graph/kahn_AOV_Network_Topological_Sorting.c)
add_executable(p77_Kahn-Ve-Vl graph/kahn_Ve_Vl.c)

# 排序
add_executable(p78_bubble-sort sort/bubble_sort.c)
add_executable(p79_insert-sort sort/insert_sort.c)
add_executable(p80_select-sort sort/select_sort.c)
add_executable(p81_quick-sort sort/quick_sort.c)
add_executable(p82_quick-sort-double-axis sort/quick_sort_dual_pivot.c)
add_executable(p83_shell-sort sort/shell_sort.c)
add_executable(p84_heap-sort sort/heap_sort.c)

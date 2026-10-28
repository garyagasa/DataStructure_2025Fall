#include "../graph/graph_matrix.h"
#include "../graph/ret_format.h"
#include "../graph/utils.h"
#include <vector>
#include <algorithm>
using namespace std;

FloydWarshallResult floyd_warshall_all_pairs(Graph_Matrix& graph);

FloydWarshallResult mat_mul_all_pairs(Graph_Matrix& graph);

PathResult floyd_warshall_get_path(const FloydWarshallResult& floyd_result, 
                                  const std::string& start, const std::string& end);

PathResult matmul_get_path(const FloydWarshallResult& matmul_result,
                        const std::string& start, const std::string& end);
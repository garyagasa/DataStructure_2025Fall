#pragma once
#include "../graph/graph.h"
#include "../graph/ret_format.h"
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

MSTResult prim_mst(Graph& graph, std::string start_vertex);
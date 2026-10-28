#pragma once
#include "../graph/graph.h"
#include "../graph/ret_format.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <limits>
#include <algorithm>

PathResult dijkstra_shortest_path(Graph& graph, const std::string& start, const std::string& end);

OneToAllResult dijkstra_one_to_all(Graph& graph, const std::string& start);
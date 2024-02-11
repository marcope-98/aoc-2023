#include "aoc/solutions/day25.hpp"

#include <algorithm>
#include <iostream>
#include <unordered_map>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  struct Iteration
  {
    std::string supernode;
    std::size_t min_cut;
  };

  struct Graph
  {
    std::unordered_map<std::string, std::size_t> nodes;
    std::vector<std::vector<std::size_t>>        weights;
    std::string                                  supernode;
    std::string                                  last;
    explicit Graph(const aoc::vstring &input)
    {
      this->fill_nodes(input);

      std::size_t n_nodes = this->nodes.size();
      this->weights.resize(n_nodes);
      for (std::size_t i = 0; i < n_nodes; ++i)
        this->weights[i].resize(n_nodes, 0);

      this->fill_weights(input);
      for (const auto &node : this->nodes)
        if (node.second == 0)
          this->supernode = node.first;
    }

    void fill_weights(const aoc::vstring &input)
    {
      for (const auto &line : input)
      {
        aoc::vstring temp = aoc::parse::split_by_delimiters(line, " :");
        std::size_t  src  = this->nodes[temp.front()];
        temp.erase(temp.begin());
        for (const auto &node : temp)
        {
          std::size_t dst         = this->nodes[node];
          this->weights[src][dst] = 1;
          this->weights[dst][src] = 1;
        }
      }
    }

    void fill_nodes(const aoc::vstring &input)
    {
      for (const auto &line : input)
      {
        aoc::vstring temp = aoc::parse::split_by_delimiters(line, " :");
        for (const auto &node : temp)
          if (this->nodes.find(node) == this->nodes.end())
            this->nodes[node] = this->nodes.size();
      }
    }

    void update_weights(const std::string &node1, const std::string &node2)
    {
      std::size_t src = this->nodes[node1];
      std::size_t dst = this->nodes[node2];
      for (std::size_t i = 0; i < this->weights.size(); ++i)
      {
        this->weights[i][src] += this->weights[i][dst];
        this->weights[src][i] += this->weights[dst][i];
      }
      this->weights[src][src] = 0;
      this->weights[dst][dst] = 0;

      for (auto &row : this->weights)
        row.erase(row.begin() + dst);
      this->weights.erase(this->weights.begin() + dst);
    }

    void merge(std::string node1, std::string node2)
    {
      if (this->nodes[node1] > this->nodes[node2])
      {
        std::string temp = node2;
        node2            = node1;
        node1            = temp;
      }
      // sum the two vectors into the first one;
      this->update_weights(node1, node2);

      // update key of this->nodes
      std::size_t src = this->nodes[node1];
      std::size_t dst = this->nodes[node2];

      this->nodes.erase(this->nodes.find(node1));
      this->nodes.erase(this->nodes.find(node2));

      for (auto &node : this->nodes)
        if (node.second > dst)
          --node.second;

      this->nodes[node1 + "," + node2] = src;
    }

    Iteration step()
    {
      std::size_t size = this->nodes.size();
      for (std::size_t j = 0; j < (size - 2); ++j)
      {
        // find maximum
        std::size_t max = 0, res = 0;
        for (std::size_t i = 0; i < this->weights.front().size(); ++i)
          if (this->weights.front()[i] > max)
          {
            max = this->weights.front()[i];
            res = i;
          }

        // retrieve edge name
        for (const auto &elem : this->nodes)
          if (elem.second == res)
            this->last = elem.first;
        this->merge(this->supernode, this->last);
        this->supernode += "," + this->last;
      }
      return Iteration{this->supernode, this->weights[0][1]};
    }

    void print()
    {
      for (const auto &node : this->nodes)
        std::cerr << node.first << " " << node.second << "\n";

      for (std::size_t i = 0; i < this->nodes.size(); ++i)
      {
        for (std::size_t j = 0; j < this->nodes.size(); ++j)
          std::cerr << this->weights[i][j] << " ";
        std::cerr << "\n";
      }
    }
  };
} // namespace

std::size_t aoc::day25::part1(const std::string &filename)
{
  aoc::vstring           input = aoc::parse::cvt_file_to_vstring(filename);
  Graph                  graph(input);
  std::size_t            n_nodes = graph.nodes.size();
  std::vector<Iteration> iterations;
  while (graph.nodes.size() > 2)
  {
    Graph temp_graph = graph;
    iterations.emplace_back(temp_graph.step());
    std::string node1 = temp_graph.last;
    std::string node2;
    for (const auto &node : temp_graph.nodes)
      if (node.second == 1)
        node2 = node.first;
    graph.merge(node1, node2);
  }
  auto it = std::min_element(iterations.begin(), iterations.end(), [](const Iteration &a, const Iteration &b)
                             { return a.min_cut < b.min_cut; });

  std::size_t res = aoc::parse::split_by_delimiters(it->supernode, ",").size();

  return res * (n_nodes - res);
}

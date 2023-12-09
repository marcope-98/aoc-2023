#include "aoc/solutions/day08.hpp"

#include <algorithm>
#include <string>
#include <unordered_map>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

static std::size_t gcd(const std::size_t &a, const std::size_t &b)
{
  if (b == 0) return a;
  return gcd(b, a % b);
}

static std::size_t lcm(const std::size_t &a, const std::size_t &b) { return a / (gcd(a, b)) * b; }

struct Dirs
{
  std::string left;
  std::string right;
};

struct Task
{
  std::size_t offset{0};
  std::size_t period{0};

  void simulate_till(const std::size_t &time)
  {
    while (this->offset < time)
      this->offset += this->period;
  }
};

template<typename Key, typename Value>
using HashMap = std::unordered_map<Key, Value>;

static HashMap<std::string, Dirs> construct_graph(const aoc::vstring &input)
{
  HashMap<std::string, Dirs> graph;
  for (const auto &line : input)
  {
    aoc::vstring temp = aoc::parse::split_by_delimiters(line, "=(,)");
    graph[temp[0]]    = {temp[1], temp[2]};
  }
  return graph;
}

static aoc::vstring get_starting_nodes(const HashMap<std::string, Dirs> &graph)
{
  aoc::vstring out;
  for (const auto &node : graph)
    if (node.first.back() == 'A')
      out.emplace_back(node.first);
  return out;
}

struct Node
{
  HashMap<std::string, std::size_t> hashmap;
  std::string                       current;
  bool                              loop_condition = false;
  aoc::vstring                      visited;

  Node() = default;
  explicit Node(const std::string &node) : current{node} {}

  bool ends_with_Z() const { return this->current.back() == 'Z'; }
  bool is_ZZZ() const { return this->current == "ZZZ"; }
  bool is_loop() const { return this->loop_condition; }

  Task get_loop_metadata() const
  {
    std::size_t offset = 0;
    std::size_t index  = this->hashmap.find(this->current)->second;
    for (std::size_t i = index; i < this->visited.size(); ++i)
      if (this->visited[i].back() == 'Z')
        offset = i;
    return {offset, this->visited.size() - index};
  }

  void step(const std::string &sequence, const HashMap<std::string, Dirs> &graph)
  {
    if (this->hashmap.find(this->current) != this->hashmap.end())
    {
      this->loop_condition = true;
      this->current        = this->visited[hashmap[this->current]];
    }
    else
    {
      std::string temp = this->current;
      for (const auto &direction : sequence)
      {
        Dirs dir = graph.find(temp)->second;
        temp     = direction == 'L' ? dir.left : dir.right;
      }

      hashmap[this->current] = this->visited.size();
      this->visited.emplace_back(this->current);
      this->current = temp;
    }
  }
};

static bool all_loops(const std::vector<Node> &nodes)
{
  for (const auto &node : nodes)
    if (!node.is_loop())
      return false;
  return true;
}

std::size_t aoc::day08::part1(const std::string &filename)
{
  aoc::vstring input    = aoc::parse::cvt_file_to_vstring(filename);
  std::string  sequence = input[0];
  input.erase(input.begin(), input.begin() + 2);

  HashMap<std::string, Dirs> graph = construct_graph(input);
  Node                       node("AAA");
  std::size_t                result = 0;

  while (!node.is_ZZZ())
  {
    node.step(sequence, graph);
    result += sequence.size();
  }

  return result;
}

std::size_t aoc::day08::part2(const std::string &filename)
{
  aoc::vstring input    = aoc::parse::cvt_file_to_vstring(filename);
  std::string  sequence = input[0];
  input.erase(input.begin(), input.begin() + 2);

  HashMap<std::string, Dirs> graph = construct_graph(input);
  aoc::vstring               temp  = get_starting_nodes(graph);
  std::vector<Node>          nodes;
  nodes.reserve(temp.size());
  for (const auto &str : temp)
    nodes.emplace_back(Node(str));

  while (!all_loops(nodes))
    for (auto &node : nodes)
      node.step(sequence, graph);

  std::vector<Task> tasks;
  for (const auto &node : nodes)
    tasks.emplace_back(node.get_loop_metadata());

  std::size_t start = std::max_element(tasks.begin(), tasks.end(),
                                       [](const Task &a, const Task &b)
                                       { return a.offset < b.offset; })
                          ->offset;

  Task t = {0, 1};
  for (auto &task : tasks)
  {
    task.simulate_till(start);
    t.period = lcm(t.period, gcd(task.period, task.offset));
  }

  return t.period * sequence.size();
}

#include "aoc/solutions/day20.hpp"

#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

#include "aoc/utils/aliases.hpp"
#include "aoc/utils/parse.hpp"

namespace
{
  std::size_t gcd(const std::size_t &lhs, const std::size_t &rhs)
  {
    std::size_t a = lhs, b = rhs;
    while (a != b)
    {
      if (a > b)
        a -= b;
      else
        b -= a;
    }
    return a;
  }
  std::size_t lcm(const std::size_t &lhs, const std::size_t &rhs)
  {
    return (lhs * rhs) / gcd(lhs, rhs);
  }

  struct State
  {
    std::string from;
    std::string to;
    std::size_t pulse;
  };

  struct Node
  {
    char                                         type;
    std::string                                  name;
    aoc::vstring                                 outputs;
    std::unordered_map<std::string, std::size_t> memory;

    Node() = default;
    Node(const char &type, const std::string &name, const aoc::vstring &outputs) : type{type}, name{name}, outputs{outputs}
    {
      if (!this->is_conjunction())
        this->memory["."] = 0;
    }

    std::size_t pulse()
    {
      if (this->is_conjunction())
      {
        for (const auto &elem : this->memory)
          if (elem.second == 0)
            return 1;
        return 0;
      }
      else
        return this->memory["."];
    }

    bool is_conjunction() const { return this->type == '&'; }

    std::vector<State> execute(const std::string &from, const std::size_t &pulse)
    {
      std::vector<State> out;
      out.reserve(this->outputs.size());

      if (this->is_conjunction())
        this->memory[from] = pulse;
      else
      {
        if (pulse == 1) return out;
        this->memory["."] = 1 - this->memory["."];
      }

      std::size_t out_pulse = this->pulse();
      for (const auto &output : this->outputs)
        out.emplace_back(State{this->name, output, out_pulse});

      return out;
    }
  };

  struct Graph : public std::unordered_map<std::string, Node>
  {
    aoc::vstring broadcaster_targets;
    explicit Graph(const aoc::vstring &input)
    {
      for (const auto &line : input)
      {
        aoc::vstring outputs = aoc::parse::split_by_delimiters(line, "->, ");
        std::string  name    = outputs.front();
        outputs.erase(outputs.begin());
        if (name == "broadcaster")
          this->broadcaster_targets = outputs;
        else
          this->add(name, outputs);
      }
    }

    void add(const std::string &lhs, const aoc::vstring &rhs)
    {
      char        type = lhs.front();
      std::string name = lhs.substr(1);
      this->insert({name, Node(type, name, rhs)});
    }

    std::size_t solve()
    {
      std::size_t low = 0, high = 0;
      for (std::size_t _ = 0; _ < 1000; ++_)
      {
        low += 1;
        std::queue<State> q;
        for (const auto &broadcaster_target : this->broadcaster_targets)
          q.push(State{"broadcaster", broadcaster_target, 0});

        while (!q.empty())
        {
          State state = q.front();
          q.pop();

          state.pulse == 0 ? low++ : high++;
          if (this->find(state.to) == this->end()) continue;

          std::vector<State> new_states = this->at(state.to).execute(state.from, state.pulse);
          for (const auto &new_state : new_states)
            q.push(new_state);
        }
      }
      return low * high;
    }

    std::vector<std::string> inputs(const std::string &to) const
    {
      std::vector<std::string> out;
      for (auto it = this->cbegin(); it != this->cend(); ++it)
        if (std::find(it->second.outputs.cbegin(), it->second.outputs.cend(), to) != it->second.outputs.cend())
          out.emplace_back(it->first);
      return out;
    }

    std::size_t simulate_till(const std::string &to, const std::size_t &desired_pulse) const
    {
      Graph       copy   = *this;
      std::size_t cycles = 0;
      while (true)
      {
        cycles++;
        std::queue<State> q;
        for (const auto &broadcaster_target : copy.broadcaster_targets)
          q.push(State{"broadcaster", broadcaster_target, 0});
        while (!q.empty())
        {
          State state = q.front();
          q.pop();
          if (copy.find(state.to) == copy.end()) continue;
          std::vector<State> new_states = copy.at(state.to).execute(state.from, state.pulse);
          for (const auto &new_state : new_states)
          {
            if (new_state.to == to && new_state.pulse == desired_pulse) return cycles;
            q.push(new_state);
          }
        }
      }
    }

    std::vector<std::size_t> count(const std::string &to, const std::size_t &desired_pulse)
    {
      std::vector<std::size_t> out;
      std::vector<std::string> in = this->inputs(to);

      if (in.size() == 1)
        out = count(in.front(), this->at(in.front()).is_conjunction() ? 0 : 1);
      else
        for (const auto &node : in)
          out.emplace_back(this->simulate_till(node, desired_pulse));
      return out;
    }
  };

} // namespace

std::size_t aoc::day20::part1(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);

  Graph graph(input);
  // fill memory
  for (const auto &node : graph)
    for (const auto &output : node.second.outputs)
      if (graph.find(output) != graph.end() && graph[output].is_conjunction())
        graph[output].memory[node.first] = 0;

  return graph.solve();
}

std::size_t aoc::day20::part2(const std::string &filename)
{
  aoc::vstring input = aoc::parse::cvt_file_to_vstring(filename);

  Graph graph(input);
  // fill memory
  for (const auto &node : graph)
    for (const auto &output : node.second.outputs)
      if (graph.find(output) != graph.end() && graph[output].is_conjunction())
        graph[output].memory[node.first] = 0;

  std::vector<std::size_t> cycles = graph.count("rx", 0);
  std::size_t              result = 1;
  for (const auto &cycle : cycles)
    result = lcm(result, cycle);
  return result;
}

#ifndef COMMON_HPP_1FEF0AA8_6133_EE17_A063_0828B7862D32
#define COMMON_HPP_1FEF0AA8_6133_EE17_A063_0828B7862D32

#include <libfunction/all.hpp>
#include <libfunction/protocol_buffer.hpp>
#include <libfunction/protocol_sql.hpp>

#include <libhse/pipeline.hpp>

#include <nlohmann-json/json.hpp>

#include <random>

using json = nlohmann::json;
using namespace hse::pipeline;
using namespace protocol;
using namespace biz_helper;

static auto rand_number_maker(std::size_t begin = 1, std::size_t end = 10000)
{
  return [eng(std::mt19937{ std::random_device{}() }), dist(std::uniform_int_distribution<>{1, 10000})]() mutable {
    return dist(eng);
  };
}

template<typename List>
static auto append_to(List& list)
{
  return [&list](auto&& obj) {
    list.push_back(std::forward<decltype(obj)>(obj));
  };
}

#endif //COMMON_HPP_1FEF0AA8_6133_EE17_A063_0828B7862D32
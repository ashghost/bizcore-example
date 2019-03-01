#include "common.hpp"

#include <libbizcore/bizcore_request.h>

DEC_VERSION("updates", "world updates", "0001", "")

DEC_SAFE_MAIN_ENTRY(protocol::buffer_stream)

static const char sql_select[] = R"(SELECT id FROM world WHERE id = ?)";
static const char sql_update[] = R"(UPDATE world SET randomNumber = ? WHERE id = ?)";

void function_safe_call(const protocol::buffer_stream::context& ctx)
{
  const char* queries = bizcore_request_prop("#queries");
  if (queries == nullptr || *queries == '\0') {
    queries = "1";
  }
  const auto count = std::min(std::max(atoi(queries), 1), 500);
  json list(json::value_t::array);
  auto rand_number = rand_number_maker();
  for (int i = 0; i < count; i++) {
    const auto id = rand_number();
    const auto new_random_number = rand_number();
    auto record = sql::stmt(sql_select, id) | send_to("db") | sql::unpacker | sql::table | sql::object;
    sql::stmt(sql_update, new_random_number, id) | send_to("db") | sql::unpacker;
    record["randomNumber"] = new_random_number;
    list.push_back(std::move(record));
  }
  ctx.response(list.dump());
}
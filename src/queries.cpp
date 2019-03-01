#include "common.hpp"

#include <libbizcore/bizcore_request.h>

DEC_VERSION("queries", "world queries", "0001", "")

DEC_SAFE_MAIN_ENTRY(protocol::buffer_stream)

static const char sql_select[] = R"(SELECT id, randomNumber FROM world WHERE id = ?)";

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
    sql::stmt(sql_select, rand_number())
      | send_to("db")
      | sql::unpacker
      | sql::table
      | sql::object
      | append_to(list);
  }
  ctx.response(list.dump());
}
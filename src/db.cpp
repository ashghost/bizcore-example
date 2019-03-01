#include "common.hpp"

DEC_VERSION("db", "world query", "0001", "")

DEC_SAFE_MAIN_ENTRY(protocol::buffer_stream)

static const char sql_select[] = R"(SELECT id, randomNumber FROM world WHERE id = ?)";

void function_safe_call(const protocol::buffer_stream::context& ctx)
{
  auto rand_number = rand_number_maker();
  auto record = sql::stmt(sql_select, rand_number())
    | send_to("db")
    | sql::unpacker
    | sql::table
    | sql::object;
  ctx.response(record.dump());
}
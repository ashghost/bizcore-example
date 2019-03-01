#include <libfunction/function.hpp>
#include <libfunction/protocol_buffer.hpp>

#include <nlohmann-json/json.hpp>

DEC_VERSION("json", "json query", "0001", "")

DEC_SAFE_MAIN_ENTRY(protocol::buffer_stream)

using json = nlohmann::json;

void function_safe_call(const protocol::buffer_stream::context& ctx)
{
  ctx.response(json{{"message", "Hello, World!"}}.dump());
}
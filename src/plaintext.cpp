#include <libfunction/function.hpp>
#include <libfunction/protocol_buffer.hpp>

DEC_VERSION("plaintext", "plaintext query", "0001", "")

DEC_SAFE_MAIN_ENTRY(protocol::buffer_stream)

void function_safe_call(const protocol::buffer_stream::context& ctx)
{
  ctx.response("Hello, World!");
}
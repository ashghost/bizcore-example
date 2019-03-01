#include "common.hpp"

#include <sstream>

DEC_VERSION("fortunes", "fortunes query", "0001", "")

DEC_SAFE_MAIN_ENTRY(protocol::buffer_stream)

static const char sql_select[] = R"(SELECT id, message FROM fortune)";

static auto sort_by(const std::string& field)
{
  return [&field](auto&& obj_list) {
    std::sort(std::begin(obj_list), std::end(obj_list), [&field](const auto& left, const auto& right) {
      return left[field] < right[field];
    });
  };
}

static auto escape_html(const std::string& data)
{
  std::string buffer;
  buffer.reserve(data.size());
  for(auto c : data) {
    switch(c) {
      case '&': buffer.append("&amp;"); break;
      case '"': buffer.append("&quot;"); break;
      case '\'': buffer.append("&apos;"); break;
      case '<': buffer.append("&lt;"); break;
      case '>': buffer.append("&gt;"); break;
      default: buffer.append(1, c); break;
    }
  }
  return buffer;
}

static auto append_fortune_object(size_t id, const std::string& message)
{
  return [&message, &id](auto&& list) {
    list.push_back(json{
      {"id", id},
      {"message", message}
    });
  };
}

static auto append_fortune_tr(std::ostream& os)
{
  return [&os](const json& fortune) {
    os << "<tr><td>"
      << fortune["id"].get<std::string>()
      << "</td><td>"
      << escape_html(fortune["message"])
      << "</td></tr>";
  };
}

void function_safe_call(const protocol::buffer_stream::context& ctx)
{
  std::ostringstream os;
  os << "<!DOCTYPE html><html><head><title>Fortunes</title></head>"
    "<body><table><tr><th>id</th><th>message</th></tr>";
  sql::stmt(sql_select)
    | send_to("db")
    | sql::unpacker
    | sql::table
    | sql::object_list
    | append_fortune_object(0, "Additional fortune added at request time.")
    | sort_by("message")
    | sql::map(append_fortune_tr(os));
  os << "</table></body></html>";
  ctx.response(os.str());
}
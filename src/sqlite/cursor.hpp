#pragma once
#include "stl.hpp"

// forward delcare these structs to keep from having to include paths propigate
namespace mx3 { namespace sqlite {

class Stmt;

class Cursor final {
  public:
    // this is a move-only type
    Cursor(const Cursor&) = delete;
    Cursor(Cursor&&) = default;
    Cursor& operator=(const Cursor&) = delete;

    bool is_valid() { return m_is_valid; }
    void next();

    string column_name(int pos) const;
    int column_count() const;

    int32_t int_value(int pos);
    int64_t int64_value(int pos);
    double double_value(int pos);
    string string_value(int pos);
    vector<uint8_t> blob_value(int pos);

  private:
    friend class Stmt;
    Cursor(shared_ptr<Stmt> stmt, bool is_valid);

    // this keeps the statement alive while we are executing the query
    shared_ptr<Stmt> m_stmt;
    bool m_is_valid;
    unique_ptr<bool> m_dont_let_anyone_copy_me;
};

} }

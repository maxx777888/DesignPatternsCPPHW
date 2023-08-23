#include <iostream>

struct Query {
    std::string column = "*";
    std::string table = "*";
    std::string whereQuery;
    std::string query_to_send;
};

class SqlSelectQueryBuilder {
public:
    SqlSelectQueryBuilder& AddColumn(std::string col) {
        if (query.column == "*") {
            query.column = col;
        }
        else {
            query.column += ", " + col;
        }
        return *this;    
    }
    SqlSelectQueryBuilder& AddFrom(std::string tab) {
        query.table = tab;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(std::string col, std::string row) {
        if (query.whereQuery.empty()) {
            query.whereQuery = col + "=" + row;
        }
        else {
            query.whereQuery += " AND " + col + "=" + row;
        }
        return *this;
    }

    std::string BuildQuery() {

        if (query.whereQuery.empty()) {
            query.query_to_send = "SELECT " + query.column + " FROM "
                + query.table + ";";
        }
        else {
            query.query_to_send = "SELECT " + query.column + " FROM "
                + query.table + " WHERE " + query.whereQuery + ";";
        }
        return query.query_to_send;
    }

private:
    Query query;
};

int main()
{
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    std::cout << query_builder.BuildQuery() << std::endl;

    //Не нашел способа как исправить эту функцию, постоянно выдает ошибку!
    /*static_assert(query_builder.BuildQuery() == 
        "SELECT name, phone FROM students WHERE id=42 AND name=John;", 
        "ERROR"
        );*/
}


#ifndef QUERY_PTRS_STORAGE_HPP
#define QUERY_PTRS_STORAGE_HPP

#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/at_key.hpp>
#include <boost/fusion/include/value_at_key.hpp>
#include <boost/weak_ptr.hpp>

#include <map>

#include "queries.h"
#include "query_ptrs_storage_fwd.hpp"


namespace gle
{

using namespace boost;

struct query_ptrs_storage_t
{
    template<class Query>
    void delete_query(Query * query)
    {
        fusion::at_key<Query>(queries_).erase(query->gl_id());
        delete query;
    }

    template<class QueryPtr>
    QueryPtr register_query(QueryPtr query)
    {
        typedef typename QueryPtr::element_type query_type;
        fusion::at_key<query_type>(queries_)[query->gl_id()] = query;
        return query;
    }

    template<class QueryPtr>
    QueryPtr find_query(GLuint id) const
    {
        typedef typename QueryPtr::element_type query_type;
        typedef typename fusion::result_of::value_at_key<query_ptrs_map_t, query_type>::type map_type;
        map_type const& map = fusion::at_key<query_type>(queries_);
        typename map_type::const_iterator it = map.find(id);
        if (it == map.end())
            return QueryPtr();
        else
            return it->second.lock();
    }

private:
    template<class Query>
    struct query_entry_gen
    {
        typedef fusion::pair< Query, std::map<GLuint, weak_ptr<Query> > > type;
    };

    typedef fusion::map< query_entry_gen<i_primitives_generated_query>::type,
                         query_entry_gen<i_any_samples_passed_conservative_query>::type,
                         query_entry_gen<i_any_samples_passed_query>::type,
                         query_entry_gen<i_samples_passed_query>::type,
                         query_entry_gen<i_timestamp_query>::type,
                         query_entry_gen<i_time_elapsed_query>::type,
                         query_entry_gen<i_transform_feedback_primitives_written_query>::type
                      > query_ptrs_map_t;

private:
    query_ptrs_map_t queries_;
};


}

#endif // QUERY_PTRS_STORAGE_HPP

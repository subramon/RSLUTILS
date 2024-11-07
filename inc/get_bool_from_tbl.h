extern int
get_bool_from_tbl(
    lua_State *L, 
    int stack_index,
    const char * const key,
    bool *ptr_is_key,
    bool *ptr_val
    );

extern int
get_int_from_tbl(
    lua_State *L, 
    int stack_index,
    const char * const key,
    bool *ptr_is_key,
    int64_t *ptr_itmp
    );

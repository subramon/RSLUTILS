extern int
get_num_from_tbl(
    lua_State *L, 
    int stack_index,
    const char * const key,
    bool *ptr_is_key,
    double *ptr_dtmp
    );

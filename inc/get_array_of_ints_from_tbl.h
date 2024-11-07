extern int 
get_array_of_ints_from_tbl(
      lua_State *L,
      int stack_index,
      const char * const key,
      bool *ptr_is_key,
      int64_t *out, // allocated before call  /[n_out]
      int n_out
      );

extern int 
get_array_of_strings_from_tbl(
      lua_State *L,
      int stack_index,
      const char * const key,
      bool *ptr_is_key,
      const char **file_names, // [n] 
      int n
      );

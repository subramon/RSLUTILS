extern int 
get_array_of_nums(
      lua_State *L,
      int stack_index,
      double **ptr_X, // [nX][...] Lua stores number as double
      uint32_t *ptr_nX
      );

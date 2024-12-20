#include <lualib.h>
extern int 
get_array_of_strings(
      lua_State *L,
      int stack_index,
      char ***ptr_X, // [nX][...]
      uint32_t *ptr_nX
    );

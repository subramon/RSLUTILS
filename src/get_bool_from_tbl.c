#include "luaconf.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "q_incs.h"
#include "get_bool_from_tbl.h"
int
get_bool_from_tbl(
    lua_State *L, 
    int stack_index,
    const char * const key,
    bool *ptr_is_key,
    bool *ptr_val
    )
{
  int status = 0;
  *ptr_val = false; *ptr_is_key = false;
  //------------------- 
  int n = lua_gettop(L); if ( n < stack_index ) { go_BYE(-1); }
  lua_getfield (L, stack_index, key);
  int m = lua_gettop(L); if ( m != (n+1) ) { go_BYE(-1); }
  if  ( lua_type(L, m) != LUA_TBOOLEAN ) { 
    *ptr_is_key = false; goto BYE;
  }
  *ptr_val = lua_toboolean(L, m);
  *ptr_is_key = true;
BYE:
  lua_pop(L, 1);
  m = lua_gettop(L); if ( m != n  ) { go_BYE(-1); }
  return status;
}

#include "luaconf.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "q_incs.h"
#include "get_array_of_ints_from_tbl.h"

int 
get_array_of_ints_from_tbl(
      lua_State *L,
      int stack_index,
      const char * const key,
      bool *ptr_is_key,
      int64_t *out, // allocated before call  /[n_out]
      int n_out
      )
{
  int status = 0; 
  if ( out == NULL ) { go_BYE(-1); }
  *ptr_is_key = false;
  int n_on_stack = lua_gettop(L);
  int n = lua_gettop(L); if ( n < stack_index ) { go_BYE(-1); }
  lua_getfield (L, stack_index, key); 
  int m = lua_gettop(L); if ( m != (n+1) ) { go_BYE(-1); }
  if  ( lua_type(L, m) != LUA_TTABLE ) { 
    *ptr_is_key = false; goto BYE;
  }
  int chk_n = luaL_getn(L, m);
  if ( chk_n != n_out ) { go_BYE(-1); }
  for ( int i = 0; i < n_out; i++ ) { 
    lua_rawgeti(L, m, i+1);
    n = lua_gettop(L);
    if ( n != m+1 ) { go_BYE(-1); }
    out[i] = luaL_checknumber(L, m+1);
    lua_pop(L, 1);
    n = lua_gettop(L);
    if ( n != m ) { go_BYE(-1); }
  }

  *ptr_is_key = true;
BYE:
  lua_pop(L, 1);
  n = lua_gettop(L); if ( n != n_on_stack  ) { go_BYE(-1); }
  return status;
}

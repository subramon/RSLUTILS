#include "luaconf.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "q_incs.h"
#include "get_array_of_strings_from_tbl.h"
int 
get_array_of_strings_from_tbl(
      lua_State *L,
      int stack_index,
      const char * const key,
      bool *ptr_is_key,
      const char **file_names, // [n] 
      int n
      )
{
  int status = 0; 
  *ptr_is_key = false;
  int nstack = lua_gettop(L); 
  if ( nstack < stack_index ) { go_BYE(-1); }
  lua_getfield (L, 1, key); 
  nstack = lua_gettop(L); 
  if ( nstack != (1+1) ) { go_BYE(-1); }
  if  ( lua_type(L, 1+1) != LUA_TTABLE ) { 
    *ptr_is_key = false; goto BYE;
  }
  int chk_n = luaL_getn(L, 1+1);
  if ( chk_n != n ) { go_BYE(-1); }
  for ( int i = 0; i < n; i++ ) { 
    lua_rawgeti(L, 1+1, i+1);
    nstack = lua_gettop(L);
    if ( nstack != 1+1+1 ) { go_BYE(-1); }
    file_names[i] = luaL_checkstring(L, 1+1+1);
    lua_pop(L, 1);
    nstack = lua_gettop(L);
    if ( nstack != 1+1 ) { go_BYE(-1); }
  }

  *ptr_is_key = true;
BYE:
  lua_pop(L, 1);
  n = lua_gettop(L); if ( n != 1  ) { go_BYE(-1); }
  return status;
}

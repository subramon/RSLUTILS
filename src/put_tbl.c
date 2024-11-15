#include "luaconf.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "q_macros.h"
#include "put_tbl.h"
int
put_str_tbl(
    lua_State *L, 
    char **X, // [nX]
    int nX
    )
{
  int status = 0;
  lua_newtable(L);
  for ( int i = 0; i < nX; i++ ) { 
    lua_pushnumber(L, i);
    lua_pushstring(L, X[i]);
    lua_settable(L, -3);
  }
BYE:
  return status;
  // remember to set C to Lua return value to include this table 
}

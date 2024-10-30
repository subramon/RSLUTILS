#include "luaconf.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "q_incs.h"
#include "check_args_is_table.h"
int 
check_args_is_table(
    lua_State *L
    )
{
  int status =0;
  int num_args = lua_gettop(L); if ( num_args != 1 ) { go_BYE(-1); }
  if ( !lua_istable(L, 1) ) { go_BYE(-1); }
  luaL_checktype(L, 1, LUA_TTABLE ); // another way of checking
BYE:
  return status;
}

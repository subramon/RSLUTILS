#include "luaconf.h"
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include "q_incs.h"
#include "aux_lua_to_c.h"
int check_args_is_table(
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
int get_str_from_tbl(
      lua_State *L,
      int stack_index,
      const char * const key,
      bool *ptr_is_key,
      const char **ptr_cptr
      )
{
  int status = 0; 
  *ptr_cptr = NULL; *ptr_is_key = false;
  //----------------------------
  int n = lua_gettop(L); if ( n < stack_index ) { go_BYE(-1); }
  lua_getfield (L, stack_index, key); 
  int m = lua_gettop(L); if ( m != (n+1) ) { go_BYE(-1); }
  if  ( lua_type(L, m) != LUA_TSTRING ) { 
    *ptr_is_key = false; goto BYE;
  }
  *ptr_cptr = luaL_checkstring(L, m);
  *ptr_is_key = true;
BYE:
  lua_pop(L, 1);
  m = lua_gettop(L); if ( m != n  ) { go_BYE(-1); }
  return status;
}
int
get_int_from_tbl(
    lua_State *L, 
    int stack_index,
    const char * const key,
    bool *ptr_is_key,
    int64_t *ptr_itmp
    )
{
  int status = 0;
  *ptr_itmp = -1; *ptr_is_key = false;
  //------------------- 
  int n = lua_gettop(L); if ( n < stack_index ) { go_BYE(-1); }
  lua_getfield (L, stack_index, key);
  int m = lua_gettop(L); if ( m != (n+1) ) { go_BYE(-1); }
  if  ( lua_type(L, m) != LUA_TNUMBER ) { 
    *ptr_is_key = false; goto BYE;
  }
  *ptr_itmp = luaL_checknumber(L, m);
  *ptr_is_key = true;
BYE:
  lua_pop(L, 1);
  m = lua_gettop(L); if ( m != n  ) { go_BYE(-1); }
  return status;
}
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
// Set globals in C in main program after creating Lua state
// but before doing anything else
// chunk_size, memory structures, ...


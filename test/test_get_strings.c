#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <lua.h>
#include <lualib.h>
#include "q_macros.h"
#include "get_array_of_strings.h"
#include "mk_lua_state.h"

int
main(
    )
{
  int status = 0;
  lua_State *L = NULL;
  char **X = NULL; uint32_t nX = 0;

  L = mk_lua_state(); if ( L == NULL ) { go_BYE(-1); }
  status = luaL_dostring(L, "foo = require 'return_array_of_strings'");
  int chk = lua_gettop(L); if ( chk != 0 ) { go_BYE(-1); }
  //--------------------
  lua_getglobal(L, "foo");
  chk = lua_gettop(L); if ( chk != 1 ) { go_BYE(-1); }
  if ( !lua_isfunction(L, -1)) {
    fprintf(stderr, "Lua Function %s undefined\n", "foo");
    lua_pop(L, 1);
    go_BYE(-1);
  }
  // call lua function and check status 
  status = lua_pcall(L, 0, 2, 0);
  if ( status != 0 ) {
    fprintf(stderr, "lua_fn %s failed: %s\n", "foo", lua_tostring(L, -1));
    lua_pop(L, 1);
    go_BYE(-1); 
  }
  status = get_array_of_strings(L, 2, &X, &nX); cBYE(status);
  for ( uint32_t i = 0; i < nX; i++ ) { 
    printf("%u:%s\n", i, X[i]);
  }
  printf("All done\n");
BYE:
  if ( X != NULL ) { 
    for ( uint32_t i = 0; i < nX; i++ ) { 
      free_if_non_null(X[i]);
    }
    free_if_non_null(X);
  }
  return status;
}

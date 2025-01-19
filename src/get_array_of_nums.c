#include <lauxlib.h>
#include <lualib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "q_macros.h"
#include "get_array_of_nums.h"
int 
get_array_of_nums(
      lua_State *L,
      int stack_index,
      double **ptr_X, // [nX][...] Lua stores number as double
      uint32_t *ptr_nX
      )
{
  int status = 0; 
  uint32_t nX = 0, szX = 16; // initial guess of 16 
  double *X = NULL;
  int n_before, n_after, n1, n2;

  X = malloc(szX * sizeof(double));
  memset(X, 0,  szX * sizeof(double));

  n_before = lua_gettop(L); 
  if ( n_before < stack_index ) { go_BYE(-1); }

  for ( int i = 1; ; i++ ) {  // Note i is Lua index, not C 
#ifdef DEBUG
    n1 = lua_gettop(L); 
#endif
    lua_rawgeti(L, stack_index, i);
#ifdef DEBUG
    n2 = lua_gettop(L);
    if ( n2 != n1 + 1 )  { go_BYE(-1); }
#endif
    int ltype = lua_type(L, -1); 
    if ( ltype == LUA_TNIL ) { 
      lua_pop(L, 1); 
      break;
    }
    if ( ltype != LUA_TNUMBER ) { 
      lua_pop(L, 1); 
      go_BYE(-1); 
    } 
    nX++; 
    if ( nX > szX ) { // reallocate 
      szX *= 2; 
      double *newX = malloc(szX * sizeof(double));
      memset(newX, 0, szX * sizeof(double));
      for ( uint32_t j = 0; j < nX; j++ ) { 
        newX[j] = X[j];
      }
      free(X); 
      X = newX; 
    }
    X[nX-1] = luaL_checknumber(L, -1);
    lua_pop(L, 1);
#ifdef DEBUG
    int n3  = lua_gettop(L);
    if ( n3 != n1 ) { go_BYE(-1); }
#endif
  }

  *ptr_X  = X;
  *ptr_nX = nX;
BYE:
  n_after = lua_gettop(L); 
  if ( n_before != n_after ) { WHEREAMI; status = -1; }
  if ( status != 0 ) {
    free_if_non_null(X);
    *ptr_X = NULL;
    *ptr_nX = 0;
  }
  return status;
}

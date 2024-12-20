local function foo()
  local T = { "abc", "def", "ghi", }
  nT = #T
  print("nT = ", nT)
  return nT, T
end
return foo

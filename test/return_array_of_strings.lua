local function return_array_of_strings()
  local T = { "abc", "def", "ghi", }
  nT = #T
  print("nT = ", nT)
  return nT, T
end
return return_array_of_strings

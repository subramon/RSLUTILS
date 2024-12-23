local function return_array_of_nums()
  local T = { 123, 456, 789.01, }
  nT = #T
  print("nT = ", nT)
  return nT, T
end
return return_array_of_nums

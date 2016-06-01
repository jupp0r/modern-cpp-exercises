file(REMOVE_RECURSE
  "exercise1.pdb"
  "exercise1"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/exercise1.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()

add_library(htopml-json JsonState.cpp TypeToJson.cpp)
SET_TARGET_PROPERTIES(htopml-json PROPERTIES COMPILE_FLAGS -fPIC)
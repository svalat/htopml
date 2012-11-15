add_library(type_to_json JsonState.cpp TypeToJson.cpp)
SET_TARGET_PROPERTIES(type_to_json PROPERTIES COMPILE_FLAGS -fPIC)
add_library(htopml-server DirectoryWebNode.cpp FileWebNode.cpp ValidationWebNode.cpp Server.cpp WebNode.cpp)
target_link_libraries(htopml-server mongoose)
SET_TARGET_PROPERTIES(htopml-server PROPERTIES COMPILE_FLAGS -fPIC)

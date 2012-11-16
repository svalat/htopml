add_library(htopml-web-nodes GnuplotWebNode.cpp GetRusageWebNode.cpp)
SET_TARGET_PROPERTIES(htopml-web-nodes PROPERTIES COMPILE_FLAGS -fPIC)
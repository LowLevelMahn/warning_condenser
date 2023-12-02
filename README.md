# warning_condenser
simple C++ tools for condesing duplicated warnings in build output of gcc,clang

just grab all the build warnings with 

[build command] > out.txt 2>&1
build command can be make, cmake, a direct gcc,g++,clang,clang++ line, etc.

and this tool will sort the warnings by type and occurence
better see relevant warnings or start reducing them beginning with the most occureing

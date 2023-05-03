# CMake generated Testfile for 
# Source directory: C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp
# Build directory: C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(build_cryptest "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" "--build" "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug" "--target" "cryptest")
set_tests_properties(build_cryptest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/CMakeLists.txt;253;add_test;C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/CMakeLists.txt;0;")
add_test(cryptest "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug/cryptest.exe" "v")
set_tests_properties(cryptest PROPERTIES  DEPENDS "build_cryptest" _BACKTRACE_TRIPLES "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/CMakeLists.txt;254;add_test;C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/CMakeLists.txt;0;")

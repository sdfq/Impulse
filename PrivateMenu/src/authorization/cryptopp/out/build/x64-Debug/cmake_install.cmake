# Install script for directory: C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "c:/users/administration/source/repos/brothel-updated/privatemenu/src/authorization/cryptopp/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug/cryptopp-shared.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug/cryptopp-shared.dll")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug/cryptopp-static.lib")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cryptopp" TYPE FILE FILES
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/3way.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/adler32.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/aes.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/algebra.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/algparam.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/arc4.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/argnames.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/asn.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/authenc.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/base32.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/base64.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/basecode.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/bench.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/blake2.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/blowfish.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/blumshub.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/camellia.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/cast.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/cbcmac.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/ccm.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/chacha.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/channels.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/cmac.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/config.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/cpu.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/crc.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/cryptlib.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/default.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/des.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/dh.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/dh2.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/dll.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/dmac.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/dsa.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/eax.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/ec2n.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/eccrypto.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/ecp.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/elgamal.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/emsa2.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/eprecomp.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/esign.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/factory.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/fhmqv.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/files.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/filters.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/fips140.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/fltrimpl.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/gcm.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/gf256.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/gf2_32.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/gf2n.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/gfpcrypt.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/gost.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/gzip.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/hex.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/hkdf.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/hmac.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/hmqv.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/hrtimer.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/ida.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/idea.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/integer.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/iterhash.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/keccak.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/lubyrack.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/luc.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/mars.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/md2.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/md4.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/md5.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/mdc.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/mersenne.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/misc.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/modarith.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/modes.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/modexppc.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/mqueue.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/mqv.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/nbtheory.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/network.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/nr.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/oaep.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/oids.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/osrng.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/panama.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/pch.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/pkcspad.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/polynomi.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/pssr.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/pubkey.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/pwdbased.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/queue.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/rabin.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/randpool.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/rc2.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/rc5.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/rc6.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/rdrand.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/resource.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/rijndael.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/ripemd.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/rng.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/rsa.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/rw.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/safer.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/salsa.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/seal.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/secblock.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/seckey.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/seed.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/serpent.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/serpentp.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/sha.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/sha3.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/shacal2.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/shark.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/simple.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/skipjack.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/smartptr.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/socketft.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/sosemanuk.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/square.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/stdcpp.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/strciphr.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/tea.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/tiger.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/trdlocal.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/trunhash.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/ttmac.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/twofish.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/validate.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/vmac.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/wait.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/wake.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/whrlpool.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/winpipes.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/words.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/xtr.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/xtrcrypt.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/zdeflate.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/zinflate.h"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/zlib.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/cryptopp" TYPE FILE FILES
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/cryptopp-config.cmake"
    "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug/cryptopp-config-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cryptopp/cryptopp-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cryptopp/cryptopp-targets.cmake"
         "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug/CMakeFiles/Export/lib/cmake/cryptopp/cryptopp-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cryptopp/cryptopp-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/cryptopp/cryptopp-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/cryptopp" TYPE FILE FILES "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug/CMakeFiles/Export/lib/cmake/cryptopp/cryptopp-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/cryptopp" TYPE FILE FILES "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug/CMakeFiles/Export/lib/cmake/cryptopp/cryptopp-targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug/cryptest.exe")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cryptopp" TYPE DIRECTORY FILES "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/TestData")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/cryptopp" TYPE DIRECTORY FILES "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/TestVectors")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Administration/source/repos/brothel-updated/PrivateMenu/src/authorization/cryptopp/out/build/x64-Debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

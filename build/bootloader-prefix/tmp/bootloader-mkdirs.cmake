# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/esp/esp-idf-v5.0.2/components/bootloader/subproject"
  "C:/Sources/ESP32/test1/build/bootloader"
  "C:/Sources/ESP32/test1/build/bootloader-prefix"
  "C:/Sources/ESP32/test1/build/bootloader-prefix/tmp"
  "C:/Sources/ESP32/test1/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Sources/ESP32/test1/build/bootloader-prefix/src"
  "C:/Sources/ESP32/test1/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Sources/ESP32/test1/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Sources/ESP32/test1/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()

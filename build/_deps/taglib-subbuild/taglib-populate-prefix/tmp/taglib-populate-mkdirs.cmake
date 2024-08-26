# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/znschaffer/src/plyr/build/_deps/taglib-src"
  "/Users/znschaffer/src/plyr/build/_deps/taglib-build"
  "/Users/znschaffer/src/plyr/build/_deps/taglib-subbuild/taglib-populate-prefix"
  "/Users/znschaffer/src/plyr/build/_deps/taglib-subbuild/taglib-populate-prefix/tmp"
  "/Users/znschaffer/src/plyr/build/_deps/taglib-subbuild/taglib-populate-prefix/src/taglib-populate-stamp"
  "/Users/znschaffer/src/plyr/build/_deps/taglib-subbuild/taglib-populate-prefix/src"
  "/Users/znschaffer/src/plyr/build/_deps/taglib-subbuild/taglib-populate-prefix/src/taglib-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/znschaffer/src/plyr/build/_deps/taglib-subbuild/taglib-populate-prefix/src/taglib-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/znschaffer/src/plyr/build/_deps/taglib-subbuild/taglib-populate-prefix/src/taglib-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()

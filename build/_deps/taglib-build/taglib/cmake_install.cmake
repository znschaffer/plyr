# Install script for directory: /Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/opt/homebrew/opt/llvm/bin/llvm-objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/znschaffer/src/plyr/build/_deps/taglib-build/taglib/libtag.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtag.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtag.a")
    execute_process(COMMAND "/opt/homebrew/opt/llvm/bin/llvm-ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libtag.a")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/taglib" TYPE FILE FILES
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/tag.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/fileref.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/audioproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/taglib_export.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/taglib.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tstring.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tlist.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tlist.tcc"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tstringlist.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tbytevector.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tbytevectorlist.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tvariant.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tbytevectorstream.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tiostream.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tfilestream.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tmap.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tmap.tcc"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tpicturetype.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tpropertymap.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tdebuglistener.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/toolkit/tversionnumber.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/mpegfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/mpegproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/mpegheader.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/xingheader.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v1/id3v1tag.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v1/id3v1genres.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/id3v2.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/id3v2extendedheader.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/id3v2frame.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/id3v2header.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/id3v2synchdata.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/id3v2footer.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/id3v2framefactory.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/id3v2tag.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/attachedpictureframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/commentsframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/eventtimingcodesframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/generalencapsulatedobjectframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/ownershipframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/popularimeterframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/privateframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/relativevolumeframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/synchronizedlyricsframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/textidentificationframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/uniquefileidentifierframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/unknownframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/unsynchronizedlyricsframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/urllinkframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/chapterframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/tableofcontentsframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpeg/id3v2/frames/podcastframe.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ogg/oggfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ogg/oggpage.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ogg/oggpageheader.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ogg/xiphcomment.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ogg/vorbis/vorbisfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ogg/vorbis/vorbisproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ogg/flac/oggflacfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ogg/speex/speexfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ogg/speex/speexproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ogg/opus/opusfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ogg/opus/opusproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/flac/flacfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/flac/flacpicture.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/flac/flacproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/flac/flacmetadatablock.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ape/apefile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ape/apeproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ape/apetag.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ape/apefooter.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/ape/apeitem.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpc/mpcfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mpc/mpcproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/wavpack/wavpackfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/wavpack/wavpackproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/trueaudio/trueaudiofile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/trueaudio/trueaudioproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/riff/rifffile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/riff/aiff/aifffile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/riff/aiff/aiffproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/riff/wav/wavfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/riff/wav/wavproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/riff/wav/infotag.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/asf/asffile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/asf/asfproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/asf/asftag.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/asf/asfattribute.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/asf/asfpicture.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mp4/mp4file.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mp4/mp4atom.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mp4/mp4tag.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mp4/mp4item.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mp4/mp4properties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mp4/mp4coverart.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mp4/mp4itemfactory.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mod/modfilebase.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mod/modfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mod/modtag.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/mod/modproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/it/itfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/it/itproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/s3m/s3mfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/s3m/s3mproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/xm/xmfile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/xm/xmproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/dsf/dsffile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/dsf/dsfproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/dsdiff/dsdifffile.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/dsdiff/dsdiffproperties.h"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-src/taglib/dsdiff/dsdiffdiintag.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib/taglib-targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib/taglib-targets.cmake"
         "/Users/znschaffer/src/plyr/build/_deps/taglib-build/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib/taglib-targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib/taglib-targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "/Users/znschaffer/src/plyr/build/_deps/taglib-build/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^()$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES "/Users/znschaffer/src/plyr/build/_deps/taglib-build/taglib/CMakeFiles/Export/398eef5e047a0959864f2888198961bf/taglib-targets-noconfig.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/taglib" TYPE FILE FILES
    "/Users/znschaffer/src/plyr/build/_deps/taglib-build/taglib-config.cmake"
    "/Users/znschaffer/src/plyr/build/_deps/taglib-build/taglib-config-version.cmake"
    )
endif()


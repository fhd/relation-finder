# Installs and configures the supplied FILES from the current directory
# into the DESTINATION directory. In the case of install, it's
# ${CMAKE_INSTALL_DIR}/${install_dir}/${destination}, in the case of
# configure it's ${CMAKE_BINARY_DIR}/${destination}.

macro(configure_and_install files destination)
  foreach(file ${files})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${file}
      ${CMAKE_BINARY_DIR}/${destination}/${file} COPYONLY)
    install(FILES ${file} DESTINATION ${destination}
      RENAME ${file})
  endforeach(file)
endmacro(configure_and_install)
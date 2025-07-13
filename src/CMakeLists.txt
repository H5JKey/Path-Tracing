file(GLOB SOURCES
    "*.cpp"
)

add_executable(Path-Tracing
    ${SOURCES}
)

target_link_libraries(Path-Tracing PRIVATE 
  ImGui-SFML::ImGui-SFML
)


if(WIN32)
  if (BUILD_SHARED_LIBS)
    add_custom_command(TARGET Path-Tracing POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_if_different
          $<TARGET_FILE:ImGui-SFML::ImGui-SFML>
          $<TARGET_FILE:sfml-graphics>
          $<TARGET_FILE:sfml-window>
          $<TARGET_FILE:sfml-system>
          $<TARGET_FILE_DIR:Path-Tracing>)
  endif()
endif()


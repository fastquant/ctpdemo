include_directories(${PROJECT_SOURCE_DIR}/src ${CTP_INCLUDES})
add_executable(ctpdemo main.cpp mdspi.cpp)
target_link_libraries(ctpdemo ${CTP_MD_LIBRARY} ${CTP_TRADER_LIBRARY})

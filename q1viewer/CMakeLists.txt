file(GLOB_RECURSE Q1_VIEWER_SRC_FILES *.cpp *.hpp)

add_executable(q1_viewer ${Q1_VIEWER_SRC_FILES})

target_include_directories(q1_viewer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

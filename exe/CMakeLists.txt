
file(GLOB exec_files *.cpp)

foreach(cpp_file IN LISTS exec_files)
	get_filename_component(exec_file ${cpp_file} NAME_WE)
	message(STATUS "  cpp:${cpp_file}")
	message(STATUS "  exec:${exec_file}")
	add_executable(${exec_file} ${cpp_file})
	target_link_libraries(${exec_file} ${OpenCV_LIBS})
	target_link_libraries(${exec_file} ${Boost_LIBRARIES})

endforeach(cpp_file)


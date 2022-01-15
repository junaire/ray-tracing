SET(SOURCES
	main.cc
	sphere.cc
	hittable_list.cc
	camera.cc
	material.cc
)

add_executable(
	ray-tracing
	${SOURCES}
)

find_package(fmt)

target_link_libraries(
	ray-tracing
	PRIVATE
	fmt::fmt
)

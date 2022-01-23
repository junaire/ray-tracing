SET(SOURCES
	camera.cc
	hittable.cc
	main.cc
	material.cc
)

add_executable(
	ray-tracing
	${SOURCES}
)

target_link_libraries(
	ray-tracing
	PRIVATE
	fmt::fmt
)

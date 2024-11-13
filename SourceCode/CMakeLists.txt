#设置cmake最低版本要求
cmake_minimum_required(VERSION 3.15)
set(CMAKE_BUILD_TYPE Release)
#设置解决方案名称
project(TestingLibPack)

#add_compile_options(-g -fsanitize=address)
#add_link_options(-g -fsanitize=address)

#查找第三方程序包
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	message("Build with Windows OS")
elseif(CMAKE_SYSTEM_NAME MATCHES "Linux")
	message("Build with Linux OS")
	set(Qt5_DIR  ~/Qt/5.15.2/gcc_64/lib/cmake/Qt5)
endif()
find_package(Qt5    COMPONENTS Core Gui Xml Widgets REQUIRED)
find_package(HDF5   COMPONENTS CXX C REQUIRED)
find_package(Eigen3 REQUIRED)
message(EIGEN3_INCLUDE_DIR=${EIGEN3_INCLUDE_DIR})
message(HDF5_INCLUDE_DIR=${HDF5_INCLUDE_DIR})
message(HDF5_LIBRARIES=${HDF5_LIBRARIES})

#设置MSVC其它选项
if(MSVC)
	#将源字符和可执行字符集设置为utf-8
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	# cmd貌似为gbk编码，这样直接cout中文好像才不会乱码，但qDebug和QString.toStdString貌似又乱码了
	#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")
	#add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/execution-charset:gbk>")
	#add_compile_options("$<$<C_COMPILER_ID:MSVC>:/source-charset:utf-8>")
	#add_compile_options("$<$<C_COMPILER_ID:MSVC>:/execution-charset:gbk>")

	#启用OpenMP
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/openmp>")
	
endif()


#添加第三方库头文件包含目录
include_directories(
	${EIGEN3_INCLUDE_DIR}
	${HDF5_INCLUDE_DIR})

#设置可执行程序名称及其源代码文件
file(GLOB Header_Files "*.h")
file(GLOB Source_Files "*.cpp")
add_executable(TestMultiple ${Header_Files} ${Source_Files})

#设置第三方库静态链接库
set(LIBS
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
	Qt5::Xml
	${HDF5_LIBRARIES})
target_link_libraries(TestMultiple ${LIBS})

if(MSVC)

	message(MSVC_IS_TRUE)

	#文件分组
	source_group("Headers" FILES ${Header_Files})
	source_group("Sources" FILES ${Source_Files})
	
	#设置预编译头文件夹：包含msvcpch.cmake, 并调用其定义的宏 USE_MSVC_PCH
	include(${CMAKE_CURRENT_SOURCE_DIR}/msvcpch.cmake)
	USE_MSVC_PCH(TestMultiple stdafx.h stdafx.cpp)
	
	
	#设置/bigobj选项,否则会报错:error C1128
	target_compile_options(TestMultiple PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/bigobj>)

	#设置解决方案启动工程
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TestMultiple)
	# 设置Unicode
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_GLOBAL_CharacterSet "Unicode")
endif()
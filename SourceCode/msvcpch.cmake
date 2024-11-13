# msvcpch.cmake

# 参考文献：https://cloud.tencent.com/developer/article/1179123

# 声明一个宏，参数如下
# USE_MSVC_PCH      	宏名称
# PCH_TARGET        	项目名称
# PCH_HEADER_FILE   	预编译头文件名称（stdafX.h）
# PCH_SOURCE_FILE   	预编译源文件名称（stdafX.cpp）

MACRO(USE_MSVC_PCH      # 宏名称
PCH_TARGET        		# 项目名称
PCH_HEADER_FILE   		# 预编译头文件名称（stdafX.h）
PCH_SOURCE_FILE   		# 预编译源文件名称（stdafX.cpp）
)

IF(MSVC)
	# 获取预编译头文件的文件名，通常为stdafx
	GET_FILENAME_COMPONENT(PCH_NAME ${PCH_HEADER_FILE} NAME_WE)	
	# NAME_WE表示不带目录或最长扩展名的文件名
	
	# 生成预编译文件的路径
	IF(CMAKE_CONFIGURATION_TYPES)
	# 若有配置选项（Debug/Release）,路径添加以及配置选项
		SET(PCH_DIR "${CMAKE_CURRENT_BINARY_DIR}/PCH/${CMAKE_CFG_INDIR}")
	ELSE(CMAKE_CONFIGURATION_TYPES)
		SET(PCH_DIR "${CMAKE_CURRENT_BINARY_DIR}/PCH")
	ENDIF(CMAKE_CONFIGURATION_TYPES)
	
	# 创建预编译文件的路径
	FILE(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/PCH)
	
	# 设置项目属性，使用预编译头文件
	SET_TARGET_PROPERTIES(${PCH_TARGET} PROPERTIES COMPILE_FLAGS
		"/Yu${PCH_HEADER_FILE} /FI${PCH_HEADER_FILE} /Fp${PCH_DIR}/${PCH_NAME}.pch")
	# /Yu表示指示编译器在当前编译中使用现有的预编译头文件
		
	# 预编译源文件（stdafX.cpp）设置属性，创建预编译文件	
	SET_SOURCE_FILES_PROPERTIES(${PCH_SOURCE_FILE} PROPERTIES COMPILE_FLAGS
		"/Yc${PCH_HEADER_FILE}")
	# /Yc表示指示编译器创建一个预编译标头文件
	
	# 把预编译文件寄到清除列表
	SET_DIRECTORY_PROPERTIES(PROPERTIES
		ADDITIONAL_MAKE_CLEAN_FILES ${PCH_DIR}/${PCH_NAME}.pch)
		
ENDIF(MSVC)

ENDMACRO(USE_MSVC_PCH)
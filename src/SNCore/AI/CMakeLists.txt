add_library(SNAI
        Heuristics/Simple.cpp
	)
	
qt5_use_modules(SNAI Core)
target_link_libraries(SNAI SNCore)

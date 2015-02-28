


# Odd Number Analysis Program Makefile

SOURCE = tpos_main.cpp                   \
         tpos_setup.cpp                  \
		 tpos_find_numbers.cpp


OBJECT_FILES =  tpos_main.o              \
				tpos_setup.o		     \
				tpos_find_numbers.o
				
				

				
ALLEGRO_LIB = -lallegro.dll -lallegro_ttf.dll -lallegro_font.dll
#ALLEGRO_LIB = -lallegro-5.0.10-monolith-md-debug		

LINKER_FLAGS = -static-libgcc -static-libstdc++ $(ALLEGRO_LIB) 

USE_CONSOLE_STRING = -mwindows
#USE_CONSOLE_STRING = 

CPP_FLAGS = -Wall


tpos_001.exe : $(OBJECT_FILES) Makefile
	g++ -g -o tpos_001.exe $(OBJECT_FILES) $(LINKER_FLAGS) $(USE_CONSOLE_STRING)





tpos_main.o :	tpos_main.cpp                      \
				tpos_headers/find_numbers.h        \
				tpos_headers/initialisation.h      \
				tpos_headers/tpos_main_header.h                            
				g++ -c tpos_main.cpp -o $@


			 

			 
tpos_setup.o : tpos_setup.cpp                     \
               tpos_headers/initialisation.h      \
			   tpos_headers/tpos_main_header.h    \                        
			   g++ -c tpos_setup.cpp -o $@
				

tpos_find_numbers.o :  tpos_find_numbers.cpp                \
						tpos_headers/find_numbers.h         \
						tpos_headers/initialisation.h                \
						tpos_headers/tpos_main_header.h                            
						g++ -c tpos_find_numbers.cpp -o $@
	
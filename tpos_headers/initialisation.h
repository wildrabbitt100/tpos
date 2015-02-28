#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <fstream>
#include <iostream>

using namespace std;



int wait_for_keypress(void);


int make_table();

class InitialisationClass 
{

   public:
   
      
      uint32_t version;
      int init_okay;
	  
	  InitialisationClass(void) : init_okay(0), version(0)
      {
		 #ifdef USE_CONSOLE
         tpos_print("In default constructor for InitialisationClass\n");
		 #endif
      }
	  
	  InitialisationClass(Rabbit_Log& log)
      {
		  
		 /* Message for result of calling al_install_system. */
		 log.write_message_number();
		  
         if( al_install_system(ALLEGRO_VERSION_INT, atexit) == false)
         {   
		    log.write_string("Unable to install the allegro system.");
			log.end_message();
            return;
         }
		 else
		 {
		    log.write_string("Installed Allegro System.\n");
			log.end_message();
			return;
		 }
   
         al_init_font_addon();
		 
		 /* Message for call to al_init_ttf_addon(). */
		 log.write_message_number();
		 
         if(al_init_ttf_addon() == false)
	     {
	        log.write_string("Unable to install true type font addon.\n");
			log.end_message();
			return;
	     }
		 
		 
		 al_install_keyboard();
		 

		 log.write_message_number();
		 log.write_string("Finished initialising InitialisationClass.");
		 log.end_message();
		 
		 init_okay = GREEN_FLAG;
      }
	  
   private:
   
   int print_version_number(void)
   {
      ;
   }

   
   
   
   
   





};
/* END OF definition of SetUpClass. */





class DisplayClass
{

   public:
   
   int init_okay;
   int x_for_next_print;
   int font_loaded;
   
   
   DisplayClass() : display(NULL), init_okay(0), x_for_next_print(0), font(NULL), font_loaded(0), buffer(NULL)
   {
   
   }
   
   DisplayClass(int dummy, ofstream &log) : buffer(NULL) 
   {
       al_set_new_display_flags(ALLEGRO_WINDOWED);
	   
       al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
   
       display = NULL;
   
       cout << "Initialising Display Class.";
   
       if( (display = al_create_display(1024, 768)) == NULL )
       {
          return;
       }
	   else
	   {
	      init_okay = 1;
	   }
	   
       al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ANY_32_WITH_ALPHA);
	   
	   
	   
	   font = al_load_ttf_font("SIRCLIVE.ttf", 16, 0);
	   if(font == NULL)
	   {
	      log.write("Unable to load font SIRCLIVE.ttf\n", 34);
		  font_loaded = 0;
	   }
	   else
	   {
	      font_loaded = 1;
	   }
	  
	   buffer = NULL;
	   buffer = al_create_bitmap(1024, 768);
	   if(buffer == NULL)
	   {
	      init_okay = 0;
		  return;
	   }
	   else
	   {
	       al_set_target_bitmap(buffer);
	       al_clear_to_color(al_map_rgba(0, 0, 0, 255));
	   }
	 
	 
   }
   
   
   void clear(void)
   {
      al_set_target_backbuffer(display);
      al_clear_to_color(al_map_rgba(0, 0, 0, 255));
      al_flip_display();
   }
   
   ALLEGRO_DISPLAY *get_display(void)
   {
      return display;
   }
   
   
   private:
   
   ALLEGRO_DISPLAY *display;
   ALLEGRO_BITMAP *buffer;
   
   ALLEGRO_FONT *font;
   
   
   
};




class ConfigManagerClass
{
   
   ALLEGRO_CONFIG *cfg;

   
   public:

   ConfigManagerClass() : cfg(NULL)
   {
      

   }
   
   int load_config_file(const char *filename)
   {
      if(cfg != NULL)
	  {
	     return 2;
	  }
	  else
	  {
         cfg = al_load_config_file(filename);
		 
		 if( cfg == NULL )
		 {
		    return 1;
		 }
         else 
		 {
		    return 0;
		 }
      }
   }
   
   unsigned int get_integer(const char *key, int *return_state)
   {
      const char *string = NULL;
	  
      string = al_get_config_value( cfg, "", "number_of_distinct_factors");
    
	  if(string == NULL)
	  {
         *return_state = 1;
         return 0;
      }
      else
	  {
	     *return_state = 0;
	  }
      
   }
   
   


};
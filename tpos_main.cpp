#include <allegro5/allegro5.h>
#include <vector>
#include <fstream>

#include "stdio.h"

#include "tpos_headers/tpos_main_header.h"

#include "tpos_headers/log_file_manager.h"     /* tpos_main_header.h */

#include "tpos_headers/initialisation.h"                /* log_file_manager.h, tpos_main_header.h */

#include "tpos_headers/find_numbers.h"



using namespace std;











int main(int argc, char *argv[])
{
   InitialisationClass init_class = InitialisationClass();
   DisplayClass display_class = DisplayClass();
   int log_open = 0;  
   ALLEGRO_CONFIG *cfg = NULL;
   ConfigManagerClass config_manager;
   ALLEGRO_EVENT_QUEUE *queue = NULL;
   ALLEGRO_EVENT event;
   Rabbit_Log log = Rabbit_Log(0);
   int quit = 0;
   int i = 0;
   int job_done = 0;
   
   
   #ifdef USE_CONSOLE
   if(log.init_okay() == GREEN_FLAG)
   {
	  tpos_print("Opened log.\n");
   }
   else
   {
	  tpos_print("Couldn't open log.\n");
   }
   #endif
   
   
   
   init_class = InitialisationClass(log);
   if(init_class.init_okay == 0)
   {
	   /* Either the call to al_install_system() or al_init_ttf_addon() failed. */
	   log.close();
	   wait_for_keypress();
       return 1;
   }
   
   
   
   /* The allegro system is installed, true_type_font_addon installed... */
   
   log.write_message_number();
   log.write("Initialising Display. ");
   log.end_message();

   
   display_class = DisplayClass(0, log);
   
   
   /* Message for whether or not initialising the display class went okay. */
   
   log.write_message_number();
   if(display_class.init_okay != 1)
   {
      log.write_message("Couldn't create the display. Aborting.\n");
	  log.end_message();
	  log.close();
	  wait_for_keypress();
	  return 0;
   }
   else
   {
	  log.write_message("Successfully created the Display.\n");
	  log.end_message();
   }
  
   
   
   display_class.clear();
   
   i = config_manager.load_config_file("configuration/tpos_configuration_file.cfg");
   
   if( i == 1 ) /* Loading failed. */
   {
      if(log_open)
	  {
	     log.write("Unable to load configuration file.\n", 38);
		 log.close();
	  }
	  
	  return 1;
   }
   else
   {
      log.write("Loaded the configuration file.\n", 32); 
	  #ifdef USE_CONSOLE
      tpos_print("Loaded the configuration file.\n");
	  #endif
   }
   
   
   queue = al_create_event_queue();
   if(queue == NULL)
   {
      log.write("Failed to create the event queue in main. Aborting.\n", 43);
	  return 0;
   }
   
   
   al_register_event_source(queue, al_get_keyboard_event_source());
   al_register_event_source(queue, al_get_display_event_source(display_class.get_display()));
   
   
   

   while(quit == 0)
   {
      //cout << "in loop.\n";
      al_wait_for_event(queue, &event);
	  //cout << "got event\n";
	  
	  
	  switch(event.type)
	  {
	     case ALLEGRO_EVENT_DISPLAY_CLOSE:
		     quit = 1;
			 break;
		 case ALLEGRO_EVENT_KEY_DOWN:
		     break;
	  }
	  
	  
	  if(job_done == 0)
	  {
	     cout << "Calling make_table.\n";
	     if( find_numbers(display_class, log, config_manager) != MAKE_TABLE_SUCCESS)
		 {
		 
		    ;
		 }
		 else
		 {
		    job_done = 1;
		 }
	  
	  }
	  
	  
   }
   
   
   
   
   
   
   
   
   return 0;
}











int wait_for_keypress()
{
   ALLEGRO_EVENT_QUEUE *queue = NULL;
   ALLEGRO_EVENT event; 

   
   queue = al_create_event_queue();
   if(queue == NULL)
   {
      return 0;
   }
   
   al_register_event_source(queue, al_get_keyboard_event_source());
   
   do
   {
      al_wait_for_event(queue, &event);
      
   } while( event.type != ALLEGRO_EVENT_KEY_DOWN );
   
   
   al_destroy_event_queue(queue);
   
   return 1;
}


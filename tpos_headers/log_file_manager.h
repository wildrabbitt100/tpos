/* tpos */

#include <iostream>
#include <fstream>
#include <cstring>




using namespace std;





class Rabbit_Log {

    public:
	
	  /* Disable copy constructor and assignment operator. */
      Rabbit_Log(const Rabbit_Log&);
	  Rabbit_Log& operator=(const Rabbit_Log&);
   
      ofstream log;
      int init_okay_flag;
      int message_number;
   
   
      /* Rabbit_Log : Default constructor. */
   
      Rabbit_Log() : init_okay_flag(RED_FLAG) { }
      
	  /* Rabbit_Log : main constructor. */
     
      Rabbit_Log(int dummy) : init_okay_flag(GREEN_FLAG) 
	  { 
	     /* set message_number to 0 ready for the first message which will
		    be message number 0. */
	     
		 message_number = 0;
		 
	     log.open("tpos_001_log.txt", ios_base::out);
		 if(log.fail())
		 {
		    #ifdef USE_CONSOLE
		       tpos_print("log.fail() return true. Couldn't open file.\n");
		    #endif
		    init_okay_flag = RED_FLAG;
		    return;
		 }
		
		 init_okay_flag = GREEN_FLAG;
		 
		 write_message_number();
		
		 
		 
		 if( write_string("Log file opened") != 0)
		 {
		    init_okay_flag = RED_FLAG;
		    return;
		 }
		 
		 end_message();
		
		 
	   
	 }
	 
	 
	 /* init_okay() : returns the flag which indicates whether or not any constructor called
	                  failed to finish correctly. */
	 
	 int init_okay(void)
	 {
	    return init_okay_flag;
	 }
	 
	 
	 /* write_message_number() : */
	 
	 void write_message_number()
	 {
	    int i;                  /* integer for clearing the string. */
	    char string[20];
		int num_digits = 1;
		int power_of_ten = 10;
		int next_digit = 0;
		
	
		if(init_okay_flag == RED_FLAG || message_number > 9999)
		{
		   return;		
		}
		
		#ifdef USE_CONSOLE
		    tpos_print("   In write_message_number.\n");
		#endif
		
		for(i = 0; i < 20; ++i)
		{
	       string[i] = 0;	
		}
		
		sprintf(string, "%4d", message_number);
		 
		
		log.write("MESSAGE : ", 10);
		log.write(string, 4);
		log.write("   : ", 7);
		
		
		++message_number;
	 }
	 
	 
	 
	 
	 int write_string(const char *string)
	 {
	     int length_of_string = strlen(string);
		 
		 if(string == NULL || init_okay_flag == RED_FLAG)
		 {
			 return 1;
		 }
		
		 log.write(string, length_of_string);
		 
	     if(log.bad())
		 {
			#ifdef USE_CONSOLE
			tpos_print("log.badbit set to 1.\n");
			#endif
		    return 2;
		 }
		
		 return 0;
	 }
	 
	 
	 void end_message()
	 {
		log.write("\n", 1);
	 }
	 
	 void close_log(void)
	 {
		log.close();		
	 }
	 
     private:
	 
	 
	 
	 
   
};




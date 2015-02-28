

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
   
   
      /* Default constructor. */
   
      Rabbit_Log() : init_okay_flag(RED_FLAG) { }
   
     
     Rabbit_Log(int dummy) : init_okay_flag(GREEN_FLAG) 
	 { 
	 
	    log.open("tpos_001_log.txt", ios_base::out);
		if(log.fail())
		{
		   init_okay_flag = RED_FLAG;
		   return;
		}
		
		
		write_message_number();
		if( write_string(" log file opened") != 0)
		{
		   init_okay_flag = RED_FLAG;
		   return;
		}
		
		init_okay_flag = GREEN_FLAG;
	   
	 }
	 
	 
	 int init_okay(void)
	 {
	    return init_okay_flag;
	 }
	 
	 void write_message_number()
	 {
	    int i;                  /* integer for clearing the string. */
	    char string[20];
		int num_digits = 1;
		int power_of_ten = 10;
		int next_digit = 0;
		
		if(init_okay_flag == RED_FLAG)
		{
		   return;		
		}
		
		
		for(i = 0; i < 20; ++i)
		{
	       string[i] = 0;	
		}
		
		i = 0;
		
		
		while( (message_number % power_of_ten) != message_number )
		{
		   ++num_digits;
		   power_of_ten *= 10;
		   
           if(num_digits > 7)
           {
              /* need error message */
           }		   
		} 

        /* e.g  452 :    452 % 10    =   2 != 452 		
		                 452 % 100   =  52 != 452
						 452 % 1000  = 452 
						 
		*/
		
		
		while( (power_of_ten /= 10) != 0 )
		{
		   next_digit = message_number / power_of_ten;
		   string[i] = next_digit;
		   ++i;
		}
		   
		string[i] = '\0';
		
		log.write("MESSAGE ", 8);
	    log.write(string, i);
		log.write("   :   ", 7);
	 }
	 
	 
	 
	 
	 int write_string(const char *string)
	 {
	     int length_of_string = strlen(string);
		 
		 if(init_okay_flag == RED_FLAG)
		 {
			 return 1;
		 }
		 log.write(string, length_of_string);
	     if(log.failbit || log.badbit)
		 {
		    return 2;
		 }
		 
		 return 0;
	 }
	 
	 
	 void end_message()
	 {
		log.write("\n\n", 2);
	 }
	 
	 void close_log(void)
	 {
		log.close();		
	 }
	 
     private:
	 
	 
	 
	 
   
};




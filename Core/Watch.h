////////////////////////////////////////
// Watch.h
////////////////////////////////////////

#ifndef CSE168_WATCH_H
#define CSE168_WATCH_H

////////////////////////////////////////////////////////////////////////////////

#include <ctime>
#include <iostream>

class Watch
{
    public:
        Watch()
	{
	    IsStart = false;
	}
        ~Watch(){}


	static void StartTimer()
	{
	    StartTime = time(NULL);
	    std::cout << "Start Timer" << std::endl;
	}

	static void EndTimer()
	{
	    std::cout << "Time elapsed: " << difftime(time(NULL), StartTime) << " sec" << std::endl;
	}

    private:
	static time_t StartTime;
	bool IsStart;

};

time_t Watch::StartTime = time(NULL);

#endif

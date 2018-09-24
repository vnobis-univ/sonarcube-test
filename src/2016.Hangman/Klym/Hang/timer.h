#ifndef TIMER_H
#define TIMER_H

	struct timer
	{
		double startTime;
		double currentTime;

		timer( double s )
		{
			startTime = s;
		}
	};

#endif
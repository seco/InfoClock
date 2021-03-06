/*
 * ledClock.hpp
 *
 *  Created on: 01.01.2017
 *      Author: Bartosz Bielawski
 */

#ifndef DISPLAYTASK_HPP_
#define DISPLAYTASK_HPP_

#include "task.hpp"
#include "LEDMatrixDriver.h"
#include "SDD.hpp"

using MessageProvider = std::function<String()>;

struct DisplayState
{
		MessageProvider fun;
		uint16_t	period;
		uint16_t 	cycles;
		bool		scrolling;		//refresh till it's done
};


class DisplayTask: public Tasks::TaskCRTP<DisplayTask>
{
	public:
		DisplayTask(uint32_t deviceCount);

		void init();
		virtual void reset();

		void pushMessage(const String& m, uint16_t sleep, bool scrolling = false);

		void nextMessage();
		void scrollMessage();
		void refreshMessage();

	private:
		void nextDisplay();

		int index = 0;
		LEDMatrixDriver ledMatrixDriver;
		SDD scroll;
		DisplayState ds;

		std::vector<DisplayState> priorityMessages;
		bool		priorityMessagePlayed = false;
};


#endif /* DISPLAYTASK_HPP_ */

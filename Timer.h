#pragma once

#include <functional>
#include "virtools/CKAll.h"

class Timer {
public:
	Timer(CKDWORD delay, std::function<void()> callback, CKDWORD tick, float time);
	Timer(CKDWORD delay, std::function<bool()> callback, CKDWORD tick, float time);
	Timer(float delay, std::function<void()> callback, CKDWORD tick, float time);
	Timer(float delay, std::function<bool()> callback, CKDWORD tick, float time);

	bool Process(CKDWORD tick, float time);

private:
	struct {
		std::function<void()> once;
		std::function<bool()> loop;
	} m_callback;
	enum {
		TICK, TIME, ONCE, LOOP
	} m_delaytype, m_callbacktype;
	union {
		CKDWORD tick;
		float time;
	} m_delay, m_start;
};

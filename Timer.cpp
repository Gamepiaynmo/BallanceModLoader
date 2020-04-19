#include "Timer.h"

Timer::Timer(CKDWORD delay, std::function<void()> callback, CKDWORD tick, float time) {
	m_callbacktype = ONCE;
	m_callback.once = callback;
	m_delaytype = TICK;
	m_delay.tick = delay;
	m_start.tick = tick;
}

Timer::Timer(CKDWORD delay, std::function<bool()> callback, CKDWORD tick, float time) {
	m_callbacktype = LOOP;
	m_callback.loop = callback;
	m_delaytype = TICK;
	m_delay.tick = delay;
	m_start.tick = tick;
}

Timer::Timer(float delay, std::function<void()> callback, CKDWORD tick, float time) {
	m_callbacktype = ONCE;
	m_callback.once = callback;
	m_delaytype = TIME;
	m_delay.time = delay;
	m_start.time = time;
}

Timer::Timer(float delay, std::function<bool()> callback, CKDWORD tick, float time) {
	m_callbacktype = LOOP;
	m_callback.loop = callback;
	m_delaytype = TIME;
	m_delay.time = delay;
	m_start.time = time;
}

bool Timer::Process(CKDWORD tick, float time) {
	if (m_delaytype == TICK) {
		if (m_start.tick + m_delay.tick <= tick) {
			if (m_callbacktype == ONCE) {
				m_callback.once();
				return false;
			}
			else {
				m_start.tick = tick;
				return m_callback.loop();
			}
		}
	}
	else {
		if (m_start.time + m_delay.time <= time) {
			if (m_callbacktype == ONCE) {
				m_callback.once();
				return false;
			}
			else {
				m_start.time = time;
				return m_callback.loop();
			}
		}
	}
	return true;
}
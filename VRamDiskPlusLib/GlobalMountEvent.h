#pragma once

#include <string>

class GlobalMountEvent
{
public:
	GlobalMountEvent(wchar_t mountPointLetter);
	~GlobalMountEvent();

	void SignalMounted();
	void SignalUnmounted();

	void WaitForMounted();

	static std::wstring GetEventName(wchar_t driveLetter);

private:
	void* m_event;
};


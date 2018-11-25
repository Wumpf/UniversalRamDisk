#include "GlobalMountEvent.h"
#include "Log.h"
#include <Windows.h>

GlobalMountEvent::GlobalMountEvent(wchar_t mountPointName)
{
	auto eventName = GetEventName(mountPointName);
	m_event = CreateEvent(nullptr, TRUE, FALSE, eventName.c_str());
	if (!m_event)
	{
		if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
			m_event = OpenEvent(EVENT_ALL_ACCESS, TRUE, eventName.c_str());
			if (!m_event)
				Log("OpenEvent failed: ", GetLastError());
		}
		else
			Log("CreateEvent failed: ", GetLastError());
	}
}

GlobalMountEvent::~GlobalMountEvent()
{
	if (m_event)
		CloseHandle(m_event);
}

void GlobalMountEvent::SignalMounted()
{
	if (m_event)
		SetEvent(m_event);
}

void GlobalMountEvent::SignalUnmounted()
{
	if (m_event)
		ResetEvent(m_event);
}

void GlobalMountEvent::WaitForMounted()
{
	if (m_event)
		WaitForSingleObject(m_event, INFINITE);
}

std::wstring GlobalMountEvent::GetEventName(wchar_t driveLetter)
{
	driveLetter = towlower(driveLetter);
	return std::wstring(L"Global\\UniversalRamDisk_Mount_") + driveLetter;
}

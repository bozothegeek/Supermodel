
#ifndef INCLUDED_EVDEVINPUTSYSTEM_H
#define INCLUDED_EVDEVINPUTSYSTEM_H

#include "SDLInputSystem.h"
#include <libudev.h>

#define EVDEV_MAXPLAYERS 8
#define EVDEV_MAXBUTTONS 16

class CEvdevInputSystem : public CSDLInputSystem
{
  public:
        /*
         * Constructs an evdev input system.
         */
        CEvdevInputSystem(const Util::Config::Node& config);

        ~CEvdevInputSystem();

  	int GetNumMice();
	const MouseDetails *GetMouseDetails(int mseNum);

	bool Poll();

	void SetMouseVisibility(bool visible);

  protected:

  	bool InitializeSystem();

  	int GetMouseAxisValue(int mseNum, int axisNum);

	int GetMouseWheelDir(int mseNum);

	bool IsMouseButPressed(int mseNum, int butNum);

  	CInputSource *CreateAnyMouseSource(EMousePart msePart);

  private:
    struct udev *m_udev;
    int m_devices[EVDEV_MAXPLAYERS];
    int m_devices_btn[EVDEV_MAXPLAYERS][EVDEV_MAXBUTTONS];
    int m_devices_axes[EVDEV_MAXPLAYERS][2];
    int m_devices_axes_minmax[EVDEV_MAXPLAYERS][2][2];
    int m_ndevices;
    std::vector<MouseDetails> m_mseDetails;

    void handle_event(unsigned int idx, struct input_event& event);
};

#endif  // INCLUDED_EVDEVINPUTSYSTEM_H
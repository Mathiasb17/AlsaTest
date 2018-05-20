#ifndef LINUXSOUNDINTERFACE_H_FUAWGWKS
#define LINUXSOUNDINTERFACE_H_FUAWGWKS

#include <alsa/asoundlib.h>
#include <string>

class LinuxSoundInterface
{
public:
	LinuxSoundInterface();
	LinuxSoundInterface(const std::string p_sInterfaceName, const std::string p_sMixerName);
	~LinuxSoundInterface();

	void _init();
	void _end();

	long getVolumeMin() const;
	long getVolumeMax() const;
	long getVolumeCurrent() const;

	void volumeSetValue(std::uint8_t p_volume);
	void toggleSound(bool toggle);

private:
	long m_volumeMin;
	long m_volumeMax;

	long m_volumeCurrent;

	std::string m_interfaceName;
	std::string m_mixerName;

    snd_mixer_t *m_handle;
    snd_mixer_selem_id_t *m_sid;
	snd_mixer_elem_t* m_elem;
};

#endif /* end of include guard: LINUXSOUNDINTERFACE_H_FUAWGWKS */

#include	"PortAudioIO.hh"
#include	<iostream>

int	main(void)
{
  PortAudioIO	audiomanager;

  if (!audiomanager.init())
	  std::cerr << "error initializing " << std::endl;
  audiomanager.startRecording();
  audiomanager.playSound();
  audiomanager.cleanup();
}

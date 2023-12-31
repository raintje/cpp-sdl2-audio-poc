#include "main.h"

/**
 * Callback function to be passed to SDL Audiostream.
 *
 * @param userdata Honestly no clue what this is.
 * @param stream The main audiostream to play Audio on.
 * @param len The length of the audio file you want to play.
 */
void AudioCallback(void *userdata, Uint8 *stream, int len) {
  if (audio_len <= 0)
    return;

  len = len > audio_len ? (int) audio_len : len;
  SDL_memcpy(stream, audio_pos, len); // sdl magic, copy values to stream
  SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME / 2); // play audio at 50 to not rupture your eardrums

  audio_pos += len;
  audio_len -= len;
};

int main(int argc, char *argv[]) {
  // init sdl audio
  if (SDL_Init(SDL_INIT_AUDIO < 0)) {
    std::cout << "Error initializing SDL Audio." << std::endl;
    return 1;
  }

  // local variables
  static Uint32 wav_length;
  static Uint8 *wav_buffer;
  static SDL_AudioSpec wav_spec;

  bool running = true;
  std::string wavPath;

  while (running) {

    std::cout << "Type the name of the sound you want to hear: ";
    std::cin >> wavPath;

    if (wavPath == "guitar" || wavPath == "frog" || wavPath == "boot") {
      running = false;
    } else
      wavPath = "windowserror";

  }

  // load .wav file
  if (SDL_LoadWAV(("../audio/" + wavPath + ".wav").c_str(), &wav_spec, &wav_buffer, &wav_length) == nullptr) {
    std::cout << "Failed to load WAV file: " << wavPath << std::endl;
    return 1;
  }

  // set callback
  wav_spec.callback = AudioCallback;
  wav_spec.userdata = nullptr;

  // match globals to static variables
  audio_pos = wav_buffer;
  audio_len = wav_length;

  // open audio device
  if (SDL_OpenAudio(&wav_spec, nullptr) < 0) {
    fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
    return 1;
  }

  // start playing
  SDL_PauseAudio(0);
  if (wavPath == "windowserror")
    std::cout << "Invalid audio name." << std::endl;
  else
    std::cout << "Now playing: " << wavPath << std::endl;

  // wait until the entire file is finished
  while (audio_len > 0) {
    SDL_Delay(100);
  }

  // cleanup
  SDL_CloseAudio();
  SDL_FreeWAV(wav_buffer);
}

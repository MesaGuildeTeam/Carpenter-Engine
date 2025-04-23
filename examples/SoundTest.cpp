/**
 * @file SoundTest.cpp
 * @brief Basic sound test scene for the game engine
 * @author: Roberto Selles
 */

#include <Game.hpp>
#include <UI/UIButton.hpp>
#include <Audio/Music.hpp>
#include <Audio/Sound.hpp>

#include <iostream>

using namespace Engine;

// Song

Audio::Music sampleSong("Assets/demo.wav");
Audio::Sound sampleSound("Assets/drop.mp3");

void MusicToggle() {
  Audio::SoundState state = sampleSong.playing();
  std::cout << state << "\n"; // Used to debug the state of the song
  if (state == Audio::SoundState::Playing) {
    sampleSong.Pause();
  } else {
    sampleSong.Play();
  }
}

void PlaySound() {
  sampleSound.Play();
}

class TestContainer : UI::UIElement {
  private:
  UI::UIElement MusicTestContainer{UI::UIElement("MusicSection")};
  UI::UIElement SoundsTestContainer{UI::UIElement("SoundSection")};
  UI::UIButton MusicToggleBtn{UI::UIButton("MusicToggle", "Play/Pause Music", MusicToggle)};
  UI::UIButton SkipTrack{UI::UIButton("SkipTrack", "Skip Track", Engine::Audio::SkipTrack)};
  UI::UIButton SoundPulse{UI::UIButton("SoundPulse", "Play Sound", PlaySound)};

  public:
  TestContainer() : UI::UIElement("TestContainer") {
    Engine::UI::UIElement::Init();

    std::cout << "TEST: Creating Music Container\n";
    AddChild(&MusicTestContainer);
    MusicTestContainer.SetDimensions({300, 300});

    MusicTestContainer.AddChild(&MusicToggleBtn);
    MusicTestContainer.AddChild(&SkipTrack);

    MusicToggleBtn.SetAnchor("topright");

    std::cout << "TEST: Creating Sound Container\n";
    AddChild(&SoundsTestContainer);
    SoundsTestContainer.SetDimensions({300, 300});
    SoundsTestContainer.SetAnchor("topright");
    SoundsTestContainer.AddChild(&SoundPulse);

    sampleSong.setLoop(true);
  };

};

class TestScene : public Scene {
  public:
  TestScene() : Scene("TestScene") {
    std::cout << "TEST: Creating Sound Test Scene\n";
    AddChild((Node*) new TestContainer());
    std::cout << "TEST: Container Created Successfully\n";
  }
};

Engine::Game& game{Engine::Game::getInstance((Engine::Scene*) new TestScene())};
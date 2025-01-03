#include <Game.hpp>
#include <UI/UIButton.hpp>
#include <Audio/Music.hpp>

#include <iostream>

// Song

Engine::Audio::Music sampleSong("Assets/demo.wav");

void MusicToggle() {
  if (sampleSong.playing() == Engine::Audio::SoundState::Playing) {
    return;
  } else {
    sampleSong.Play();
  }
}

void PlaySound() {

}

class TestContainer: public Engine::UI::UIElement {
  public:
  TestContainer() : Engine::UI::UIElement("TestContainer") {};

  void Init() override {
    Engine::UI::UIElement::Init();

    std::cout << "TEST: Creating Music Container\n";
    size_t MusicTestContainer = AddChild((Engine::Node*) new Engine::UI::UIElement("MusicSection"));
    ((Engine::UI::UIElement*)GetChild(MusicTestContainer))->SetDimensions({300, 300});

    std::cout << "TEST: Adding a Button\n";
    ((Engine::UI::UIElement*)GetChild(MusicTestContainer))->AddChild((Engine::Node*) new Engine::UI::UIButton("MusicToggle", "Play/Pause Music", MusicToggle));

    std::cout << "TEST: Creating Sound Container\n";
    size_t SoundsTestContainer = AddChild((Engine::Node*) new Engine::UI::UIElement("SoundSection"));
    ((Engine::UI::UIElement*)GetChild(SoundsTestContainer))->SetDimensions({300, 300});
    
    ((Engine::UI::UIElement*)GetChild(SoundsTestContainer))->SetAnchor("topright");
    ((Engine::UI::UIElement*)GetChild(SoundsTestContainer))->AddChild((Engine::Node*) new Engine::UI::UIButton("SoundPulse", "Play Sound", PlaySound));

    sampleSong.Play();
  };
};

class TestScene : public Engine::Scene {
  public:
  TestScene() : Engine::Scene("TestScene") {
    std::cout << "TEST: Creating Sound Test Scene\n";
    AddChild((Engine::Node*) new TestContainer());
    std::cout << "TEST: Container Created Successfully\n";
  };
};

Engine::Game& instance{Engine::Game::getInstance((Engine::Scene*) new TestScene())};

extern "C" {
  void CallDraw() {instance.DrawScene();};
  void CallUpdate() {instance.UpdateScene(0.1f);};
}
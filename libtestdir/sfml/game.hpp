#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game
{
  public:
    // = delete:刪除C++類默認的拷貝構造函數以及拷貝賦值運算符
    Game(const Game&) = delete; 
    Game& operator=(const Game&) = delete;
    Game();

    void run();
    
  private: 
    // 動態時間步長
    void run1();
    // 固定時間步長
    void run2(int frame_per_seconds);
    // 最小時間步長
    void run3(int minimum_frame_per_seconds);
    // 這裡處理用戶的輸入
    void processEvents();
    // 更新遊戲的狀態，計算出下一步
    void update(sf::Time deltaTime);
    // 繪製遊戲的畫面(渲染)
    void render();

    sf::RenderWindow _window;
	  sf::CircleShape _player;
};

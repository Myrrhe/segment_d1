#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include "StaticObject.hpp"
#include "Types.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <array>
#include <memory>
#include <stack>
#include <string>
#include <vector>

namespace segment_d1
{

class WindowManager final : public StaticObject
{
public:
    enum class IdView : uint64_t
    {
        MAIN,
        UI,
        SHAKE,
        WHOLE
    };

    static void getMonitorSize();

    static void create();
    static void initialize();
    static void terminate();

    static void pushStateView(const IdView idView);
    static void popStateView();
    static void setViewTarget(sf::RenderTarget &renderTarget);

    static void setUiView(const float32_t x, const float32_t y,
                          const float32_t widthUi, const float32_t heightUi);

    static void setOffsetX(const float32_t newOffsetX);
    static void setOffsetY(const float32_t newOffsetY);

    static void manageEvent();

    static bool isOpen();
    static bool pollEvent(sf::Event &event);
    static bool hasFocus();
    static void close();
    static void clear(const sf::Color &color);
    static void clear();
    static void draw(const sf::Vertex *const vertices,
                     const std::size_t vertexCount,
                     const sf::PrimitiveType type,
                     const sf::RenderStates &states);
    static void draw(const sf::Drawable &drawable,
                     const sf::RenderStates &states);
    static void display();
    static sf::Vector2<int32_t> getMousePosition();
    static sf::Vector2<float32_t>
    mapPixelToCoords(const sf::Vector2<int32_t> &point);

    [[nodiscard]] static sf::RenderWindow *getRenderWindow();

    [[nodiscard]] static bool isTextEntered();
    [[nodiscard]] static char32_t getCharEntered();

    [[nodiscard]] static bool isKeyPressed();
    [[nodiscard]] static sf::Keyboard::Key getKeyPressed();

    [[nodiscard]] static bool isAltEntered();
    [[nodiscard]] static bool isControlEntered();
    [[nodiscard]] static bool isShiftEntered();
    [[nodiscard]] static bool isSystemEntered();

    static constexpr uint64_t Width = 600;
    static constexpr uint64_t Height = 600;

    static constexpr bool Fullscreen = false;

    static constexpr uint32_t Fps = 60;

    static constexpr uint32_t ModeBitsPerPixel = 32;

private:
    static std::unique_ptr<sf::RenderWindow> renderWindow;
    static std::unique_ptr<sf::Texture> textureIcon;

    static std::array<sf::View, 4> views;
    static std::stack<IdView> stateView;

    static float32_t mainScale;

    static float32_t uiX;
    static float32_t uiY;
    static float32_t uiWidth;
    static float32_t uiHeight;

    static float32_t offsetX;
    static float32_t offsetY;

    static sf::Vector2<uint64_t> monitorSize;

    static bool textEntered;
    static char32_t charEntered;

    static bool keyPressed;
    static sf::Keyboard::Key codeKeyPressed;

    static bool altEntered;
    static bool controlEntered;
    static bool shiftEntered;
    static bool systemEntered;
};

} // namespace segment_d1

#endif // WINDOWMANAGER_HPP

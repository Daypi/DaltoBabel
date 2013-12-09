//
// MySFML.hpp for rtype in /home/lequeu_m/
//
// Made by martin lequeux-gruninger
// Login   <lequeu_m@epitech.net>
//
// Started on  Mon Nov 11 09:14:07 2013 martin lequeux-gruninger
// Last update Wed Nov 20 03:40:47 2013 martin lequeux-gruninger
//

#pragma	once
#include	<SFML/System.hpp>
#include	<SFML/Graphics.hpp>
#include	<TGUI/TGUI.hpp>

#ifdef _WIN32
	typedef unsigned long int	MYUINT32;
#else
	typedef uint32_t		MYUINT32;
#endif

namespace My
{
  class Keyboard;
}

namespace My
{
  enum Style
    {
      None       = 0,
      Titlebar   = 1 << 0,
      Resize     = 1 << 1,
      Close      = 1 << 2,
      Fullscreen = 1 << 3
    };

  //CLOCK
  class Clock : public ::sf::Clock
  {
  public:
    Clock() {};
    virtual ~Clock() {};

    double	getElapsedTime()
    {
      return (::sf::Clock::getElapsedTime().asSeconds());
    }

    double	restart()
    {
      return (::sf::Clock::restart().asSeconds());
    }
  };


  //KEYBOARD
  class Keyboard : public ::sf::Keyboard
  {
  public :
    enum Key
    {
      Unknown = 0,
      A,
      B,
      C,
      D,
      E,
      F,
      G,
      H,
      I,
      J,
      K,
      L,
      M,
      N,
      O,
      P,
      Q,
      R,
      S,
      T,
      U,
      V,
      W,
      X,
      Y,
      Z,
      Num0,
      Num1,
      Num2,
      Num4,
      Num5,
      Num6,
      Num7,
      Num8,
      Num9,
      Escape,
      LControl,
      LShift,
      LAlt,
      LSystem,
      RControl,
      RShift,
      RAlt,
      RSystem,
      Menu,
      LBracket,
      RBracket,
      SemiColon,
      Comma,
      Period,
      Quote,
      Slash,
      BackSlash,
      Tilde,
      Equal,
      Dash,
      Space,
      Return,
      BackSpace,
      Tab,
      PageUp,
      PageDown,
      End,
      Home,
      Insert,
      Delete,
      Add,
      Subtract,
      Multiply,
      Divide,
      Left,
      Right,
      Up,
      Down,
      Numpad0,
      Numpad1,
      Numpad2,
      Numpad3,
      Numpad4,
      Numpad5,
      Numpad6,
      Numpad7,
      Numpad8,
      Numpad9,
      F1,
      F2,
      F3,
      F4,
      F5,
      F6,
      F7,
      F8,
      F9,
      F10,
      F11,
      F12,
      F13,
      F14,
      F15,
      Pause,
      KeyCount
    };

    static bool isKeyPressed(Key key)
    {
      return (::sf::Keyboard::isKeyPressed((::sf::Keyboard::Key)key));
    }
  };


  //MOUSE
  class Mouse :  public ::sf::Mouse
  {
  public :
    enum Button
    {
      Left,
      Right,
      Middle,
      XButton1,
      XButton2,
      ButtonCount
    };
  };

  //JOYSTICK
  class Joystick : public ::sf::Joystick
  {
  public :
    enum
      {
        Count       = 8,
        ButtonCount = 32,
        AxisCount   = 8
      };
    enum Axis
      {
        X,
        Y,
        Z,
        R,
        U,
        V,
        PovX,
        PovY
      };
  };

  //EVENT
  struct Event
  {
    ////////////////////////////////////////////////////////////
    /// \brief Size events parameters (Resized)
    ///
    ////////////////////////////////////////////////////////////
    struct SizeEvent
    {
        unsigned int width;  ///< New width, in pixels
        unsigned int height; ///< New height, in pixels
    };

    ////////////////////////////////////////////////////////////
    /// \brief Keyboard event parameters (KeyPressed, KeyReleased)
    ///
    ////////////////////////////////////////////////////////////
    struct KeyEvent
    {
        Keyboard::Key code;    ///< Code of the key that has been pressed
        bool          alt;     ///< Is the Alt key pressed?
        bool          control; ///< Is the Control key pressed?
        bool          shift;   ///< Is the Shift key pressed?
        bool          system;  ///< Is the System key pressed?
    };

    ////////////////////////////////////////////////////////////
    /// \brief Text event parameters (TextEntered)
    ///
    ////////////////////////////////////////////////////////////
    struct TextEvent
    {
        MYUINT32 unicode; ///< UTF-32 unicode value of the character
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse move event parameters (MouseMoved)
    ///
    ////////////////////////////////////////////////////////////
    struct MouseMoveEvent
    {
        int x; ///< X position of the mouse pointer, relative to the left of the owner window
        int y; ///< Y position of the mouse pointer, relative to the top of the owner window
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse buttons events parameters
    ///        (MouseButtonPressed, MouseButtonReleased)
    ///
    ////////////////////////////////////////////////////////////
    struct MouseButtonEvent
    {
        Mouse::Button button; ///< Code of the button that has been pressed
        int           x;      ///< X position of the mouse pointer, relative to the left of the owner window
        int           y;      ///< Y position of the mouse pointer, relative to the top of the owner window
    };

    ////////////////////////////////////////////////////////////
    /// \brief Mouse wheel events parameters (MouseWheelMoved)
    ///
    ////////////////////////////////////////////////////////////
    struct MouseWheelEvent
    {
        int delta; ///< Number of ticks the wheel has moved (positive is up, negative is down)
        int x;     ///< X position of the mouse pointer, relative to the left of the owner window
        int y;     ///< Y position of the mouse pointer, relative to the top of the owner window
    };

    ////////////////////////////////////////////////////////////
    /// \brief Joystick connection events parameters
    ///        (JoystickConnected, JoystickDisconnected)
    ///
    ////////////////////////////////////////////////////////////
    struct JoystickConnectEvent
    {
        unsigned int joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
    };

    ////////////////////////////////////////////////////////////
    /// \brief Joystick axis move event parameters (JoystickMoved)
    ///
    ////////////////////////////////////////////////////////////
    struct JoystickMoveEvent
    {
        unsigned int   joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
        Joystick::Axis axis;       ///< Axis on which the joystick moved
        float          position;   ///< New position on the axis (in range [-100 .. 100])
    };

    ////////////////////////////////////////////////////////////
    /// \brief Joystick buttons events parameters
    ///        (JoystickButtonPressed, JoystickButtonReleased)
    ///
    ////////////////////////////////////////////////////////////
    struct JoystickButtonEvent
    {
        unsigned int joystickId; ///< Index of the joystick (in range [0 .. Joystick::Count - 1])
        unsigned int button;     ///< Index of the button that has been pressed (in range [0 .. Joystick::ButtonCount - 1])
    };

    ////////////////////////////////////////////////////////////
    /// \brief Enumeration of the different types of events
    ///
    ////////////////////////////////////////////////////////////
    enum EventType
    {
        Closed,                 ///< The window requested to be closed (no data)
        Resized,                ///< The window was resized (data in event.size)
        LostFocus,              ///< The window lost the focus (no data)
        GainedFocus,            ///< The window gained the focus (no data)
        TextEntered,            ///< A character was entered (data in event.text)
        KeyPressed,             ///< A key was pressed (data in event.key)
        KeyReleased,            ///< A key was released (data in event.key)
        MouseWheelMoved,        ///< The mouse wheel was scrolled (data in event.mouseWheel)
        MouseButtonPressed,     ///< A mouse button was pressed (data in event.mouseButton)
        MouseButtonReleased,    ///< A mouse button was released (data in event.mouseButton)
        MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
        MouseEntered,           ///< The mouse cursor entered the area of the window (no data)
        MouseLeft,              ///< The mouse cursor left the area of the window (no data)
        JoystickButtonPressed,  ///< A joystick button was pressed (data in event.joystickButton)
        JoystickButtonReleased, ///< A joystick button was released (data in event.joystickButton)
        JoystickMoved,          ///< The joystick moved along an axis (data in event.joystickMove)
        JoystickConnected,      ///< A joystick was connected (data in event.joystickConnect)
        JoystickDisconnected,   ///< A joystick was disconnected (data in event.joystickConnect)

        Count                   ///< Keep last -- the total number of event types
    };

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    EventType type; ///< Type of the event

    union
    {
        SizeEvent            size;            ///< Size event parameters (Event::Resized)
        KeyEvent             key;             ///< Key event parameters (Event::KeyPressed, Event::KeyReleased)
        TextEvent            text;            ///< Text event parameters (Event::TextEntered)
        MouseMoveEvent       mouseMove;       ///< Mouse move event parameters (Event::MouseMoved)
        MouseButtonEvent     mouseButton;     ///< Mouse button event parameters (Event::MouseButtonPressed, Event::MouseButtonReleased)
        MouseWheelEvent      mouseWheel;      ///< Mouse wheel event parameters (Event::MouseWheelMoved)
        JoystickMoveEvent    joystickMove;    ///< Joystick move event parameters (Event::JoystickMoved)
        JoystickButtonEvent  joystickButton;  ///< Joystick button event parameters (Event::JoystickButtonPressed, Event::JoystickButtonReleased)
        JoystickConnectEvent joystickConnect; ///< Joystick (dis)connect event parameters (Event::JoystickConnected, Event::JoystickDisconnected)
    };
  };

  class Callback : public ::tgui::Callback
  {
  public:
    Callback() {}
    virtual ~Callback() {}
  };

  //WINDOW
  class	RenderWindow : public ::tgui::Window
  {
  public:
    RenderWindow(int x = 800,
		 int y = 600,
		 const std::string &title = "Main Window",
		 MYUINT32 style = My::Style::Close)
      : ::tgui::Window(::sf::VideoMode(x, y),
			   title,
			   style)
    {
    }

    bool 	pollEvent(Event &event)
    {
      sf::Event *e = reinterpret_cast<sf::Event *>(&event);
      return (::sf::RenderWindow::pollEvent(*e));
    }

    void 	handleEvent(Event event)
    {
      sf::Event *e = reinterpret_cast<sf::Event *>(&event);
      ::tgui::Window::handleEvent(*e);
    }

    virtual ~RenderWindow() {}
  };
}

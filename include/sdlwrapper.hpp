#ifndef __SDL_WRAPPER_HPP__
#define __SDL_WRAPPER_HPP__

#include <SDL.h>

class SDLWrapper
{
public:
    enum Status
    {
        NO_INIT,
        NO_WINDOW,
        INIT,

        NUM_STATUS
    };

    SDLWrapper();
    ~SDLWrapper();

    const Status GetStatus() const { return m_status; };

    void Render();
    int MustQuit();

private:
    Status m_status;
    SDL_Window *m_window;
    SDL_GLContext m_context;
    SDL_Event m_event;
};

#endif // __SDL_WRAPPER_HPP__

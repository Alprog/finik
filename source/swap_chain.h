#pragma once

class Window;

class SwapChain
{
public:
    SwapChain(Window& window);

private:
    Window& window;
};
#pragma once

class View
{
public:
    View(const char* name);

    void draw();

protected:
    virtual void draw_content() = 0;

    const char* name;
};
#pragma once

#include "view.h"

class ConsoleView : public View
{
public:
    ConsoleView(const char* name);

protected:
    void draw_content() override;
};
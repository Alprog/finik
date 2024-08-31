#pragma once

#include "view.h"

class ProfilerView : public View
{
    using View::View;

public:
    void draw_content() override;
};
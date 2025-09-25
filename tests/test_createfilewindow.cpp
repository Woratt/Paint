#include "../createfilewindow.h"
#include <gtest/gtest.h>

struct CreateFileWindowFixture : public testing::Test
{
    createFileWindow *fileWindow;

    void SetUp() override { fileWindow = new createFileWindow(); }
};
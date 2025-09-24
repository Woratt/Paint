#include <gtest/gtest.h>
#include "../createfilewindow.h"

struct CreateFileWindowFixture : public testing::Test{
    createFileWindow* fileWindow;

    void SetUp() override {
        fileWindow = new createFileWindow();
    }
};
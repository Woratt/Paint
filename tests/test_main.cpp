#include <gtest/gtest.h>
#include <QApplication>

class QtAppFixture : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Ініціалізація Qt один раз для всіх тестів
        static int argc = 1;
        static char* argv[] = {(char*)"test", nullptr};
        if (qApp == nullptr) {
            new QApplication(argc, argv);
        }
    }
};

int main(int argc, char **argv) {
    // Ініціалізація Qt
    QApplication app(argc, argv);
    
    // Ініціалізація GTest
    ::testing::InitGoogleTest(&argc, argv);
    
    // Запуск тестів
    return RUN_ALL_TESTS();
}
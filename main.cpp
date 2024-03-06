#include <TLTK.hpp>

int main() {
    TLTK::Window window("Kilt IDE", TLTK::Vector2i(800, 600));

    // Create a main page
    TLTK::Page mainPage("Main Page");

    // Add some widgets to the main page
    mainPage.addWidget(new TLTK::Label("Welcome to Kilt IDE", TLTK::Vector2i(10, 10)));
    mainPage.addWidget(new TLTK::Button("New File", TLTK::Vector2i(10, 50), [](){ 
        // Code to handle creating a new file
        std::cout << "Creating a new file...\n";
    }));
    mainPage.addWidget(new TLTK::Button("Open File", TLTK::Vector2i(10, 90), [](){ 
        // Code to handle opening a file
        std::cout << "Opening a file...\n";
    }));
    mainPage.addWidget(new TLTK::Button("Save File", TLTK::Vector2i(10, 130), [](){ 
        // Code to handle saving a file
        std::cout << "Saving a file...\n";
    }));

    // Add the main page to the window
    window.addPage(mainPage);

    // Main application loop
    while (window.isOpen()) {
        window.update();
    }

    return 0;
}

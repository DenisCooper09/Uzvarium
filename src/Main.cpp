#include "Application.hpp"

int main()
{
    try
    {
        Uz::Application app;
    }
    catch (const std::exception& exception)
    {
        std::cerr << "[UZVARIUM] Error: " << exception.what() << '\n';
    }
}

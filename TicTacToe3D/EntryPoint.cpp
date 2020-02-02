#define CONSOLE_APP

//If the configure type is .exe
#ifdef CONSOLE_APP
int main() {
    return 0;
}
#endif // CONSOLE_APP

//If the configure type is .dll
#ifndef CONSOLE_APP
extern "C" __declspec(dllexport) int GetBestMove(char* gameBoard, int gameSize, int lastFill)
{
    return 0;
}
extern "C" __declspec(dllexport) bool IsTerminal(char* gameBoard, int gameSize, int lastFill)
{
    return false;
}
#endif // !CONSOLE_APP

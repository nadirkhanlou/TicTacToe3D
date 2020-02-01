#define CONSOLE_APP

//If the configure type is .exe
#ifdef CONSOLE_APP
int main() {
    return 0;
}
#endif // CONSOLE_APP

//If the configure type is .dll
#ifndef CONSOLE_APP
extern "C" __declspec(dllexport) int GetBestMove(char* gameBoard, int gameSize, bool isXTurn)
{
    return 0;
}
#endif // !CONSOLE_APP

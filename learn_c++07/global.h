//
// Created by lyx on 2025/7/29.
//

#ifndef LEARNC___GLOBAL_H
#define LEARNC___GLOBAL_H
const int bufSize = 10;
extern void PrintBufAdress();
extern const int bufSize2;
extern int GetSize();
inline constexpr int GetSizeConst(){
    return 1;
}
#endif //LEARNC___GLOBAL_H

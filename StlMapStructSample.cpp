// StlMapStructSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <windows.h>
#include <iostream>
#include <utility>
#include <string>
#include <tuple>
#include <map>

#define MAX_IDX 10

typedef struct {
    std::map<DWORD, std::tuple<DWORD, BOOL>> mtSample;
} SAMPLESTRUCT1, *LPSAMPLESTRUCT1;

typedef struct {
    DWORD adwSample[MAX_IDX + 1];
    BOOL abSample[MAX_IDX + 1];
} SAMPLESTRUCT2, *LPSAMPLESTRUCT2;

int main()
{
    SAMPLESTRUCT1 stSample1;
    ::RtlZeroMemory(&stSample1, sizeof(SAMPLESTRUCT1));
    SAMPLESTRUCT2 stSample2;
    ::RtlZeroMemory(&stSample2, sizeof(SAMPLESTRUCT2));

    for (int i = 0; i < 10; i++) {
        stSample2.adwSample[i] = i;
        stSample2.abSample[i] = i % 2 == 0;
    }

#pragma region SAMPLESTRUCT2のZeroMemoryは問題ない
    std::cout << "==================================================" << std::endl;
    std::cout << "== SAMPLESTRUCT2                                ==" << std::endl;
    std::cout << "==================================================" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "i: " << i << std::endl;
        std::cout << "  adwSample: " << stSample2.adwSample[i] << std::endl;
        std::cout << "  abSample: " << stSample2.abSample[i] << std::endl;
    }

    for (int i = 0; i < 10; i++) {
        stSample1.mtSample.insert(
            std::make_pair(
                i,
                std::make_tuple(
                    i,
                    i % 2)));
    }
#pragma endregion

#pragma region SAMPLESTRUCT1のZeroMemoryはヤバい
    std::cout << "==================================================" << std::endl;
    std::cout << "== SAMPLESTRUCT1                                ==" << std::endl;
    std::cout << "==================================================" << std::endl;
    for (int i = 0; i < 10; i++) {
        std::cout << "i: " << i << std::endl;
        std::cout << "  std::get<0>(mtSample): " << std::get<0>(stSample1.mtSample[i]) << std::endl;
        std::cout << "  std::get<1>(mtSample): " << std::get<1>(stSample1.mtSample[i]) << std::endl;
    }
#pragma endregion

    std::cout << "end" << std::endl;
}

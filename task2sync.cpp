#include <iostream>
#include <fstream>
#include <chrono>

const int MAX_NUM = 10000;
const int BUF_SIZE = 10000;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    char buffer[BUF_SIZE];
    for (int i = 0; i < BUF_SIZE; i++)
        buffer[i] = 'a';

    std::ofstream out_file("data.txt", std::ios::binary);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX_NUM; i++)
        out_file.write(buffer, BUF_SIZE);
    out_file.close();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Without synchronization: " << duration.count() << " milliseconds" << std::endl;

    std::ios_base::sync_with_stdio(true);
    std::cin.tie(0);
    std::cout.tie(0);

    out_file.open("data.txt", std::ios::binary);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX_NUM; i++)
        out_file.write(buffer, BUF_SIZE);
    out_file.close();
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "With synchronization: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}
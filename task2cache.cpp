#include <iostream>
#include <fstream>
#include <chrono>

const int MAX_NUM = 100000;
const int BUF_SIZE = 100000;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    char buffer[BUF_SIZE];
    for (int i = 0; i < BUF_SIZE; i++)
        buffer[i] = 'a';

    std::ofstream out_file("data.txt", std::ios::binary);
    for (int i = 0; i < MAX_NUM; i++)
        out_file.write(buffer, BUF_SIZE);
    out_file.close();

    std::ifstream in_file("data.txt", std::ios::binary);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX_NUM; i++)
        in_file.read(buffer, BUF_SIZE);
    in_file.close();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Without caching: " << duration.count() << " milliseconds" << std::endl;

    in_file.open("data.txt", std::ios::binary);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < MAX_NUM; i++)
        in_file.read(buffer, BUF_SIZE);
    in_file.close();
    stop = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "With caching: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}

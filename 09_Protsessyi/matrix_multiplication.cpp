#include <iostream>
#include <vector>
#include <thread>
#include <functional>

void multiplyRowByMatrix(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int row) {
    int n = B.size();
    int m = B[0].size();
    for (int j = 0; j < m; ++j) {
        C[row][j] = 0;
        for (int k = 0; k < n; ++k) {
            C[row][j] += A[row][k] * B[k][j];
        }
    }
}

void parallelMatrixMultiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {
    int numRows = A.size();
    std::vector<std::thread> threads;

    for (int i = 0; i < numRows; ++i) {
        threads.push_back(std::thread(multiplyRowByMatrix, std::cref(A), std::cref(B), std::ref(C), i));
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

int main() {
    std::vector<std::vector<int>> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    std::vector<std::vector<int>> B = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
    int numRows = A.size();
    int numCols = B[0].size();

    std::vector<std::vector<int>> C(numRows, std::vector<int>(numCols));

    parallelMatrixMultiply(A, B, C);

    std::cout << "Result of A * B:" << std::endl;
    for (const auto& row : C) {
        for (int val : row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

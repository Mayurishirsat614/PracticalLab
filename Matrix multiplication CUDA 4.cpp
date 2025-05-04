
#include <iostream>
#include <cuda_runtime.h>

__global__ void matmul(int *A, int *B, int *C, int N) {
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;

  if (row < N && col < N) {
    int sum = 0;
    for (int k = 0; k < N; ++k) {
      
      sum += A[row * N + k] * B[k * N + col];
    }
    C[row * N + col] = sum;
  }
}

int main() {
  int N = 512;
  int size = N * N * sizeof(int);


  int *h_A, *h_B, *h_C;
  cudaMallocHost(&h_A, size);
  cudaMallocHost(&h_B, size);
  cudaMallocHost(&h_C, size);


  int *d_A, *d_B, *d_C;
  cudaMalloc(&d_A, size);
  cudaMalloc(&d_B, size);
  cudaMalloc(&d_C, size);


  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      h_A[i * N + j] = i * N + j;
      h_B[i * N + j] = j * N + i;
    }
  }

  
  cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

  
  int threadsPerBlock = 16;
  int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;
  dim3 dimBlock(threadsPerBlock, threadsPerBlock);
  dim3 dimGrid(blocksPerGrid, blocksPerGrid);
  matmul<<<dimGrid, dimBlock>>>(d_A, d_B, d_C, N);

 
  cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

  // Print the result (limited to a sub-matrix for large N)
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      std::cout << h_C[i * N + j] << " ";
    }
    std::cout << std::endl;
  }

 
  cudaFree(d_A);
  cudaFree(d_B);
  cudaFree(d_C);
  cudaFreeHost(h_A);
  cudaFreeHost(h_B);
  cudaFreeHost(h_C);

  return 0;
}
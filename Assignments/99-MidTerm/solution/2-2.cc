#include "2-2-chunks.h"
#include <cinttypes>
#include <cstdio>
#include <iostream>
using namespace std;
int main() {
  std::vector<std::uint16_t> v_us(256);
  std::iota(std::begin(v_us), std::end(v_us), 1);

  //                                    ,-- wrapped container
  //                                    |
  cpppc::chunks<128, std::uint16_t, std::vector<std::uint16_t>> v_chunks(v_us);
  //             |      |
  //             |      '-- element type
  //             |
  //             '-- maximum size of a
  //                 single chunk in bytes

  // Iterate chunks:
  auto first_chunk = v_chunks.begin();
  auto num_chunks = std::distance(v_chunks.begin(), v_chunks.end());
  // --> 128/(16/8) = 64
  std::cout << "Number of chunks (" << v_us.size() << " elements * "
            << sizeof(std::uint16_t)
            << " Bytes = 512 Bytes / 128 "
               "Bytes chunks size = 4): "
            << num_chunks << "\n";

  // Iterators on elements in a chunk:
  uint16_t first_chunk_elem = *first_chunk.begin();
  // uint16_t first_chunk_elem2 = *(*first_chunk).begin();
  std::cout << first_chunk_elem << '\n';
  // std::cout << first_chunk_elem2 << '\n';
  uint16_t third_chunk_elem = first_chunk[2];
  std::cout << third_chunk_elem << '\n';
  //
  // // Pointer to data in second chunk:
  auto chunk_1_data = v_chunks[1].data();
  std::cout << *chunk_1_data << '\n';
  // // Pointer to data in third chunk (= end pointer of data in secondchunk):
  auto chunk_2_data = v_chunks[2].data();
  std::cout << *chunk_2_data << '\n';

  // Iterate chunks:
  auto first_chunk2 = v_chunks.begin();
  auto num_chunks2 = std::distance(v_chunks.begin(), v_chunks.end());
  // --> 128/(16/8) = 64

  // Iterators on elements in a chunk:
  std::uint16_t first_chunk_elem2 = *first_chunk.begin();
  std::uint16_t third_chunk_elem2 = first_chunk[2];

  // Pointer to data in second chunk:
  const std::uint16_t *chunk_1_data2 = v_chunks[1].data();
  // Pointer to data in third chunk (= end pointer of data in second chunk):
  const std::uint16_t *chunk_2_data2 = v_chunks[2].data();
  return 1;
}

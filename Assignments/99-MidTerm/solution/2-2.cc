#include "2-2-chunks.h"
#include <cinttypes>
#include <cstdio>
#include <iostream>
using namespace std;
int main() {
  std::vector<std::uint16_t> v_us(256);
  std::iota(std::begin(v_us), std::end(v_us), 0);

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
  std::cout << *first_chunk << '\n';
  auto num_chunks = std::distance(v_chunks.begin(), v_chunks.end());
  // --> 128/(16/8) = 64
  std::cout << "Chunk Size: " << num_chunks << "\n";

  // Iterators on elements in a chunk:
  uint16_t first_chunk_elem = *first_chunk.begin();
  std::cout << first_chunk_elem << '\n';
  uint16_t third_chunk_elem = first_chunk[2];
  std::cout << third_chunk_elem << '\n';
  //
  // // Pointer to data in second chunk:
  auto chunk_1_data = v_chunks[1].data();
  std::cout << *chunk_1_data << '\n';
  // // Pointer to data in third chunk (= end pointer of data in second chunk):
  auto chunk_2_data = v_chunks[2].data();
  std::cout << *chunk_2_data << '\n';
  return 1;
}

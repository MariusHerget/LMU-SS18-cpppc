#include <celero/Celero.h>

#include "virtual.h"
#include "crtp.h"
#include <iostream>
#include <random>

#ifndef WIN32
#include <cmath>
#include <cstdlib>
#endif

///
/// This is the main(int argc, char** argv) for the entire celero program.
/// You can write your own, or use this macro to insert the standard one into
/// the project.
///
CELERO_MAIN

std::random_device RandomDevice;
std::uniform_int_distribution<int> UniformDistribution(0, 1024);

static const int probSpaceStart = 128;
static const int probSpaceEnd   = 4096;

class Shaming : public celero::TestFixture {
public:
  Shaming() {}

  // It's ironic that we are shaming virtual and to do this we are using
  // a framework which implements virtual :D
  virtual std::vector<std::pair<int64_t, uint64_t>>
  getExperimentValues() const override {
    std::vector<std::pair<int64_t, uint64_t>> problemSpace;

    // ExperimentValues is part of the base class and allows us to specify
    // some values to control various test runs to end up building a nice graph.
    for (int64_t elements = probSpaceStart; elements <= int64_t(probSpaceEnd); elements *= 2) {
      problemSpace.push_back(std::make_pair(int64_t(elements), uint64_t(0)));
    }

    return problemSpace;
  }

  /// Before each sample, build a vector of random integers.
  virtual void setUp(int64_t experimentValue) override {
    this->arraySize = experimentValue;
  }

  // Before each iteration
  virtual void onExperimentStart(int64_t) override {
    this->array.resize(this->arraySize);
    for (int64_t i = 0; i < this->arraySize; i++) {
      this->array[i] = rand();
    }
    // std::cout << "!!! " << arraySize << "  " << array.size() << " !!!";
    sum = 0;
  }

  // After each iteration
  virtual void onExperimentEnd() override {
    // std::cout << "\t" << sum;
    this->array.clear();
  }

  // After each sample
  virtual void tearDown() override {}

  std::vector<int64_t> array;
  int64_t arraySize;
  long sum;
};

static const int SamplesCount = 2000;
static const int IterationsCount = 20;

BASELINE_F(badVirtual, directAccess, Shaming, SamplesCount, IterationsCount) {
  for (int64_t i = 0; i < arraySize; i++) {
    sum += array.at(i) * array.at(i) *2;
  }
}

BENCHMARK_F(badVirtual, Virtual, Shaming, SamplesCount, IterationsCount) {
  // auto v = new VectorImpl<int64_t, std::vector<int64_t> *>(array);
  auto v = new BadVectorImpl();
  v->setArray(&array);
  for (int64_t i = 0; i < arraySize; i++) {
    sum += v->get(i);
  }
}

BENCHMARK_F(badVirtual, CRTP, Shaming, SamplesCount, IterationsCount) {
  // auto v = new VectorImpl<int64_t, std::vector<int64_t> *>(array);
  auto v = new GoodVectorImpl(&array);
  for (int64_t i = 0; i < arraySize; i++) {
    sum += v->get(i);
  }
}

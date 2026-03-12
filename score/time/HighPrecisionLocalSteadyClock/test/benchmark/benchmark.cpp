/********************************************************************************
 * Copyright (c) 2026 Contributors to the Eclipse Foundation
 *
 * See the NOTICE file(s) distributed with this work for additional
 * information regarding copyright ownership.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0
 *
 * SPDX-License-Identifier: Apache-2.0
 ********************************************************************************/
#include "score/time/HighPrecisionLocalSteadyClock/details/factory_impl.h"

#include <benchmark/benchmark.h>

namespace score
{
namespace time
{
namespace server
{

class ServerBenchmarkFixture : public benchmark::Fixture
{
  public:
    ServerBenchmarkFixture()
    {
        high_precision_clock_ = HighPrecisionLocalSteadyClock::FactoryImpl().CreateHighPrecisionLocalSteadyClock();

        this->Repetitions(1);
        this->ReportAggregatesOnly(true);
        this->ThreadRange(1, 16);
        this->UseRealTime();
        this->MeasureProcessCPUTime();
    }

    ~ServerBenchmarkFixture() {}

    std::unique_ptr<HighPrecisionLocalSteadyClock> high_precision_clock_;
};

// Benchmark score::time::HighPrecisionLocalSteadyClock::Now()
BENCHMARK_F(ServerBenchmarkFixture, ServerInit)(benchmark::State& state)
{
    for (auto _ : state)
    {
        benchmark::DoNotOptimize(high_precision_clock_->Now());
    }
}

// Run the benchmark
BENCHMARK_MAIN();

}  // namespace server
}  // namespace time
}  // namespace score

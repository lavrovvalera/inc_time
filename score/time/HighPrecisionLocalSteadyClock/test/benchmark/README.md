# Benchmark HighPrecisionLocalSteadyClock

## Purpose
This module benchmarks HighPrecisionLocalSteadyClock performance on IPNext hardware directly.

## How-to-use

### Build

Binary should be build with:
bazel build --config=ipnext_arm64_qnx //score/time/HighPrecisionLocalSteadyClock/test/benchmark:HighPrecisionLocalSteadyClockBenchmark

### Run on target

- Build binary
- SCP to IPNext /tmp/ and run

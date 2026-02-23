# Basic information

`clock_realtime` is a stub implementation used only for qnx qqvp virtual machine, until qgptp will be fully available on qqvp. Solution is based
on `std::chrono::high_resolution_clock` as ticks for `::Now()` interface.

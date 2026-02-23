/********************************************************************************
 * Copyright (c) 2025 Contributors to the Eclipse Foundation
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
#ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_SLAVE_TIMEBASE_NOTIFICATION_TYPES_H
#define SCORE_TIME_SYNCHRONIZEDVEHICLETIME_SLAVE_TIMEBASE_NOTIFICATION_TYPES_H

#include <chrono>
#include <cstdint>
#include <ostream>

namespace score
{
namespace time
{

///
/// \brief Representation of HW timer on the local ethernet device where PTP messages
///        are received and which gets utilized for ingress & egress timestamping.
///
struct LocalPTPDeviceTimer
{
    using Duration = std::chrono::nanoseconds;
};
using LocalPTPDeviceTimerValue = std::chrono::time_point<LocalPTPDeviceTimer, LocalPTPDeviceTimer::Duration>;

///
/// \brief Representation of HW timer on the ethernet device of the PTP time master where the PTP client's
///        pDelay measurement request packets are received and the corresponding reply packets will be sent.
///
struct MasterPTPDeviceTimer
{
    using Duration = std::chrono::nanoseconds;
};
using MasterPTPDeviceTimerValue = std::chrono::time_point<MasterPTPDeviceTimer, MasterPTPDeviceTimer::Duration>;

/// \brief Structure containing the pieces of inform. that identify a certain participant involved in PTP communication.
struct PortIdentity
{
    /// \brief clock identity of the PTP port
    std::uint64_t clock_identity{};

    /// \brief port number of the PTP port
    std::uint16_t port_number{};

    /// \brief print content to any output stream
    template <typename OutputStream>
    auto& PrintTo(OutputStream& output_stream) const
    {
        /* False positives: << incorrectly identified as bitwise operators, no address of a local variable is
         * returned.*/
        return output_stream << "(" << clock_identity << ", " << port_number << ")";
    }
};

/// \brief output operator for any stream
template <typename OutputStream>
auto& operator<<(OutputStream& output_stream, const PortIdentity& port_identity)
{
    return port_identity.PrintTo(output_stream);
}

///
/// \brief Structure containing detailed data about synchronization updates received for a Time Slave.
///
template <typename Timebase>
struct TimeSlaveSyncData
{
    /// \brief Time Master's timestamp of global time at which a Sync Frame has actually been transmitted
    ///        at it its Ethernet port and which gets put into the Sync Follow-Up Frame sent afterwards
    typename Timebase::Timepoint precise_origin_timestamp{};

    /// \brief Time Slave's timestamp of global time after the sync process took place
    typename Timebase::Timepoint reference_global_timestamp{};

    /// \brief Time Slave's local time (e.g. Ethernet device's HW timer) after the sync process took place
    LocalPTPDeviceTimerValue reference_local_timestamp{};

    /// \brief Time Slave's value of local time (e.g. Ethernet device's HW timer) at the point where
    ///        it received the Sync Frame at its Ethernet port
    LocalPTPDeviceTimerValue sync_ingress_timestamp{};

    /// \brief correction value taken from the Sync Follow-Up Frame (PTP standard field which gets filled
    ///        e.g. by Ethernet Bridges or Switches between the Time Master and the Time Slave) and which
    ///        needs to be considered at Time Slave side. NOTE: the unit of this value is 1 / 0x10000
    ///        nanoseconds, meaning a value of 0x10000 in correction_field is equal to 1 nanosecond)
    std::int64_t correction_field{};

    /// \brief sequence number of the received Sync Frame
    std::uint16_t sequence_id{};

    /// \brief currently valid pDelay value
    std::chrono::nanoseconds pdelay{};

    /// \brief identity of the port the Sync & Follow-Up Frames originate from
    PortIdentity source_port_identity{};

    /// \brief print content to any output stream
    template <typename OutputStream>
    auto& PrintTo(OutputStream& output_stream) const
    {
        /* False positives: << incorrectly identified as bitwise operators, no address of a local variable is returned.
         */
        return output_stream << "[" << precise_origin_timestamp.time_since_epoch().count() << ", "
                             << reference_global_timestamp.time_since_epoch().count() << ", "
                             << reference_local_timestamp.time_since_epoch().count() << ", "
                             << sync_ingress_timestamp.time_since_epoch().count() << ", " << correction_field
                             << " / 0x10000, " << sequence_id << ", " << pdelay.count() << ", " << source_port_identity
                             << "]";
    }
};

///
/// \brief output operator for any stream
///
template <typename OutputStream, typename Timebase>
auto& operator<<(OutputStream& output_stream, const TimeSlaveSyncData<Timebase>& sync_data)
{
    return sync_data.PrintTo(output_stream);
}

/// \brief output operator required for gtest
template <typename Timebase>
/* The dereference output_stream is passed as a non-const reference. Therfore, output_stream should be a pointer to a
 * non-const. */
void PrintTo(const TimeSlaveSyncData<Timebase>& sync_data, std::ostream* const output_stream)
{
    sync_data.PrintTo(*output_stream);
}

///
/// \brief Structure containing detailed data about the pDelay measurement performed by a Time Slave.
///
template <typename Timebase>
struct PDelayMeasurementData
{
    /// \brief Time Slave's value of local time (e.g. Ethernet device's HW timer) at the point
    ///        where it transmitted the pDelay Request Frame via its Ethernet port
    LocalPTPDeviceTimerValue request_origin_timestamp{};

    /// \brief Time Master's timestamp of global or local time at which it received
    ///        the pDelay Request Frame at its Ethernet port
    MasterPTPDeviceTimerValue request_receipt_timestamp{};

    /// \brief Time Master's timestamp of global or local time at which it transmitted
    ////       the pDelay Response Frame from its Ethernet port
    MasterPTPDeviceTimerValue response_origin_timestamp{};

    /// \brief Time Slave's value of local time (e.g. Ethernet device's HW timer) at the point
    ///        where it received the pDelay Response Frame at its Ethernet port
    LocalPTPDeviceTimerValue response_receipt_timestamp{};

    /// \brief Time Slave's timestamp of global time at which the process of
    ///        measuring pDelay was initiated
    typename Timebase::Timepoint reference_global_timestamp{};

    /// \brief Time Slave's value of local time (e.g. Ethernet device's HW timer) at the
    ///        point where it captured the reference_global_timestamp
    LocalPTPDeviceTimerValue reference_local_timestamp{};

    /// \brief sequence number of the pDelay Request Frame
    std::uint16_t sequence_id{};

    /// \brief measured pDelay value
    std::chrono::nanoseconds pdelay{};

    /// \brief identity of the port from where the pDelay measurement got initiated
    PortIdentity request_port_identity{};

    /// \brief identity of the port that responded to the pDelay measurement
    PortIdentity response_port_identity{};

    /// \brief print content to any output stream
    template <typename OutputStream>
    auto& PrintTo(OutputStream& output_stream) const
    {
        /* False positives: << incorrectly identified as bitwise operators, no address of a local variable is returned.
         */
        return output_stream << "[" << request_origin_timestamp.time_since_epoch().count() << ", "
                             << request_receipt_timestamp.time_since_epoch().count() << ", "
                             << response_origin_timestamp.time_since_epoch().count() << ", "
                             << response_receipt_timestamp.time_since_epoch().count() << ", "
                             << reference_global_timestamp.time_since_epoch().count() << ", "
                             << reference_local_timestamp.time_since_epoch().count() << ", " << sequence_id << ", "
                             << pdelay.count() << ", " << request_port_identity << ", " << response_port_identity
                             << "]";
    }
};

///
/// \brief output operator for any stream
///
template <typename OutputStream, typename Timebase>
auto& operator<<(OutputStream& output_stream, const PDelayMeasurementData<Timebase>& pdelay_data)
{
    return pdelay_data.PrintTo(output_stream);
}

///
/// \brief output operator required for gtest
///
template <typename Timebase>
void PrintTo(const PDelayMeasurementData<Timebase>& pdelay_data, std::ostream* const output_stream)
{
    pdelay_data.PrintTo(*output_stream);
}

}  // namespace time
}  // namespace score

#endif  // #ifndef SCORE_TIME_SYNCHRONIZEDVEHICLETIME_SLAVE_TIMEBASE_NOTIFICATION_TYPES_H

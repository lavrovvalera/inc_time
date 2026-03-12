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
#ifndef SCORE_TIME_COMMON_TIME_BASE_STATUS_H
#define SCORE_TIME_COMMON_TIME_BASE_STATUS_H

#include <sstream>
#include <cstdint>

#include <score/assert.hpp>

namespace score
{
namespace time
{

///
/// \brief Default member type alias to express the StatusFlagType type for the time base status.
///
using StatusFlagType = std::uint8_t;

///
/// \brief This class encapsulates the common functionality of the TimeBaseStatus as it is created by every time base.
///
/// \tparam FlagEnumT Type used as an input for checking if flag is active and initializing TimeBaseStatus with
/// particular active flags - they shall be treated as bit positions
/// \tparam StatusFlagT Type used to store of all active flags
///
template <typename FlagEnumT>
class TimeBaseStatus final
{
    static_assert(std::is_enum<FlagEnumT>::value, "FlagEnumT must be an enum");
    using StatusFlagT = std::underlying_type_t<FlagEnumT>;

  public:
    ///
    /// \brief Constructor that initializes TimeBaseStatus with provided flagList container. Its simple
    ///        to use with using FlagEnumT types
    ///
    /// \param flag_list The list of status flags that should be set for this status
    ///
    TimeBaseStatus(const std::initializer_list<FlagEnumT> flag_list) noexcept : status_flags_{}
    {
        for (const auto flag : flag_list)
        {
            AddStatusFlagTo(status_flags_, flag);
        }
    }

    TimeBaseStatus() = default;
    TimeBaseStatus(const TimeBaseStatus&) = default;
    TimeBaseStatus(TimeBaseStatus&&) noexcept = default;
    TimeBaseStatus& operator=(const TimeBaseStatus&) = default;
    TimeBaseStatus& operator=(TimeBaseStatus&&) noexcept = default;
    ~TimeBaseStatus() noexcept = default;

    /// \brief Method that can be used to check, if a certain flag were set during the time when the status was
    /// obtained.
    ///
    /// \param flag The StatusFlag that shall be checked.
    ///
    /// \return True if the flag was set, otherwise false.
    ///
    bool IsFlagActive(const FlagEnumT flag) const noexcept
    {
        const StatusFlagT flag_position{static_cast<StatusFlagT>(flag)};

        SCORE_LANGUAGE_FUTURECPP_ASSERT_PRD_MESSAGE((flag_position < (sizeof(StatusFlagT) * 8U)),
                               "mw::time: IsFlagActive() argument 'flag' exceeds possible size of status_flags_ type");

        return static_cast<bool>(status_flags_ & (static_cast<StatusFlagT>(1U << flag_position)));
    }

    /// \brief Method that can be used to check, if a certain flags were set during the time when the status was
    /// obtained.
    ///
    /// \param flag_list The StatusFlag list that shall be checked.
    ///
    /// \return True if any of the flags was set, otherwise false.
    ///
    bool IsAnyOfFlagsActive(const std::initializer_list<FlagEnumT>& flag_list) const noexcept
    {
        bool is_any_flag_set{false};
        for (const auto flag : flag_list)
        {
            if (IsFlagActive(flag))
            {
                is_any_flag_set = true;
                break;
            }
        }
        return is_any_flag_set;
    }

    /// \brief Method that can be used to check, if a timebase is synchronized
    ///
    /// \note it requires a specialization per timebase functionality
    ///
    /// \return True if timebase status is synchronized.
    ///
    bool IsSynchronized() const;

    /// \brief Method that can be used to check, if a timebase is in valid state
    ///
    /// \note it requires a specialization per timebase functionality
    ///
    /// \return True if timebase status is in valid state.
    ///
    bool IsValid() const;

    /// \brief Print all status flags to output stream
    ///
    /// \note it requires a specialization per timebase functionality
    ///
    std::ostringstream PrintTo() const;

    /// \brief Method to add new active flags to status
    /// \param flag specified flag to be added as active
    ///
    void AddFlag(const FlagEnumT flag)
    {
        AddStatusFlagTo(status_flags_, flag);
    }

    /// \brief Method compares two TimeBaseStatus objects
    ///
    /// \param lhs first object
    /// \param rhs object to compare with lhs
    ///
    friend bool operator==(const TimeBaseStatus& lhs, const TimeBaseStatus& rhs) noexcept
    {
        return lhs.status_flags_ == rhs.status_flags_;
    }

    /// \brief Method to get TimeBaseStatus underlying type, to store them in flag
    /// container outside of the class
    ///
    constexpr StatusFlagT ToUnderlying() const noexcept
    {
        return status_flags_;
    }

    /// \brief Method to retrieve status flags from the container
    /// \param status_flags status flags container
    ///
    void FromUnderlying(const StatusFlagT status_flags) noexcept
    {
        status_flags_ = status_flags;
    }

  private:
    ///
    /// \brief Adds specified status flag to provided container
    ///
    /// \param status_container container to add status flag
    /// \param flag specified flag to be set in status_container
    ///
    static inline void AddStatusFlagTo(StatusFlagT& status_container, const FlagEnumT flag) noexcept
    {
        const StatusFlagT flag_position{static_cast<StatusFlagT>(flag)};
        SCORE_LANGUAGE_FUTURECPP_ASSERT_PRD_MESSAGE((flag_position < (sizeof(status_container) * 8U)),
                               "mw::time: AddStatusFlagTo() argument 'flag' exceeds possible size of used "
                               "'StatusFlagT& status_container'");

        const StatusFlagT temp{static_cast<StatusFlagT>(1U << flag_position)};
        status_container = static_cast<StatusFlagT>(status_container | temp);
    }

    ///
    /// \brief Member variable to store the StatusFlags of the issuing clock
    ///
    StatusFlagT status_flags_;
};

/// \brief output operator to any output stream
template <typename OutputStream, typename FlagEnumT>
auto operator<<(OutputStream& output_stream, const TimeBaseStatus<FlagEnumT>& time_base_status) -> OutputStream&
{
    output_stream << time_base_status.PrintTo().str();
    return output_stream;
}

}  // namespace time
}  // namespace score

#endif  // #define SCORE_TIME_COMMON_TIME_BASE_STATUS_H

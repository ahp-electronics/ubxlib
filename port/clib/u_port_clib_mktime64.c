/*
 * Copyright 2020 u-blox Ltd
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @file
 * @brief an implementation of mktime() with a 64-bit return value.
 */

#ifdef U_CFG_OVERRIDE
# include "u_cfg_override.h" // For a customer's configuration override
#endif

#include "stdint.h"    // int32_t etc.
#include "time.h"      // struct tm

#include "u_port_clib_mktime64.h"

/* ----------------------------------------------------------------
 * COMPILE-TIME MACROS
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * TYPES
 * -------------------------------------------------------------- */

/* ----------------------------------------------------------------
 * VARIABLES
 * -------------------------------------------------------------- */

// For date conversion.
static const char gDaysInMonth[] = {31, 28, 31, 30, 31, 30, 31,
                                    31, 30, 31, 30, 31
                                   };
static const char gDaysInMonthLeapYear[] = {31, 29, 31, 30, 31, 30,
                                            31, 31, 30, 31, 30, 31
                                           };

/* ----------------------------------------------------------------
 * STATIC FUNCTIONS
 * -------------------------------------------------------------- */

// Check if a year is a leap year.
static int32_t isLeapYear(int32_t year)
{
    int32_t leapYear = 0;

    if (year % 400 == 0) {
        leapYear = 1;
    } else if (year % 4 == 0) {
        leapYear = 1;
    }

    return leapYear;
}

/* ----------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * -------------------------------------------------------------- */
// mktime() with a guaranteed 64-bit return value.
//lint -esym(818, pTm) Suppress could be pointer to
// const, need to follow function signature.
int64_t mktime64(struct tm *pTm)
{
    int64_t answer = 0;
    int32_t year;
    int32_t months;

    // TM has years since 1900, so convert to since 1970
    year = pTm->tm_year - 70;
    // Months since January 0-11
    months = pTm->tm_mon;
    months += year * 12;
    // Work out the number of seconds due to the year/month count
    for (int32_t x = 0; x < months; x++) {
        if (isLeapYear((x / 12) + 1970)) {
            answer += gDaysInMonthLeapYear[x % 12] * 3600 * 24;
        } else {
            answer += gDaysInMonth[x % 12] * 3600 * 24;
        }
    }
    // Day (1 to 31)
    answer += (((int64_t) pTm->tm_mday) - 1) * 3600 * 24;
    // Hours (0 to 23)
    answer += ((int64_t) pTm->tm_hour) * 3600;
    // Minutes (0 to 59)
    answer += ((int64_t) pTm->tm_min) * 60;
    // Seconds (0 to 59ish)
    answer += pTm->tm_sec;
    // Since this function returns local time
    // the Daylight Saving Time flag has no
    // effect on the answer.

    return answer;
}

// End of file
